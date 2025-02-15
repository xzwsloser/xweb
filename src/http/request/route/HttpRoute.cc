// @Author: loser
#include "HttpRoute.h"
#include "../../../utils/StringUtils.h"
#include<vector>

// example: /hello/go?key1=value1&key2=value2&key3=value3

namespace xweb {

void HttpRoute::Parse(const std::string& path)
{
    int pos = path.find("?");

    if(pos == std::string::npos) {
        path_ = path;
        return ;
    }

    path_ = path.substr(0 , pos);
    std::string context = path.substr(pos + 1); 
    std::vector<std::string> km;
    StringUtils::Split(context , "&" , km);
    for(std::string& str : km) {
        pos = str.find("=");
        std::string key = str.substr(0 , pos);
        std::string value = str.substr(pos + 1);
        params_[key] = value;
    }
}

void HttpRoute::SetPath(const std::string& path)
{
    path_ = path;
}

std::string HttpRoute::GetPath()
{
    return path_;
}

void HttpRoute::SetParam(const std::string& key , const std::string& value)
{
    params_[key] = value;
}

std::string HttpRoute::GetParam(const std::string& key)
{
    return params_[key];
}

std::string HttpRoute::ToString()
{
    if(params_.empty()) {
        return path_;
    }

    std::vector<std::string> km;       
    for(auto& pair : params_) {
        km.emplace_back(std::string(pair.first + "=" + pair.second));
    }

    std::string suffix = StringUtils::Join(km , "&");
    std::string url = "";
    url += (path_ + "?" + suffix);
    return url;
}

}
