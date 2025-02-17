#include "HttpResp.h"
#include <exception>
#include<vector>
#include "../../utils/StringUtils.h"
#include "status_code/HttpStatusCode.h"
#include "../../logger/Logger.h"

namespace xweb {

int HttpResp::Parse(const std::string& resp)
{
    std::string kCRCF = "\r\n";
    int pos = resp.find(kCRCF + kCRCF);
    std::string context = resp.substr(0 , pos); 
    // \r\n\r\n
    body_ = resp.substr(pos + 2 * kCRCF.size()); 
    pos = context.find(kCRCF); 
    std::string respLine = context.substr(0 , pos);
    std::string headerStr = context.substr(pos + kCRCF.size());
    std::vector<std::string> resps; 
    StringUtils::Split(respLine , " " , resps); 
    version_.SetVersion(HttpVersion::ConverToVersion(resps[0]));
    int code;
    try {
        code = std::stoi(resps[1]);
    } catch(std::exception& e) {
        LOG_ERROR << "status is not a number!";
        return kLogicerr;
    }

    code_.SetCode(HttpStatusCode::CoverToCode(code));
    header_.Parse(headerStr);

    return kSuccess; 
}

std::string HttpResp::ToString() 
{
    std::string kCRCF = "\r\n";
    std::string respLine = version_.ToString() + " " + 
        std::to_string(static_cast<int>(code_.GetCode())) + " " + 
        HttpStatusCode::CoverToStr(code_.GetCode());

    std::string resp = respLine + kCRCF + header_.ToString() + kCRCF + kCRCF + body_;

    return resp;
}

}
