#include<iostream>
#include<memory>
#include "../../pool/MemoryPool.h"

// MemoryPool and std::shared_ptr

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

int main()
{
    std::shared_ptr<Person> p1{newElement<Person>(1,"zhangsan") , deleteElement<Person>};
    std::cout << "id = " << p1 -> id_ << " name = " << p1 -> name_ << std::endl;
    return 0;
}
