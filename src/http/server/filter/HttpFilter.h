// @Author: loser
#pragma once
#include "../../context/HttpContext.h"

namespace xweb {

class HttpFilter {
public:
    virtual bool IsMatch(HttpContext& ctx) = 0;
    virtual ~HttpFilter() = default;
};

}
