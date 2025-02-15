#include "../../../src/http/request/HttpReq.h"
#include<iostream>

using namespace xweb;
using namespace std;

int main() {
    std::string httpRequest = 
    "POST /submit-form?key1=value1&key2=value2 HTTP/1.1\r\n"
    "Host: www.example.com\r\n"
    "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
    "Accept-Language: en-US,en;q=0.5\r\n"
    "Accept-Encoding: gzip, deflate, br\r\n"
    "Connection: keep-alive\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 51\r\n"
    "\r\n"
    "<html><body><h1>Example HTML Content</h1></body></html>";

    HttpReq req;
    req.Parse(httpRequest);
    cout << "==Method=="<< endl;
    cout << req.GetMethod().ToString() << endl;
    cout << "==route==" << endl;
    cout << req.GetRoute().ToString() << endl;
    cout << "==version==" << endl;
    cout << req.GetVersion().ToString() << endl;
    cout << "==header==" << endl;
    cout << req.GetHeader().ToString() << endl;
    cout << "==body==" << endl;
    cout << req.GetBody() << endl;
    
    cout << "=============" << endl;

    cout << req.ToString() << endl;
}
