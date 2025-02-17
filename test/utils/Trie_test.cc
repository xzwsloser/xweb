#include "../../src/utils/Trie.h"
#include<iostream>
#include<functional>

using namespace xweb;
using namespace std;

using CallBack = function<void()>;

// TM 的空指针,排查2个小时 ...

class Data {
public:
    Data(CallBack cb): cb_(std::move(cb)) {}
    CallBack cb_;
};

int main() {
    Trie trie;

    function<void()> data = []() {
        cout << "终于找到我了..." << "1" << endl;
    };

    function<void()> data1 = []() {
        cout << "终于找到我了..." << "2" << endl;
    };
    
    std::shared_ptr<Data> d = make_shared<Data>(data);
    std::shared_ptr<Data> d1 = make_shared<Data>(data1);

    cout << "是否执行1" << endl;
    trie.Add<Data>("/hello" , d);
    cout << "是否执行..." << endl;
    trie.Add<Data>("/hello/world" , d1);

    cout << "==1==" << endl;
    if(trie.Search<Data>("/hello" , [](shared_ptr<Data> d) -> bool { return true; }))
    {
        cout << "找到了" << endl;
        shared_ptr<Data> res = trie.Get<Data>("/hello");
        res -> cb_();
    } else {
        cout << "没有找到" << endl;
    }

    cout << "==2==" << endl;
    if(trie.Search<Data>("/hello/hello" , [](shared_ptr<Data> d) -> bool { return true; }))
    {
        cout << "找到了" << endl;
        shared_ptr<Data> res = trie.Get<Data>("/hello");
        res -> cb_();
    } else {
        cout << "没有找到" << endl;
    }
    cout << "===3===" << endl;
    if(trie.Search<Data>("/hello/hello" , [](shared_ptr<Data> d) -> bool { return false; }))
    {
        cout << "找到了" << endl;
        shared_ptr<Data> res = trie.Get<Data>("/hello");
        res -> cb_();
    } else {
        cout << "没有找到" << endl;
    }
    cout << "===4===" << endl;
    if(trie.Search<Data>("/hello/world" , [](shared_ptr<Data> d) -> bool { return true; }))
    {
        cout << "找到了" << endl;
        shared_ptr<Data> res = trie.Get<Data>("/hello/world");
        res -> cb_();
    } else {
        cout << "没有找到" << endl;
    }
}

