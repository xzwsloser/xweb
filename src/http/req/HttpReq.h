// @Author: loser
#pragma once
#include<string>
#include "./method/HttpMethod.h"
#include "./route/HttpRoute.h"
#include "../header/HttpHeader.h"
#include "../version/HttpVersion.h"
#include "../../utils/const.h"


// 请求 = 请求行 + 请求头 + /r/n + 请求体
/*std::string httpRequest = */
/*    "GET /index.html HTTP/1.1\r\n"*/
/*    "Host: www.example.com\r\n"*/
/*    "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\n"*/
    /*"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/
/*    "Accept-Language: en-US,en;q=0.5\r\n"*/
/*    "Accept-Encoding: gzip, deflate, br\r\n"*/
/*    "Connection: keep-alive\r\n"*/
/*    "\r\n";*/
/**/

namespace xweb {

class HttpReq {
public:
    HttpReq() = default;
    ~HttpReq() = default;

    int Parse(const std::string& req);
    
    HttpMethod GetMethod() { return method_; }
    void SetMethod(HttpMethod method) { method_ = method; }
    void SetMethod(Method method) { method_.SetMethod(method); }

    HttpVersion GetVersion() { return version_; }
    void SetVersion(HttpVersion version) { version_ = version; }
    void SetVersion(Version version) { version_.SetVersion(version); }

    HttpRoute GetRoute() { return route_; }
    void SetRoute(HttpRoute route) { route_ = route; }
    
    HttpHeader GetHeader() { return header_; }
    void SetHeader(HttpHeader header) { header_ = header; };

    std::string GetBody() { return body_; }
    void SetBody(const std::string& body) { body_ = body; }

    std::string ToString();

private:
    HttpMethod method_;
    HttpVersion version_;
    HttpRoute route_;
    HttpHeader header_;
    std::string body_;
};

}
