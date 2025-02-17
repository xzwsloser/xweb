// @Author: loser
#include "HttpMethodFilter.h"

namespace xweb {

bool HttpMethodFilter::IsMatch(HttpContext& ctx) 
{
    return ctx.req().GetMethod().ToString() == method_.ToString();
}

}
