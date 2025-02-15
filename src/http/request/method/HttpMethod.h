// @Author: loser
#pragma once
#include<string>

namespace xweb {

class HttpMethod {
public:
    HttpMethod() = default;
    ~HttpMethod() = default;

    enum class Method {
        GET,
        POST,
        PUT,
        DELETE,
        HEAD,
        OPTIONS,
        PATCH,
        TRACE,
        CONNECT,
        UNKNOW
    };

    static Method CovertToMethod(const std::string& method);

private:
    Method method_;
};

}
