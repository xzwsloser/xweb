// @Author: loser
#pragma once
#include<string>
#include<unordered_map>

// example: /hello/go?key1=value1&key2=value2&key3=value3

namespace xweb {

class HttpRoute {
public:
    HttpRoute() = default; 
private:
    std::string path_;
    std::unordered_map<std::string,std::string> params_;
};

}
