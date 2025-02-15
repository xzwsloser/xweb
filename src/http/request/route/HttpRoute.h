// @Author: loser
#pragma once
#include<string>
#include<unordered_map>

// example: /hello/go?key1=value1&key2=value2&key3=value3

namespace xweb {

class HttpRoute {
public:
    HttpRoute() = default; 
    ~HttpRoute() = default;

    void Parse(const std::string& path);

    void SetPath(const std::string& path);
    std::string GetPath();

    void SetParam(const std::string& key , const std::string& value); 
    std::string GetParam(const std::string& key); 

    std::string ToString();

private:
    std::string path_;
    std::unordered_map<std::string,std::string> params_;
};

}
