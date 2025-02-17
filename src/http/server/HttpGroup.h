// @Author: loser
#pragma once
#include <initializer_list>
#include<string>
#include "../req/route/HttpRoute.h"
#include "../context/HttpContext.h"
#include "../server/filter/HttpFilter.h"
#include "../../utils/Trie.h"
#include<functional>
#include<vector>

namespace xweb {

/*
 *  HttpGroup 的作用就是路由
 *  也就是需要一个路由对象
 */

class HttpGroup {
public:
    using HttpCallBack = std::function<void(HttpContext&)>;
    HttpGroup(const std::string& route);
    HttpGroup() = default;

    // the data of trie node
    struct HttpTrieData {
        std::vector<std::shared_ptr<HttpFilter>> filters_;
        HttpCallBack callback_;
    };

    std::string GetRoute() { return route_; }
    void SetRoute(const std::string& route) { route_ = route; }

    void RegisterHandler(const std::string& path , HttpMethod method , HttpCallBack callback , std::initializer_list<std::shared_ptr<HttpFilter>> filters);

    void GET(const std::string& key , HttpCallBack callback , 
            std::initializer_list<std::shared_ptr<HttpFilter>> filters);

    void GET(const std::string& key , HttpCallBack callback);

    void POST(const std::string& key , HttpCallBack callback , 
            std::initializer_list<std::shared_ptr<HttpFilter>> filters);

    void POST(const std::string& key , HttpCallBack callback);

    Trie& GetTrie() { return trie_; }

protected:
    std::string route_{""};
    Trie trie_;
};

}
