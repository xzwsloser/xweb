// @Author: loser
#include "HttpReq.h"
#include "../../utils/StringUtils.h"

namespace xweb {

void HttpReq::Parse(const std::string& req)
{
    std::string kCRCF = "\r\n";
    int pos = req.find(kCRCF + kCRCF);
    body_ = req.substr(pos + 2 * kCRCF.size());
    std::string context = req.substr(0 , pos);
    pos = context.find(kCRCF);
    std::string reqLine = context.substr(0 , pos);
    std::string headerStr = context.substr(pos + kCRCF.size());

    std::vector<std::string> options;   
    StringUtils::Split(reqLine , " " , options);

    method_.SetMethod(HttpMethod::CovertToMethod(options[0]));
    version_.SetVersion(HttpVersion::ConverToVersion(options[2]));
    route_.Parse(options[1]);
    header_.Parse(headerStr);
}

std::string HttpReq::ToString()
{
    std::string kCRCF = "\r\n";
    std::string reqLine = method_.ToString() + " " + route_.ToString() + " " + version_.ToString() + kCRCF;
    std::string headerStr = header_.ToString() + kCRCF + kCRCF; 
    std::string req = reqLine + headerStr + body_;
    return req;
}

}
