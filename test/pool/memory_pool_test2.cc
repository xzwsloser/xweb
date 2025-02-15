#include<iostream>
#include<memory>
#include<vector>
#include "../../pool/MemoryPool.h"
#include<thread>
#include <chrono>
#include<thread>

using namespace std;

class Person {
public:
    int id_;
    std::string name_;
public:
    Person(int id,std::string name): id_(id) , name_(name)
    {
        std::cout << "构造函数调用" << std::endl;
    }

    ~Person()
    {
        std::cout << "析构函数调用" << std::endl;
    }
};


void thread_func(int i)
{
    shared_ptr<Person> p{newElement<Person>(i,"lisi") , deleteElement<Person>};
    this_thread::sleep_for(chrono::seconds(10));
}

int main()
{
    vector<thread> threads; 
    for(int i = 0 ; i < 100 ; i ++) {
        threads.emplace_back(thread_func , i);
    }

    for(int i = 0 ; i < 100 ; i ++) {
        threads[i].join();
    }
}
