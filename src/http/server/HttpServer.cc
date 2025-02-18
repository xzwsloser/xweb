// @Author: loser
#include "HttpServer.h"
#include "../../../src/utils/SocketUtils.h"

namespace xweb {

void HttpServer::Run(int port)
{
    server_.Init(DEFAULT_THREAD_NUM , port);
    server_.setCallBack(std::bind(&HttpServer::NewEvent , this , 
                std::placeholders::_1 , std::placeholders::_2));
    pool_ -> Init();
    server_.start();
}

void HttpServer::NewEvent(int fd , SP_EventLoop loop)
{
    channel_ -> setEvents(EPOLLIN | EPOLLET);
    channel_ -> setFd(fd);
    channel_ -> SetLoop(loop);
    channel_ -> setReadHandler(std::bind(&HttpServer::handleRead , this));
    channel_ -> setErrorHandler(std::bind(&HttpServer::handleError , this));
    channel_ -> setWriteHandler(std::bind(&HttpServer::handleWrite , this));
    channel_ -> setConnHandler(std::bind(&HttpServer::handleConn , this));
    loop -> pollerAdd(channel_);
}

void HttpServer::handleRead()
{
    pool_ -> AddTask(&HttpServer::RealHandler , this);
}

void HttpServer::handleWrite()
{
    LOG_INFO << "write event comes";
}

void HttpServer::handleError()
{
    LOG_ERROR << "error comes";
}

void HttpServer::handleConn()
{
    // update the channel_
    channel_ -> GetLoop() -> pollerMod(channel_); 
}

void HttpServer::handleClose()
{
    channel_ -> GetLoop() -> pollerDel(channel_);
}

// core method
void HttpServer::RealHandler()
{
    // 1. read the header and line of the request
    std::string buffer; 
    std::string kCRCF = "\r\n";
    auto rc = SocketUtils::ReadUntil(channel_ -> getFd(), buffer , kCRCF + kCRCF);

    LOG_INFO << buffer;

    if(rc < 0) {
        LOG_ERROR << "read failed!" ; 
        handleClose();
        return ;
    } else if(rc == 0) {
        LOG_ERROR << "the connection is close";
        handleClose();
        return ;
    }

    HttpReq req;
    req.Parse(buffer);
    LOG_INFO << req.GetMethod().ToString();
    LOG_INFO << req.GetRoute().GetPath();
    LOG_INFO << req.GetVersion().ToString();

    int len = 0;
    if(req.GetMethod().ToString() != HttpMethod::ConverToStr(Method::GET)) {
        len = req.GetContentLength();
    }

    if(len < 0) {
        LOG_ERROR << "content length error!";
        handleClose();
        return ;
    }

    std::string body = "";

    if(len != 0) {
        len = SocketUtils::Read(channel_->getFd() , body , len);

        if(len < 0) {
            LOG_ERROR << "read failed!";
            handleClose();
            return ;
        } else if(len == 0) {
            LOG_WARN << "body is empty!";
        }

    }
    
    req.SetBody(body);

    // 2. get the HttpContext and search the trie for callback
    HttpContext ctx; 
    ctx.SetReq(req);
    std::function<bool(std::shared_ptr<HttpTrieData>)> cb 
        = [&ctx](std::shared_ptr<HttpTrieData> ptr) -> bool {
        for(auto& rule : ptr -> filters_) {
            if(!(rule -> IsMatch(ctx))) return false;
        }
        return true;
    };

    // get the node
    if(this -> trie_.Search(ctx.req().GetRoute().GetPath() , cb)) {
        auto data = this -> trie_.Get<HttpTrieData>(ctx.req().GetRoute().GetPath());
        if(data -> callback_) {
            data -> callback_(ctx);
        }
    }

    // 3. get the resp and send back
    std::string res = ctx.resp().ToString();
    len = res.size();
    rc = SocketUtils::Write(channel_->getFd() , res , len);
    if(rc <= 0) {
        LOG_ERROR << "write failed!";
        return ;
    }
}

}
