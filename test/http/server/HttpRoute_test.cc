#include "../../../src/http/server/HttpGroup.h"
#include<iostream>
#include<functional>
#include<memory>
using namespace xweb;
using namespace std;

int main() {
    HttpGroup g{"/hello"};

    g.GET("/world" , [](HttpContext& ctx) {
            cout << "找到了" << endl;
            cout << ctx.req().GetMethod().ToString() << endl;
            cout << ctx.req().GetBody() << endl;
    });
    
    HttpContext ctx;
    ctx.req().SetBody("<html><body>H1</body></html>");

    ctx.req().SetMethod(Method::GET);

    function<bool(shared_ptr<HttpGroup::HttpTrieData>)>
        cb= 
        [&ctx](shared_ptr<HttpGroup::HttpTrieData> ptr) -> bool {
            for(int i = 0 ; i < ptr -> filters_.size() ; i ++) {
                if(!(ptr -> filters_)[i] -> IsMatch(ctx)) {
                    return false;
                }
            }
            return true;
        };

    if(g.GetTrie().Search("/hello/world", cb)) {
        g.GetTrie().Get<HttpGroup::HttpTrieData>("/hello/world")->callback_(ctx);
    } else {
        cout << "没有找到" << endl;
    }
}
