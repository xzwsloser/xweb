// @Author: loser
#include "HttpHeader.h"
#include "../../logger/Logger.h"
#include<vector>

namespace xweb {

int HttpHeader::Parse(const std::string& origin)
{
    if(origin.empty()) {
       LOG_WARN << "the header is empty!"; 
       return kLogicerr;
    }

    std::vector<std::string> headerStrs;    
    StringUtils::Split(origin , "\r\n" , headerStrs);
    for(std::string& str : headerStrs) {
        int pos = str.find(":");
        std::string key = str.substr(0 , pos);
        pos ++; 
        while(str[pos] == ' ') pos ++;
        std::string value = str.substr(pos);
        headers_[key] = value;
    }

    return kSuccess;
}

void HttpHeader::Set(const std::string& key , const std::string& value)
{
    headers_[key] = value;
}

std::string HttpHeader::Get(const std::string& key)
{
    return headers_[key];
}

std::string HttpHeader::operator[](const std::string& key)
{
    return headers_[key];
}

std::string HttpHeader::ToString()
{
    std::vector<std::string> result;
    for(auto& pair : headers_) {
        std::string temp = pair.first + ": " + pair.second;
        result.push_back(temp);
    }
    return StringUtils::Join(result , "\r\n"); 
}

}
