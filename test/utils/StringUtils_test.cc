// @Author: loser
#include "../../src/utils/StringUtils.h"
#include <string>
#include<iostream>
#include <vector>
using namespace std;
using namespace xweb;

int main() {
    string a = "1,2,3,4,5,6,7";
    vector<string> res;
    StringUtils::Split(a, ",", res);
    for(string& s : res) cout << s << " ";
    cout << endl;

    std::string request = 
    "GET /hello/index.jsp HTTP/1.1\r\n"
    "Host: localhost\r\n"
    "User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:5.0) Gecko/20100101 Firefox/5.0\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: zh-cn,zh;q=0.5\r\n"
    "Accept-Encoding: gzip, deflate\r\n"
    "Accept-Charset: GB2312,utf-8;q=0.7,*;q=0.7\r\n"
    "Connection: keep-alive\r\n"
    "Cookie: JSESSIONID=369766FDF6220F7803433C0B2DE36D98\r\n";

    vector<string> headers; 
    StringUtils::Split(request , "\r\n" , headers);
    for(string& s : headers) {
        cout << s ;
    }
    cout << endl;

    vector<string> va{"1" , "2" , "3" , "4" , "5"};
    cout << StringUtils::Join(va , "--") << endl;;
} 
