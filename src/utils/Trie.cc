// @Author: loser
#include "Trie.h"
#include "const.h"
#include<vector>

namespace xweb {

void Trie::CleanMemory(TrieNode* root)
{
    if(!root) return ; 
    for(int i = 0 ; i < (root -> son_).size(); i ++) {
        if(root -> son_[i] != nullptr) {
            CleanMemory(root -> son_[i]);
        }
    } 

    delete root;
    root = nullptr;
}

void Trie::Reset()
{
    CleanMemory(root_);
}

Trie::~Trie()
{
    CleanMemory(root_);
    root_ = nullptr;
}

int Trie::AddNode(const std::string& key , std::any data)
{
    if(root_ == nullptr) root_ = new TrieNode;
    auto ptr = root_;
    for(int i = 0 ; i < key.size() ; i ++) {

        if(static_cast<int>(key[i]) >= 128) {
            return kLogicerr;
        }

        if((ptr -> son_)[static_cast<int>(key[i])] == nullptr) {
            (ptr -> son_)[key[i]] = new TrieNode;
        }

        ptr = ptr -> son_[key[i]];

        if(i == key.size() - 1) {
            ptr -> is_end_ = true;
            ptr -> data_ = data;
            return kSuccess;
        }
    }
    return kSuccess;
}

const Trie::TrieNode* Trie::GetNode(const std::string& key) const
{
    if(key.empty()) return nullptr;

    auto ptr = root_;
    for(int i = 0 ; i < key.size() ; i ++) {
        if(ptr -> son_[key[i]] != nullptr) {
            ptr = ptr -> son_[key[i]];
        } else {
            return nullptr;
        } 
        
        if(i == key.size() - 1) {
           if(ptr -> is_end_) {
               return ptr;
           } 
        }
    }
    return nullptr;
}

bool Trie::SearchNode(const std::string& key , std::function<bool(const TrieNode*)> callback) const
{
    if(key.empty()) return false;
    if(root_ == nullptr) return false;

    auto ptr = root_;
    for(int i = 0 ; i < key.size() ; i ++) {
        if(ptr -> son_[key[i]] != nullptr) {
            ptr = ptr -> son_[key[i]];
        } else {
            return false;
        }

        if(i == key.size() - 1) {
            if((ptr -> is_end_) && callback(ptr)) {
                return true;
            }
        }
    }
    return false;
}

}
