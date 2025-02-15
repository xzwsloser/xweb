// @Author: loser
#pragma once
#include<string>
#include<vector>

namespace xweb {

class StringUtils {
public:
    StringUtils() = delete;
    ~StringUtils() = delete;
    static void Split(const std::string& origin , 
            const std::string& delimter ,
            std::vector<std::string>& result , bool keep_delimter = false); 

    static std::string Join(const std::vector<std::string>& target, 
            const std::string& delimter);
};

}
