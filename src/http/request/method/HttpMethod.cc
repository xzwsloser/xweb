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

}
