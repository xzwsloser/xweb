#include "../../../src/http/server/HttpServer.h"

using namespace xweb;
using namespace std;

int main() {
    HttpServer server;
    server.GET("/hello" , [](HttpContext& ctx) {
        LOG_INFO << "GET执行";

        string body =  
        "<!DOCTYPE html>\r\n"
        "<html>\r\n"
        "<head>\r\n"
        "    <title>xweb</title>\r\n"
        "</head>\r\n"
        "<body>\r\n"
        "    <h1>Run , Success!</h1>\r\n"
        "</body>\r\n"
        "</html>";

        ctx.resp().SetBody(body);
        ctx.resp().SetCode(StatusCode::OK);
        ctx.resp().SetContentType("text/html");
        ctx.resp().SetContentLength(body.size());

        LOG_INFO << "GET执行结束";
    });
    server.Run(8080);
}
