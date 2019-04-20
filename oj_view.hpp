//#pragma once
// google 的一个开源库
#include <ctemplate/template.h>
#include "oj_model.hpp"

class OjView {
public:
    // 根据实际，生成 html 这个动作，通常叫做 页面渲染（render）
    static void RenderAllQuestions(const std::vector<Question>& all_questions , std::string* html) {
        // 这个函数帮我们 把所有的题目数据 转换成 题目列表页 html
        // 在这个 C++ 代码中直接通过字符串拼接的方式构造 html
        // 通过网页模板的方式解决问题
        // 模板类似于填空题，事先准备好一个 html 把其中一些需要动态计算的数据挖个空留出来，
        // 处理请求过程中，根据计算结果来填这个空
        
        // 1.先创建一个 ctemplate 的对象，这是一个总的组织数据的对象
        // 2.循环的往这个对象中添加一些子对象
        // 3.每一个子对象再设置一些键值对（和模板中留下的{{}}是要对应的）
        // 4.进行数据的替换，生成最终的 html
        ctemplate::TemplateDictionary dict("all_questions");
        for (const auto& question : all_questions) {
            ctemplate::TemplateDictionary* table_dict = dict.AddSectionDictionary("question");
            table_dict->SetValue("id" , question.id);
            table_dict->SetValue("name" , question.name);
            table_dict->SetValue("level" , question.level);
        }

        ctemplate::Template* tpl;
        tpl = ctemplate::Template::GetTemplate("./template/all_questions.html", ctemplate::DO_NOT_STRIP);
        tpl->Expand(html, &dict);

    }

    static void RenderQuestion(const Question& question) {
        ctemplate::TemplateDictionary dict("question");
        dict.SetValue("id" , question.id);
        dict.SetValue("name" , question.name);
        dict.SetValue("level" , question.level);
        dict.SetValue("desc" , question.desc);
        dict.SetValue("header" , question.header_cpp);

        ctemplate::Template* tpl;
        tpl = ctemplate::Template::GetTemplate("./template/questions.html", ctemplate::DO_NOT_STRIP);
        tpl->Expand(html, &dict);

    }
};

