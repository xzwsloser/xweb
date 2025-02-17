// @Author: loser
#include "HttpReq.h"
#include "../../utils/StringUtils.h"
#include <exception>
#include "../../logger/Logger.h"
#include <functional>

namespace xweb {

int HttpReq::Parse(const std::string& req)
{
    std::string kCRCF = "\r\n";
    int pos = req.find(kCRCF + kCRCF);
    body_ = req.substr(pos + 2 * kCRCF.size());
    std::string context = req.substr(0 , pos);
    pos = context.find(kCRCF);
    std::string reqLine = context.substr(0 , pos);
    std::string headerStr = context.substr(pos + kCRCF.size());

    std::vector<std::string> options;   
    StringUtils::Split(reqLine , " " , options);

    method_.SetMethod(HttpMethod::CoverToMethod(options[0]));
    version_.SetVersion(HttpVersion::ConverToVersion(options[2]));
    route_.Parse(options[1]);
    header_.Parse(headerStr);

    return kSuccess;
}

std::string HttpReq::ToString()
{
    std::string kCRCF = "\r\n";
    std::string reqLine = method_.ToString() + " " + route_.ToString() + " " + version_.ToString() + kCRCF;
    std::string headerStr = header_.ToString() + kCRCF + kCRCF; 
    std::string req = reqLine + headerStr + body_;
    return req;
}

int HttpReq::GetContentLength()
{
    int rc;
    try {
        rc = stoi(header_["Content-Length"]);
    } catch(std::exception& e) {
        LOG_ERROR << "transform content length failed!";
        return kLogicerr;
    }
    return rc;
}

}
