// @Author: loser
#pragma once
#include "../../utils/StringUtils.h"
#include <unordered_map>
#include "../../utils/const.h"

namespace xweb {

class HttpHeader {
public:
    HttpHeader() = default;
    ~HttpHeader() = default;

    enum class ContextType {
       kTextHtml,           // text/html 
       kTextPlain,          // test/plain
       kApplicationJson,    // application/json
       kApplicationXml,     // application/xml
       kMultipartFormData,  // mulitpart/form-data
       kImgPng,             // image/png
       kImgJpeg,            // image/jpeg
       kImgGif,             // image/gif
       UNKNOW
    };

    int Parse(const std::string& origin);

    void Set(const std::string& key , const std::string& value);
    std::string Get(const std::string& key);
    std::string operator[](const std::string& key);

    std::string ToString();

private:
    std::pmr::unordered_map<std::string,std::string> headers_;
};

}
