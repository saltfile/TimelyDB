//
// Created by saltfish on 23-4-19.
//
#include "tree_base.h"
//using namespace dt::lexer;
//using namespace dt::parser;
//using namespace dt::lexer;


condition* malloc_sqlcondition(void){
    condition* con;
    con=(condition*)malloc(sizeof(condition));
    memset(con,0,sizeof(condition));
    return con;
}

sql_operation* malloc_sqloperation(void){
    sql_operation* sqlOperation;
    sqlOperation=(sql_operation*)malloc(sizeof(sql_operation));

    sqlOperation->data_list=malloc_sqlcondition();
    return sqlOperation;
}



void test_fire(){
    cout<<"assdasd"<<endl;
    string str = "select monitor tabname time:3 conlm,conlm2 file:show1";
//    student *s = new student();
//    Lexer *a = new Lexer("/opt/TIme1.2/TimelyDB/TimelyDB_V0.1.2/test.txt");
//    std::shared_ptr<Lexer> lexer(new Lexer(str.c_str(),str.length()));
//    std::shared_ptr<Parser> parser(new Parser(lexer));
//    auto program = parser->parse_program();
//
//    cout<<program->json();
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
treenode *check_tree(scan_word *scan){
    int wordlen = get_wordlen(scan);
    treenode *root = NULL;
    sqlitWord head = get_word(scan,0);

    switch (head.num) {
//        case 1:
//            log_info("查询语句");
//            root = init_sel();
//            sql_sel(scan,root);
//            break;
//        case 2:
//            log_info("插入语句");
//            root = init_ins();
//            sql_ins(scan,root);
//            break;
//        case 22:
//            root = check_create(scan,root);
//            break;
        case 25:
            root = init_use();
            sql_use(scan,root);
            break;
        default:
            cout<<"错误，语句存在违规语法";
            break;
    }

    return root;
}
void add_list(tree_list *root,treenode *node){
    tree_list *p = root;

    if(p->tree == NULL){
        p->tree = node;
        return;
    }
    while (p->next){
        p = p->next;
    }
    tree_list *newnode = (struct tree_list*)malloc(sizeof(tree_list));
    newnode->tree = node;
    newnode->next = NULL;
    p->next = newnode;
    newnode->prev = p;
}

treenode *init_use(){
    treenode *node1 = (treenode *)malloc(sizeof(treenode));
    memset(node1,0,sizeof(treenode));
    node1->strtype = 25;
    node1->str = "use";
    node1->strlen = strlen(node1->str);
    treenode *node2 = (treenode *)malloc(sizeof(treenode));
    memset(node2,0,sizeof(treenode));
    node2->strtype = 100;
    node2->str = "xxx";
    node2->strlen = strlen(node2->str);
    node1->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node1->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node2);
    return node1;
}

void sql_use(scan_word *scan,treenode *root){
    treenode *p = root;
    tree_list * sel = p->nodelist;
    treenode *sql = sel->tree;
    int arrlen = 1;
    int wordlen = get_wordlen(scan);
    if (wordlen < arrlen || wordlen > 2){
        root = NULL;
        return;
    }
    sqlitWord word = get_word(scan,arrlen);
    if (word.num == sql->strtype){
        sql->str = str_copy(sql->str,word.arr);
        sql->strlen = strlen(sql->str);
    } else {
        cout<<"错误：数据库名错误或为空";
    }
}



char* use_memte(treenode *root){
    char* res;
    sql_operation* use_dataname=malloc_sqloperation();
    use_dataname->handler=USE;
    use_dataname->name = root->nodelist->tree->str;
    bool b =  use_database(root->nodelist->tree->str);

    if (b){
        res = "OK!! Database selected for ";
        char* name = root->nodelist->tree->str;
        res = str_marge(res,name);
    } else{

        res = "Not found Database ";
        char* name = root->nodelist->tree->str;
        res = str_marge(res,name);
    }
    return res;
}



char* use_handle(char* sentence){
    char** sent = str_spilt(sentence,"\n");
    scan_word *words = scanWordInit();
    sqlsacnner(words,sent[0]);
    treenode *use = check_tree(words);
    if (use){
        char *res = use_memte(use);
        return res;
    } else{
        char* res = "Use syntax error";
        return res;
    }

}














