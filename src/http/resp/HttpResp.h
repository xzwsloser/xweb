// @Author: loser
#pragma once
#include<string>
#include "../header/HttpHeader.h"
#include "../version/HttpVersion.h"
#include "./status_code/HttpStatusCode.h"

// An Http Resp:

/**
    HTTP/1.1 200 OK
    Date: Sat, 31 Dec 2005 23:59:59 GMT
    Content-Type: text/html;charset=ISO-8859-1
    Content-Length: 122

    ＜html＞
    ＜head＞
    ＜title＞Wrox Homepage＜/title＞
    ＜/head＞
    ＜body＞
    ＜!-- body goes here --＞
    ＜/body＞
    ＜/html＞
 */

namespace xweb {

class HttpResp {
public:
    HttpResp() = default; 
    ~HttpResp() = default;

    int Parse(const std::string& resp);

    void SetVersion(Version version) { version_.SetVersion(version); };    
    HttpVersion GetVersion() { return version_; }

    void SetCode(StatusCode code) { code_.SetCode(code); }
    HttpStatusCode GetCode() { return code_; }

    void SetHeader(HttpHeader header) { header_ = header; }
    HttpHeader GetHeader() { return header_; }

    void SetBody(const std::string& body) { body_ = body; }
    std::string GetBody() { return body_; }

    void SetContentLength(int ContentLength)  { header_["Content-Length"] = std::to_string(ContentLength); }

    std::string ToString();     
private:
    HttpVersion version_;
    HttpStatusCode code_;
    HttpHeader header_;
    std::string body_;
};

}
