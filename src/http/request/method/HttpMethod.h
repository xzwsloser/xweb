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
    static std::string ConvertToStr(Method method);

    void SetMethod(Method method);
    Method GetMethod();

    std::string ToString() { return ConvertToStr(method_); }

private:
    Method method_;
};

}
