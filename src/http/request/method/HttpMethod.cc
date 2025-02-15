#include "HttpMethod.h"

namespace xweb {

HttpMethod::Method HttpMethod::CovertToMethod(const std::string &method)
{
    if(method == "GET") {
        return HttpMethod::Method::GET;
    } else if(method == "POST") {
        return HttpMethod::Method::POST;
    } else if(method == "PUT") {
        return HttpMethod::Method::PUT;
    } else if(method == "DELETE") {
        return HttpMethod::Method::DELETE;
    } else if(method == "HEAD") {
        return HttpMethod::Method::HEAD;
    } else if(method == "OPTIONS") {
        return HttpMethod::Method::OPTIONS;
    } else if(method == "PATCH") {
        return HttpMethod::Method::PATCH;
    } else if(method == "CONNECT") {
        return HttpMethod::Method::CONNECT;
    }
    return HttpMethod::Method::UNKNOW;
}

std::string HttpMethod::ConvertToStr(Method method)
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

void HttpMethod::SetMethod(HttpMethod::Method method)
{
    method_ = method;
}

HttpMethod::Method HttpMethod::GetMethod()
{
    return method_;
}

}
