#include "../../../src/http/resp/HttpResp.h"
#include<iostream>
using namespace xweb;
using namespace std;

int main() {
    string httpResponse = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 48\r\n"
        "\r\n"
        "<html><body><h1>Hello, World!</h1></body></html>";
    HttpResp resp;
    auto res = resp.Parse(httpResponse);
    if(res != kSuccess) {
        cout << "转换失败" << endl; 
    }

    cout << resp.GetHeader()["Content-Type"] << endl;
    cout << resp.GetHeader()["Content-Type"] << endl;

    resp.GetHeader().Set("abc" , "abc");

    cout << "===version===" << endl; 
    cout << resp.GetVersion().ToString() << endl;
    cout << "===status code===" << endl;
    cout << resp.GetCode().ToString() << endl;
    cout << "===header===" << endl;
    cout << resp.GetHeader().ToString() << endl;
    cout << "===body===" << endl;
    cout << resp.GetBody() << endl;
    cout << "============" << endl;
    cout << resp.ToString() << endl;
}


