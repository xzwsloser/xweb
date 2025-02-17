// @Author: loser
#pragma once
#include<string>
#include "../resp/HttpResp.h"
#include "../req/HttpReq.h"

namespace xweb {

class HttpContext {
public:
    HttpContext() = default;
    ~HttpContext() = default;

    void Next() { is_continue_ = true; }
    void Abort() { is_continue_ = false; }
    bool IsContinue() { return is_continue_; }
     
private:
    HttpReq req_;
    HttpResp resp_;
    bool is_continue_{true};
};

}
