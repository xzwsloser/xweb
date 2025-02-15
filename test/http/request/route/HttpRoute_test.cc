#include "../../../../src/http/request/route/HttpRoute.h"
#include<iostream>

using namespace xweb;
using namespace std;

int main() {
    string url = "/hello/hello?key1=value1&key2=value2&key3=value3";
    HttpRoute hp;
    hp.Parse(url);
    cout << hp.GetParam("key1") << endl;
    hp.SetParam("key4", "value4");
    string res = hp.Build();
    cout << res << endl;
}
