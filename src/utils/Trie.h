// @Author: loser
#pragma once
#include <any>
#include<string>
#include<memory>
#include<functional>
#include<vector>
#include "const.h"

namespace xweb {

class Trie {
public:
    Trie() = default;
    ~Trie();
    
    struct TrieNode {
        std::vector<struct TrieNode*> son_{128,nullptr}; 
        bool is_end_{false};
        std::any data_;
    };
    
    template<typename T>
    int Add(const std::string& key , std::shared_ptr<T> data) 
    {
        return AddNode(key , data);
    }

    template<typename T>
    std::shared_ptr<T> Get(const std::string& key) const
    {
        return std::any_cast<std::shared_ptr<T>>(GetNode(key) -> data_);
    }

    template<typename T>
    bool Search(const std::string& key , std::function<bool(std::shared_ptr<T>)> callback) const
    {
        return SearchNode(key , [callback](const TrieNode* node) -> bool {
            return callback(std::any_cast<std::shared_ptr<T>>(node -> data_));
        });        
    }

    void CleanMemory(TrieNode* root);
    void Reset();

private:
    TrieNode* root_{nullptr};

    int AddNode(const std::string& key , std::any data);
    const TrieNode* GetNode(const std::string& key) const;
    bool SearchNode(const std::string& key , std::function<bool(const TrieNode*)> callback) const;

};

}
