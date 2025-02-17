// @Author: loser
#include "HttpVersion.h"

namespace xweb {

Version HttpVersion::ConverToVersion(const std::string &version)
{
    if(version == "HTTP/1.1") {
        return Version::HTTP_1_1;
    } else if(version == "HTTP/1.0") {
        return Version::HTTP_1_0;
    } else if(version == "HTTP/2.0") {
        return Version::HTTP_2_0;
    } 
    return Version::UNKNOW;
}

std::string HttpVersion::ConverToStr(Version version)
{
    if(version == Version::HTTP_1_1) {
        return "HTTP/1.1";
    } else if(version == Version::HTTP_1_0) {
        return "HTTP/1.0";
    } else if(version == Version::HTTP_2_0) {
        return "HTTP/2.0";
    }
    return "";
}

void HttpVersion::SetVersion(Version version)
{
    version_ = version;
}

Version HttpVersion::GetVersion()
{
    return version_;
}

}
