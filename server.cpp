#include "httplib.h"
#include "compile.hpp"

int main() {
    using namespace httplib;
    Server server;

    // Get 给 server 注册一个回调函数，这个函数的调用时机，
    // 处理 Get 方法的时候
    // lambda 表达式？  匿名函数(一次性函数)
    // 路由
    server.Post("/comepile" , [](const Request& req , Response& resp){
        (void)req;
        // 根据具体问题场景，根据请求，计算出响应结果
        // TODO 如何从 req 中获取到 json 请求，json 如何和 http 协议结合，
        // json 如何进行解析和构造 ？json 的第三方库?

        // 需要的请求格式是json 格式，而 http 能够提供的格式，是另一种键值对的格式，所以此处要进行格式的转换
        // 此处由于提交的代码中可能包含一些特殊符号，这些特殊符号要想正确传输，就需要进行转义。浏览器会自动帮我们完成
        // 服务器收到请求之后,解析这个数据整理出需要的 json 格式
        // 键值对，用哪个数据结构表示？ STL容器
        std::unordered_map<std::string , std::string> body_kv;
        UrlUtil::ParseBody(req.body , &body_kv);

        // 在这里调用 CompileAndRun
        Json::Value req_json; // 从 req 对象中获取
        //for (std::unordered_map<std::string , std::string>::iterator it = body_kv.begin() ; it != body_kv.end() ; ++it) {
        //  req_json[it->first] = it->second;
        //}
        
        // auto 自动类型推倒
        // range based for 
        for (auto p : body_kv) {
            // p 的类型和 *it 得到的类型是一致的，it 是迭代器
            req_json[p.first] = p.second;
        }
        Json::Value resp_json; // resp_json 放到响应中
        Compiler::CompileAndRun(req_json , &resp_json);
        // 需要把 Json::Value 对象序列化成一个字符串，才能返回
        Json::FastWriter writer;
        resp.set_content(writer.write(resp_json) , "test/plain");
    });
    // 加上这个目录是为了让浏览器可以访问到一个静态页面。
    // 静态页面：index.html 不会发生变化
    // 动态页面：编译结果，随着参数的不同而发生变化
    server.set_base_dir("./wwwroot");
    server.listen("0.0.0.0" , 9092);
    return 0;
}
