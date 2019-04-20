#include <iostream>
#include "util.hpp"
#include <jsoncpp/json/json.h>
#include "compile.hpp"

int main() {
    Json::Value req;
    req["code"] = "#include <stdio.h> \n int main() {printf(\"hello\");return 0;}";
    req["stdin"] = "";
    Json::Value resp;
    Compiler::CompileAndRun(req , &resp);
    Json::FastWriter writer;
    LOG(INFO) << writer.write(resp) << std::endl;
    return 0;
}
