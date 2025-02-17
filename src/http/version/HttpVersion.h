// @Author: loser
#pragma once
#include<string>

namespace xweb {

enum class Version {
        HTTP_1_0,
        HTTP_1_1,
        HTTP_2_0,
        UNKNOW
};

class HttpVersion {
public:
    HttpVersion() = default;
    ~HttpVersion() = default;

    static Version ConverToVersion(const std::string& version);
    static std::string ConverToStr(Version version);
    void SetVersion(Version version);
    Version GetVersion();

    std::string ToString() { return ConverToStr(version_); }

private:
    Version version_;
};

}
