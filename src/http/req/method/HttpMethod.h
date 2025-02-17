// @Author: loser
#pragma once
#include<string>

namespace xweb {

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

class HttpMethod {
public:
    HttpMethod() = default;
    ~HttpMethod() = default;


    static Method CoverToMethod(const std::string& method);
    static std::string ConverToStr(Method method);

    void SetMethod(Method method);
    Method GetMethod();

    std::string ToString() { return ConverToStr(method_); }

private:
    Method method_;
};

}
