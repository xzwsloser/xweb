#include "HttpMethod.h"

namespace xweb {

Method HttpMethod::CoverToMethod(const std::string &method)
{
    if(method == "GET") {
        return Method::GET;
    } else if(method == "POST") {
        return Method::POST;
    } else if(method == "PUT") {
        return Method::PUT;
    } else if(method == "DELETE") {
        return Method::DELETE;
    } else if(method == "HEAD") {
        return Method::HEAD;
    } else if(method == "OPTIONS") {
        return Method::OPTIONS;
    } else if(method == "PATCH") {
        return Method::PATCH;
    } else if(method == "CONNECT") {
        return Method::CONNECT;
    }
    return Method::UNKNOW;
}

std::string HttpMethod::ConverToStr(Method method)
{
    switch (method) {
        case Method::GET:
            return "GET";
        case Method::POST:
            return "POST";
        case Method::PUT:
            return "PUT";
        case Method::DELETE:
            return "DELETE";
        case Method::HEAD:
            return "HEAD";
        case Method::OPTIONS:
            return "OPTIONS";
        case Method::PATCH:
            return "PATCH";
        case Method::TRACE:
            return "TRACE";
        case Method::CONNECT:
            return "CONNECT";
        default:
            return "UNKNOW";
    }
    return "UNKNOW";
}

void HttpMethod::SetMethod(Method method)
{
    method_ = method;
}

Method HttpMethod::GetMethod()
{
    return method_;
}

}
