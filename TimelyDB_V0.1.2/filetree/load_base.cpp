//
// Created by saltfish on 23-4-19.
//
#include "tree_base.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
//using namespace dt::lexer;
//using namespace dt::parser;
//using namespace dt::lexer;
void test_fire(){
    cout<<"assdasd"<<endl;
    string str = "select monitor tabname time:3 conlm,conlm2 file:show1";
//    student *s = new student();
//    Lexer *a = new Lexer("/opt/TIme1.2/TimelyDB/TimelyDB_V0.1.2/test.txt");
    std::shared_ptr<Lexer> lexer(new Lexer(str.c_str(),str.length()));
    std::shared_ptr<Parser> parser(new Parser(lexer));
    auto program = parser->parse_program();

    cout<<program->json();
//
//    auto ps = program->m_statements;
//    for (auto & p : ps)
//    {
//        // 递归构建执行计划
//        evaluator->eval(p, env.get(), root);
//
//        // 递归运行执行计划
//        executor->execute_plan(root);
//
//        root = std::make_shared<dt::execution::RootNode>();
//    }

}