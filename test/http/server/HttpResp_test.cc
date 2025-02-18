#include "../../../src/http/context/HttpContext.h"
#include<iostream>

using namespace xweb;
using namespace std;

int main() {
    HttpContext ctx;

    ctx.resp().SetBody("hello world");
    ctx.resp().SetContentLength(11);
    ctx.resp().SetContentType("text/plain");
    ctx.resp().SetVersion(Version::HTTP_1_1);
    ctx.resp().SetCode(StatusCode::OK);

    cout << ctx.resp().ToString() << endl;

}
