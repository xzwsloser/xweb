#include "../../../src/http/header/HttpHeader.h"
#include<iostream>

using namespace xweb;
using namespace std;

int main() {
    HttpHeader hh;
    std::string request = 
    "Host: localhost\r\n"
    "User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:5.0) Gecko/20100101 Firefox/5.0\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: zh-cn,zh;q=0.5\r\n"
    "Accept-Encoding: gzip, deflate\r\n"
    "Accept-Charset: GB2312,utf-8;q=0.7,*;q=0.7\r\n"
    "Connection: keep-alive\r\n"
    "Cookie: JSESSIONID=369766FDF6220F7803433C0B2DE36D98";
    
    hh.Parse(request);
    cout << hh["Host"] << endl;
    cout << hh.Get("User-Agent") << endl;;

    hh.Set("aaa" , "abc"); 
    cout << hh.Build() << endl;

}
