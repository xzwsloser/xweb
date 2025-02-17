// @Author: loser
#pragma once
#include "HttpFilter.h"
#include "../../req/method/HttpMethod.h"

namespace xweb {

class HttpMethodFilter: public HttpFilter {
public:
    virtual bool IsMatch(HttpContext& ctx) override;
    HttpMethod GetMethod() { return method_; }
    void SetMethod(HttpMethod method) { method_ = method; }
private:
    HttpMethod method_;
};

}
