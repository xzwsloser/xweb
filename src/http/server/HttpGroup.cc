// @Author: loser
#include "HttpGroup.h"
#include "./filter/HttpMethodFilter.h"
#include <initializer_list>

namespace xweb {

HttpGroup::HttpGroup(const std::string& route)
    : route_(route)
{

}

void HttpGroup::RegisterHandler(const std::string& path , HttpMethod method , HttpCallBack callback , std::initializer_list<std::shared_ptr<HttpFilter>> filters)
{
    std::vector<std::shared_ptr<HttpFilter>> fs;
    std::shared_ptr<HttpMethodFilter> hmf(new HttpMethodFilter);
    hmf -> SetMethod(method);
    fs.emplace_back(hmf);

    for(auto& hf : filters) {
        fs.emplace_back(hf);
    }

    std::shared_ptr<HttpTrieData> htd{new HttpTrieData};
    htd -> callback_ = callback;
    htd -> filters_ = fs;
    
    std::string key = route_ + path;
    trie_.Add<HttpTrieData>(key , htd);
}

void HttpGroup::GET(const std::string& key , HttpCallBack callback)
{
    GET(key , callback , {});
}

void HttpGroup::GET(const std::string& key , HttpCallBack callback , std::initializer_list<std::shared_ptr<HttpFilter>> filters)
{
    HttpMethod method; 
    method.SetMethod(Method::GET);
    RegisterHandler(key, method, callback, filters);
}

void HttpGroup::POST(const std::string& key , HttpCallBack callback)
{
    POST(key , callback , {});
}

void HttpGroup::POST(const std::string& key , HttpCallBack callback , std::initializer_list<std::shared_ptr<HttpFilter>> filters)
{
    HttpMethod method;
    method.SetMethod(Method::POST);
    RegisterHandler(key, method, callback, filters);
}

}
