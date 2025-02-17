#include "../../../src/http/server/HttpServer.h"

using namespace xweb;
using namespace std;

int main() {
    HttpServer server;
    server.GET("/hello" , [](HttpContext& ctx) {
        ctx.resp().SetBody("hello world");
    });
    server.Run(8080);
}
