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

colnm *get_andcolum(scan_word *scan,int len){
    int end = len;
    if(len+3 > scan->nowlen){
        colnm *c = (colnm *)malloc(sizeof(colnm));
        c->type = -235;
        return c;
    }
    for(int i = len;i < len+3;i++){
        if(scan->word[i].num == 10||scan->word[i].num == 11){
            colnm *c = (colnm *)malloc(sizeof(colnm));
            c->type = -234;
            return c;
        } else{
            end++;
        }
    }
    int get_strlen = 1;

    for(int i = len;i < end;i++){
        get_strlen += strlen(scan->word[i].arr);
        get_strlen++;
    }
    char res[get_strlen];
    memset(res,0,get_strlen);
    for(int i = len;i < end;i++){
        strcat(res,scan->word[i].arr);
        strcat(res," ");
    }
    res[get_strlen-1] = '\0';

    char *str = (char *)malloc(sizeof(get_strlen));
    memcpy(str,res,get_strlen);
    colnm *p = (colnm *)malloc(sizeof(colnm));
    p->end = end;
    p->str = str;
    p->type = 254;
    p->start = 1;
    return p;

}

colnm *get_colnm(scan_word *scan){
    int arr = 0;

    for(int i = 1;i < scan->nowlen;i++){
        if(scan->word[i].num != 4){
            arr++;
        } else{
            break;
        }
    }
    int get_len = 1;

    for(int i = 1;i <= arr;i++){
        get_len += strlen(scan->word[i].arr);
    }
    char res[get_len];
    memset(res,0,get_len);
    for(int i = 1;i <= arr;i++){
        strcat(res,scan->word[i].arr);
    }
    res[get_len-1] = '\0';

    char *str = (char *)malloc(sizeof(get_len+1));
    memcpy(str,res,get_len+1);
    colnm *p = (colnm *)malloc(sizeof(colnm));
    p->end = arr;
    p->str = str;
    p->type = 256;
    p->start = 1;
    return p;
}

void test_fire(){
    cout<<"assdasd"<<endl;
    string str = "monitor tabname time:3 conlm,conlm2 file:show1";
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
        case 1:
            root = init_sel();
            sql_sel(scan,root);
            break;
        case 2:
            root = init_ins();
            sql_ins(scan,root);
            break;
        case 22:
            root = check_create(scan,root);
            break;
        case 25:
            root = init_use();
            sql_use(scan,root);
            break;
        case 31:
            root = init_mointor();
            sql_mointor(scan,root);
            break;

        default:
            cout<<"错误，语句存在违规语法";
            break;
    }

    return root;
}

treenode *init_create_db(){
    treenode *node1 = (treenode *)malloc(sizeof(treenode));
    memset(node1,0,sizeof(treenode));
    node1->strtype = 23;
    node1->str = "database";
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


void sql_create_db(scan_word *scan,treenode *root){
    treenode *p = root;
    tree_list * sel = p->nodelist;
    treenode *sql = sel->tree;
    int arrlen = 2;
    int wordlen = get_wordlen(scan);
    if (wordlen < arrlen){
        root = NULL;
        return;
    }
    sqlitWord word = get_word(scan,arrlen);
    if (word.num == sql->strtype){
        sql->str = str_copy(sql->str,word.arr);
        sql->strlen = strlen(sql->str);
    } else {
        cout<<"错误：数据库名错误或为空"<<endl;
    }


}

treenode *init_create_tb(){
    treenode *node1 = (treenode *)malloc(sizeof(treenode));
    memset(node1,0,sizeof(treenode));
    node1->strtype = 24;
    node1->str = "table";
    node1->strlen = strlen(node1->str);
    treenode *node2 = (treenode *)malloc(sizeof(treenode));
    memset(node2,0,sizeof(treenode));
    node2->strtype = 100;
    node2->str = "xxx";
    node2->strlen = strlen(node2->str);
    node1->nodelist = (tree_list*)malloc(sizeof(tree_list));
    memset(node1->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node2);
    return node1;
}

int base_type_syntax(scan_word *scan,int start){
    int res = start+1;
    sqlitWord word = get_word(scan,res);
    //首先测试类型
    if (word.num == 26 ||word.num == 27||word.num == 28||word.num == 29){
        return res;
    } else if (word.num == 30){
        res+=1;
        if (res >= get_wordlen(scan))return -2;
        word = get_word(scan,res);
        if (word.num != 40)return -1;
        res+=1;
        word = get_word(scan,res);
        if (word.num != 200) return -1;
        res+=1;
        word = get_word(scan,res);
        if (word.num != 41)return -1;
        return res;
    } else return -2;
}




void sql_create_tb(scan_word *scan,treenode *root){
    treenode *p = root;
    tree_list * sel = p->nodelist;
    treenode *sql = sel->tree;
    int arrlen = 2;
    int wordlen = get_wordlen(scan);
    if (wordlen < arrlen){
        root = NULL;
        return;
    }
    sqlitWord word = get_word(scan,arrlen);
    if (word.num == sql->strtype){
        sql->str = str_copy(sql->str,word.arr);
        sql->strlen = strlen(sql->str);
    } else {
        cout<<"错误：表名错误或为空"<<endl;
    }
    //重写部分
    //分词指针继续往下走
    word = get_word(scan,++arrlen);
    if (word.num == 40) {
        arrlen++;
        while (true) {
            if (arrlen > get_wordlen(scan))break;
            word = get_word(scan, arrlen);
            if (word.num == 100) {
                int end = base_type_syntax(scan, arrlen);
                treenode *new_node = (treenode *) malloc(sizeof(treenode));
                memset(new_node, 0, sizeof(treenode));
                new_node->strtype = 259;
                new_node->nodelist = branch_259(scan, arrlen, end);
                add_list(sel, new_node);
                arrlen = end;
                arrlen++;
                word = get_word(scan,arrlen);
                if (word.num == 44){
                    arrlen++;
                    continue;
                }
                if (word.num == 41){
                    int all = get_wordlen(scan);
                    if (all > arrlen+1){
                        cout<<"末尾检测到违法字符"<<endl;
                        free(p);
                        break;
                    }else{
                        break;
                    }
                }
            } else {
                cout<<"表列名与表列类型之间有语法错误"<<endl;
                free(p);
                break;}
        }
    }
    else{
        cout<<"语句缺少 \"()\""<<endl;
        free(p);
    }

}



treenode *check_create(scan_word* scan,treenode *root){
    int arrlen = 1;
    sqlitWord word = get_word(scan,arrlen);

    //判断是创建数据库还是创建表单
    switch (word.num) {
        case 23:
            cout<<"建库语句"<<endl;
            root = init_create_db();
            sql_create_db(scan,root);
            break;
        case 24:
            cout<<"建表语句"<<endl;
            root = init_create_tb();
            sql_create_tb(scan,root);
            break;
        default:
            cout<<"错误:语法创建库表参数有误"<<endl;
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

int get_list_size(tree_list *root){
    int res  = 0;
    tree_list *p= root;
    while (p->next){
        res++;
        p=p->next;
    }
    return ++res;
}


treenode *init_mointor(){


    treenode *node1 = (treenode *)malloc(sizeof(treenode));
    memset(node1,0,sizeof(treenode));
    node1->strtype = 31;
    node1->str = "mointor";
    node1->strlen = strlen(node1->str);
    //node2是表名称
    treenode *node2 = (treenode *)malloc(sizeof(treenode));
    memset(node2,0,sizeof(treenode));
    node2->strtype = 100;
    node2->str = "tab_name";
    node2->strlen = strlen(node2->str);
    node1->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node1->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node2);
    //node3是time
    treenode *node3 = (treenode *)malloc(sizeof(treenode));
    memset(node3,0,sizeof(treenode));
    node3->strtype = 21;
    node3->str = "time";
    node3->strlen = strlen(node3->str);
    node2->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node2->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node3);
    //node4是":"
    treenode *node4 = (treenode *)malloc(sizeof(treenode));
    memset(node4,0,sizeof(treenode));
    node4->strtype = 58;
    node4->str = ":";//这个只是代替
    node4->strlen = strlen(node4->str);
    node3->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node3->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node4);
    //node5
    treenode *node5 = (treenode *)malloc(sizeof(treenode));
    memset(node5,0,sizeof(treenode));
    node5->strtype = 200;
    node5->str = "1";//这个只是代替
    node5->strlen = strlen(node5->str);
    node4->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node4->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node5);

    //node6
    treenode *node6 = (treenode *)malloc(sizeof(treenode));
    memset(node6,0,sizeof(treenode));
    node6->strtype = 32;
    node6->str = "file";//这个只是代替
    node6->strlen = strlen(node6->str);
    node5->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node5->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node6);
    //:
    treenode *node7 = (treenode *)malloc(sizeof(treenode));
    memset(node7,0,sizeof(treenode));
    node7->strtype = 58;
    node7->str = ":";//这个只是代替
    node7->strlen = strlen(node7->str);
    node6->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node6->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node7);

    treenode *node8 = (treenode *)malloc(sizeof(treenode));
    memset(node8,0,sizeof(treenode));
    node8->strtype = 100;
    node8->str = "test";//这个只是代替
    node8->strlen = strlen(node8->str);
    node7->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node7->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node8);

    treenode *node9 = (treenode *)malloc(sizeof(treenode));
    memset(node9,0,sizeof(treenode));
    node9->strtype = 100;
    node9->str = "test";//这个只是代替
    node9->strlen = strlen(node9->str);
    node8->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node8->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node9);
    return node1;

}






treenode *init_sel(){
    //node1是select//节点type是1
    treenode *node1 = (treenode *)malloc(sizeof(treenode));
    memset(node1,0,sizeof(treenode));
    node1->strtype = 1;
    node1->str = "select";
    node1->strlen = strlen(node1->str);
    //node2是搜索结果*
    treenode *node2 = (treenode *)malloc(sizeof(treenode));
    memset(node2,0,sizeof(treenode));
    node2->strtype = 42;
    node2->str = "*";
    node2->strlen = strlen(node2->str);
    node1->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node1->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node2);
    //node3是from
    treenode *node3 = (treenode *)malloc(sizeof(treenode));
    memset(node3,0,sizeof(treenode));
    node3->strtype = 4;
    node3->str = "from";
    node3->strlen = strlen(node3->str);
    node2->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node2->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node3);
    //node4是表名就是个letter
    treenode *node4 = (treenode *)malloc(sizeof(treenode));
    memset(node4,0,sizeof(treenode));
    node4->strtype = 100;
    node4->str = "xxx";//这个只是代替
    node4->strlen = strlen(node4->str);
    node3->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node3->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node4);
    return node1;
}




//初始化insert
treenode *init_ins(){
    treenode *node1 = (treenode *)malloc(sizeof(treenode));
    memset(node1,0,sizeof(treenode));
    node1->strtype = 2;
    node1->str = "insert";
    node1->strlen = strlen(node1->str);
    treenode *node2 = (treenode *)malloc(sizeof(treenode));
    memset(node2,0,sizeof(treenode));
    node2->strtype = 5;
    node2->str = "into";
    node2->strlen = strlen(node2->str);
    node1->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node1->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node2);
    treenode *node3 = (treenode *)malloc(sizeof(treenode));
    memset(node3,0,sizeof(treenode));
    node3->strtype = 100;
    node3->str = "t_name";
    node3->strlen = strlen(node3->str);
    node2->nodelist = (tree_list *)malloc(sizeof(tree_list));
    memset(node2->nodelist,0,sizeof(tree_list));
    add_list(node1->nodelist,node3);
    return node1;
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







void sql_sel(scan_word *scan,treenode *root){
    root->is_succ = true;
    treenode *p = root;
    tree_list * sel = p->nodelist;
    treenode *sql = sel->tree;
    int arrlen = 1;
    int wordlen = get_wordlen(scan);
    sqlitWord word = get_word(scan,arrlen);
    if(word.num != sql->strtype){
        colnm *s = get_colnm(scan);
        sql->strtype = s->type;
        sql->str = s->str;
        sql->strlen = strlen(sql->str);
        int nums =  s->end-arrlen-1;
        sql->nodelist = branch_256(scan,arrlen,nums);
        arrlen+=s->end;
    }else{
        arrlen += 1;
    }
    sqlitWord wfrom = get_word(scan,arrlen);
    sel = sel->next;
    sql = sel->tree;
    if(wordlen <= arrlen){
        root->is_succ = false;
        return;
    }
    if(wfrom.num == sql->strtype){
        //检测到from并且识别成功开始识别后面的表名
        sel = sel->next;
        sql = sel->tree;
        arrlen++;
    }else{
        //清空并封装一个语句做返回
        return;
    };
    word = get_word(scan,arrlen);
    if(word.num == sql->strtype){
        sql->str = (char *)malloc(sizeof(strlen(word.arr)+1));
        sql->str = str_copy(sql->str,word.arr);
        sql->strlen = strlen(sql->str);
        sql->str += '\0';
    }
    arrlen++;
    if(arrlen >= wordlen){
        //证明后面没东西
        return;
    }
    sqlitWord where_word = get_word(scan,arrlen);
    if(where_word.num == 6){
        treenode *node = (treenode *)malloc(sizeof(treenode));
        memset(node,0,sizeof(treenode));
        node->strtype = 6;
        node->str = (char *)malloc(sizeof(strlen(where_word.arr)+1));

        node->str = where_word.arr;
        node->strlen = strlen(node->str);
        node->str += '\0';
        add_list(sel,node);
        sel = sel->next;
        sql = sel->tree;
        arrlen++;
    } else{
        //这里需要封装错误包
        root->is_succ = false;
    }
    if(wordlen <= arrlen){
        //封装语法错误
        root->is_succ = false;
        return;
    }

    sqlitWord and_word = get_word(scan,arrlen);

    if(and_word.num == 100) {
        while (true){
            //先形成小链表
            colnm *s = get_andcolum(scan,arrlen);
            if(s->type == -234){

                return;
            } else if(s->type == -235){
                root->is_succ = false;
                return;
            }
            int p_len = arrlen;
            treenode *annode = (treenode *) malloc(sizeof(treenode));
            annode->nodelist = (struct tree_list*)malloc(sizeof(tree_list));
            memset(annode->nodelist,0,sizeof(tree_list));

            annode->nodelist = branch_245(scan,arrlen);

            annode->str = s->str;
            annode->strlen = strlen(annode->str);
            annode->strtype = s->type;
            add_list(sel, annode);
            sel = sel->next;
            sql = sel->tree;
            arrlen = s->end;

            if (wordlen <= arrlen) {
                //封装语法错误
                break;
            }

            sqlitWord rela_word = get_word(scan,arrlen);
            if(rela_word.num == 10 || rela_word.num == 11){
                switch (rela_word.num) {
                    case 10:{treenode *newptr = (treenode *) malloc(sizeof(treenode));
                        newptr->strtype = 10;
                        newptr->str = (char *)malloc(sizeof(4));
                        newptr->str = "and";
                        newptr->str+='\0';
                        newptr->strlen = strlen(newptr->str);
                        add_list(sel,newptr);sel = sel->next;
                        sql = sel->tree;arrlen++;} break;

                    case 11:{treenode *newptr = (treenode *) malloc(sizeof(treenode));
                        newptr->strtype = 11;
                        newptr->str = (char *)malloc(sizeof(3));
                        newptr->str = "or";
                        newptr->str+='\0';
                        newptr->strlen = strlen(newptr->str);
                        add_list(sel,newptr);sel = sel->next;
                        sql = sel->tree;arrlen++;}break;
                }
                if (wordlen <= arrlen) {
                    //封装语法错误
                    root->is_succ = false;
                    return;
                }
            }else{
                return;
            }
        }
    } else{
        string str = "语句where后面不可加上: ";
        string  str1 = and_word.arr;
        string sss = str+str1;
        root->is_succ = false;
    }

}









void sql_mointor(scan_word *scan,treenode *root){
    treenode *p = root;
    root->is_succ = true;
    tree_list * sel = p->nodelist;
    treenode *sql = sel->tree;
    int arrlen = 1;
    int wordlen = get_wordlen(scan);
    sqlitWord word = get_word(scan,arrlen);
    //表名赋值
    if (word.num != 100){
        root->is_succ = false;
        return;
    }
    root->handler.tab_name = str_copy("",word.arr);
    arrlen+=2;
    word = get_word(scan,arrlen);



    arrlen++;
    word = get_word(scan,arrlen);

    if (word.num != 200){
        root->is_succ = false;
        return;
    }
    root->handler.time = atoi(word.arr);

    arrlen++;
    word = get_word(scan,arrlen);
    //文件
    if (word.num != 32){
        root->is_succ = false;
        return;
    }
    arrlen+=2;
    word = get_word(scan,arrlen);

    if (word.num != 100){
        root->is_succ = false;
        return;
    }
    root->handler.file = str_copy("",word.arr);

    vector<string> colum;
    arrlen++;
    word = get_word(scan, arrlen);
    colum.push_back(word.arr);
    while (arrlen < wordlen) {
        arrlen+=2;
        word = get_word(scan, arrlen);
        if (word.num != 100){
            break;
        }
        colum.push_back(word.arr);

    }
    root->handler.colums = colum;


}


void sql_ins(scan_word *scan,treenode *root){
    treenode *p = root;
    tree_list * sel = p->nodelist;
    treenode *sql = sel->tree;
    int arrlen = 1;
    int wordlen = get_wordlen(scan);
    sqlitWord word = get_word(scan,arrlen);
    //into
    if(word.num == sql->strtype){
        sel = sel->next;
        sql = sel->tree;
        arrlen++;
    } else{
        cout<<"插入语句错误,缺少into"<<endl;
        return;
    }
    //tname
    word = get_word(scan,arrlen);
    if(word.num == sql->strtype){
        sql->str = str_copy(sql->str,word.arr);
        sql->strlen = strlen(sql->str);
        arrlen++;
    } else{
        cout<<"表名位置，缺少后续语句"<<endl;
        return;
    }

    if(wordlen <= arrlen){
        //封装语法错误
        cout<<"语句残缺"<<endl;
        return;
    }
    //列名字表
    word = get_word(scan,arrlen);
    char *str="\0";
    int col_list = arrlen;
    if(word.num == 40){

        arrlen++;
        while (true){
            if(wordlen <= arrlen){
                //封装语法错误
                cout<<"列表名，语句残缺"<<endl;
                return;
            }
            word = get_word(scan,arrlen);
            if(word.num == 41){
                break;
            }
            str = str_marge(str,word.arr);
            arrlen++;
        }
    } else{
        cout<<"错误，语句不完整"<<endl;
        return;
    }
    tree_list *slist = branch_257(scan,col_list);
    treenode *colomn = (treenode *)malloc(sizeof(treenode));
    memset(colomn,0,sizeof(treenode));
    colomn->str = str;
    colomn->strtype = 257;
    colomn->strlen = strlen(colomn->str);
    colomn->nodelist = slist;
    add_list(sel,colomn);
    sel = sel->next;
    arrlen++;
    int clonm_lens = get_list_size(slist);

    //values
    word = get_word(scan,arrlen);
    if(word.num == 14){
        treenode *valnode = (treenode *)malloc(sizeof(treenode));
        memset(valnode,0,sizeof(treenode));
        valnode->str = str_copy(valnode->str,word.arr);
        valnode->strtype = 14;
        valnode->strlen = strlen(valnode->str);
        add_list(sel,valnode);
        sel = sel->next;
        arrlen++;
    }
    if(wordlen <= arrlen){
        //封装语法错误
        cout<<"语句残缺"<<endl;
        return;
    }


    //values后面的列表
    word = get_word(scan,arrlen);
    while (true){

        if(wordlen <= arrlen){
            break;
        }
        word = get_word(scan,arrlen);
        int val_len = 0;
        char *val_str = "\0";
        if (word.num == 40){
            val_len = arrlen;
            arrlen++;
            while (true){
                if(wordlen <= arrlen){
                    //封装语法错误
                    cout<<"列表名，语句残缺"<<endl;
                    return;
                }
                word = get_word(scan,arrlen);
                if(word.num == 41){
                    break;
                }
                val_str = str_marge(val_str,word.arr);//前继
                arrlen++;
            }
        } else{
            cout<<"语法错误"<<endl;
            return;
        }

        treenode *val_list =  (treenode *)malloc(sizeof(treenode));
        memset(val_list,0,sizeof(val_list));
        val_list->str = str_copy(val_list->str,val_str);
        val_list->strtype = 258;
        val_list->strlen = strlen(val_list->str);
        val_list->nodelist = branch_258(scan,val_len);
        int val_nums = get_list_size(val_list->nodelist);
        if(val_nums != clonm_lens){
            cout<<"值与列不匹配"<<endl;
            return;
        }
        add_list(sel,val_list);
        arrlen++;
        sel = sel->next;
    }
    clear_cache(scan);
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
char * merge_res(vector<string> result){
    char *res = "";
    for (int i = 0; i < result.size(); ++i) {
       char *col = const_cast<char *>(result[i].c_str());
       char *c_r = "";
       char**col_r = str_spilt(col,";");
       int col_size = str_spilt_size(col,";");
        if (strcmp(col_r[0],"nil") == 0)continue;
        for (int j = 0; j < col_size - 1; ++j) {
            c_r = str_marge(c_r,col_r[j]);
            c_r = str_marge(c_r,",");
        }
        c_r = str_marge(c_r,col_r[col_size - 1]);
        c_r = str_marge(c_r,";");
        res = str_marge(res,c_r);
    }
}


char* memte_select(treenode* root){
    tree_list* sql = root->nodelist->next;
    char *result = "";
    char *base_name = is_use_database();
    if (base_name == NULL){
        return "please use with database";
    }
    if (!root->is_succ){
        result = str_copy("","Syntax error");
    }
    sql = sql->next;
    treenode* p = sql->tree;
    char *tab_name = str_copy("",p->str);
    /**
     * select *
     */
    if (sql->next == NULL){
        char*get_col = get_tab_cols(base_name,tab_name);
        result = str_marge(result,get_col);
        result = str_marge(result,"\n");
        vector<string> col_arr = get_DB_data(base_name,tab_name);
        for (int i = 0; i < col_arr.size(); ++i) {
            char *s = const_cast<char *>(col_arr[i].c_str());
            if (strcmp(str_spilt(s,";")[0],"nil") == 0)continue;
            result = str_marge(result,const_cast<char *>(col_arr[i].c_str()));
            result = str_marge(result,"\n");
        }

    } else{
        char*get_col = get_tab_cols(base_name,tab_name);
        vector<string> col_arr = get_DB_data(base_name,tab_name);
        char *y_res = merge_res(col_arr);
        sql = sql->next->next;
        p = sql->tree;
        if (p->strtype == 254){
            tree_list *node = p->nodelist;
            treenode *filed = node->tree;
            char *nus = filed->str;
            node = node->next;
            filed = node->tree;
            int str_type = filed->strtype;
            TokenType type;

            switch (str_type) {
                case 62:type = GT;break;
                case 60:type = LT;break;
                case 61:type = EQ;break;
                case 150:type = GE;break;
                case 160:type = GT;break;
            }

            node = node->next;
            filed = node->tree;
            int num = atoi(filed->str);

            string res = y_res;
//            vector<string> SrceenDatas(res,2,num,type);

        }

    }

    return result;


}
char* memte_insert(treenode* root){
    char *result = NULL;

    tree_list* sql = root->nodelist->next;
    treenode* p = sql->tree;

    sql_operation* insert = malloc_sqloperation();
    insert->handler = INSERTINTO;
    insert->name = str_copy(insert->name,p->str);
    insert->timestamp = 0;
    sql = sql->next;
    char *cols = str_copy("",sql->tree->str);
    char **col_arr = str_spilt(cols,",");
    int col_size = str_spilt_size(cols,",");

    sql = sql->next;
    sql = sql->next;

    char *vals = str_copy("",sql->tree->str);
    char **val_arr = str_spilt(vals,",");
    int val_size = str_spilt_size(vals,",");

    char *tab_name = str_copy("",p->str);
    map<string,string> map_col = get_tab_map_colums(is_use_database(),tab_name);

    for (int i = 0; i < col_size; ++i) {
        string col_key = col_arr[i];
        string val = val_arr[i];
        map_col[col_key] = val;
    }
    string times = "timeStamp";
    string stamp_val = to_string(get_now_timestamp());
    map_col[times] = stamp_val;

    char **push_col = (char **) calloc(map_col.size() , sizeof(char *));
    char **push_val = (char **) calloc(map_col.size(),sizeof(char *));
    int i = 0;
    for (map<string ,string>::iterator it = map_col.begin(); it != map_col.end(); ++it) {
        push_col[i] = str_copy(push_col[i],const_cast<char *>(it->first.c_str()));
        push_val[i] = str_copy(push_val[i],const_cast<char *>(it->second.c_str()));
        i++;
    }
    bool is_success = DB_insert_table(is_use_database(),tab_name,push_col,map_col.size(),push_val,map_col.size());
    if (is_success){
        result = str_copy("","Successfully inserted 1 * row into");
    } else{
        result = str_copy("","Insert Failed table is not exist or lock");
    }

    return result;
}

char* spell_char(char arr,int len){
    char* res = (char*)malloc(len+1);
    memset(res,0,len+1);
    for (int i = 0; i < len; ++i) {
        res[i] = arr;
    }
    return res;
}

char* show_table_panle(){
    char *db_name = is_use_database();

    if (db_name == NULL){
        return "Error: database exception";
    }
    string base_key = db_name;
    vector<string> tab_res = get_any_table(base_key);
    if (tab_res.empty()){
        return "This is Empty";
    }


    char** res_db = (char**)malloc(sizeof(char*)*tab_res.size());
    memset(res_db,0,sizeof(res_db));
    int push_lens = 0;
    for (int i = 0; i < tab_res.size(); ++i) {
        if (tab_res[i].size() > push_lens){
            push_lens = tab_res[i].size();
        }
        res_db[i] = str_copy(res_db[i],const_cast<char *>(tab_res[i].c_str()));
    }
    char* result = NULL;
    char* head = spell_char('*',push_lens+4);
    head = str_marge(head,"\n");
    result = str_copy(result,head);
    for (int i = 0; i < tab_res.size(); ++i) {
        char* start = "* ";
        start = str_marge(start,res_db[i]);
        int cloum_s = push_lens-strlen(res_db[i]);
        int space_s = 1;
        char* space = spell_char(' ',space_s+cloum_s);
        start = str_marge(start,space);
        start = str_marge(start,"*\n");
        start = str_marge(start,head);
        result = str_marge(result,start);
    }

    return result;




}

char*show_database_panle(){
    vector<string> databases = get_any_base();
    if ( databases.size() == 0){
        return "This is empty\n";
    }
    char** res_db = (char**)malloc(sizeof(char*)*databases.size());
    memset(res_db,0,sizeof(res_db));
    int push_lens = 0;

    for (int i = 0; i < databases.size(); ++i) {
        cout<<"=>"<<databases[i]<<endl;
        if (databases[i].size()>push_lens){
            push_lens = databases[i].size();
        }
        res_db[i] = str_copy(res_db[i],const_cast<char *>(databases[i].c_str()));
    }
    char* result = NULL;

    char* head = spell_char('*',push_lens+4);
    head = str_marge(head,"\n");
    result = str_copy(result,head);

    for (int i = 0; i < databases.size(); ++i) {
        char* start = "* ";
        start = str_marge(start,res_db[i]);
        int cloum_s = push_lens-strlen(res_db[i]);
        int space_s = 1;
        char* space = spell_char(' ',space_s+cloum_s);
        start = str_marge(start,space);
        start = str_marge(start,"*\n");
        start = str_marge(start,head);
        result = str_marge(result,start);
    }

    return result;

}



char* show_DB_handle(char* sentence){
    char** sent = str_spilt(sentence,"\n");
    char* res = NULL;
    if (strcmp(sent[0],"show databases") == 0){
        res = show_database_panle();
        return res;
    } else{
        res = "Statement or server error!!";
        return res;
    }

}
char* show_Table_handle(char* sentence){
    char** sent = str_spilt(sentence,"\n");
    if (strcmp(sent[0],"show tables") != 0){
        return "Error: syntax error";
    }
    char* res = NULL;
    res = str_copy(res,show_table_panle());
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


char* deltab_handle(char* sentence){
    char** sent = str_spilt(sentence,"\n");
    scan_word *words = scanWordInit();
    sqlsacnner(words,sent[0]);
    int arrlen = 0;
    sqlitWord word = get_word(words,arrlen);
    if (word.num != 3)return "is not delete word\n";
    arrlen++;
    word = get_word(words,arrlen);
    if (word.num != 24)return "Sytnex error!!\n";

    char *base_name = is_use_database();
    if (base_name == NULL)return "please use a database\n";
    arrlen++;
    word = get_word(words,arrlen);


}





char* insert_handle(char* sentence){
    char** sent = str_spilt(sentence,"\n");
    scan_word *words = scanWordInit();
    sqlsacnner(words,sent[0]);
    scan_word* iword = scanWordInit();
    sqlsacnner(iword,sent[0]);
    treenode *create = check_tree(iword);
    char* res = NULL;
    if (create==NULL){return "Error: syntax error between statements, please try again";}
    //加入对语句中表和列的校验
    int exis = check_table_exists(create);
    if (exis == 0){return "Error: Please use a database";}
    if (exis == -1){return "Your table does not exist";}
    if (exis == -2){return "Column in statement does not exist";}
    res = memte_insert(create);




    return res;
}

char* select_handle(char* sentence){
    char** sent = str_spilt(sentence,"\n");
    scan_word *words = scanWordInit();
    sqlsacnner(words,sent[0]);
    scan_word* iword = scanWordInit();
    sqlsacnner(iword,sent[0]);
    treenode *create = check_tree(iword);
    char* res = NULL;

    if (create){
        res = memte_select(create);
    } else{
        res = str_copy("","Error: syntax error, please try again");
    }


    return res;
}


char* handler_mointor(char* sentence){
    char *base_name = str_copy("",is_use_database());
    if (base_name == NULL){
        return "is not use database";
    }

    char** sent = str_spilt(sentence,"\n");
    scan_word *words = scanWordInit();
    sqlsacnner(words,sent[0]);
    scan_word* iword = scanWordInit();
    sqlsacnner(iword,sent[0]);
    treenode *create = check_tree(iword);
    if (create->is_succ) {
        mointor_add_task(base_name, create->handler.tab_name, create->handler.file, create->handler.colums,
                         create->handler.time);
    } else{
        return "runing fail is synce error";
    }


//    vector<string> arr_col;
//    arr_col.push_back("temp");
//    arr_col.push_back("name");
//    mointor_add_task("myTest","boiler","boiler",arr_col,3);
    return "successfully";
}






int check_table_exists(treenode* root){
    char* db = is_use_database();
    if (db == NULL){return 0;}


    tree_list *sql_s = root->nodelist;
    char* tablename = sql_s->next->tree->str;

    if (!DB_tab_is_exist(tablename))return -1;
    char* colum_mes = sql_s->next->next->tree->str;
    char** colums = str_spilt(colum_mes,",");
    int col_len = str_spilt_size(colum_mes,",");
    for (int i = 0; i < col_len; ++i) {
        if (!DB_colum_is_exist(tablename,colums[i]))return -2;
    }
    return 1;

}



bool sql_oper_create_database(sql_operation* sql){
    bool result = false;

    if (sql->name==NULL)  perror("[ERROR] create database false,databaseName  can't be NULL\n");
    //初始化完成
    result = create_database_db(sql->name);

    return result;

}


/*创建表
 * */
bool sql_oper_create_table(sql_operation* sql){
    char *use_database = is_use_database();
    char *tab_name = str_copy("",sql->name);

    if (use_database==NULL){
        perror("[ERROR] databaseName  can't be NULL\n");
        perror(" 先use databasename");
        return false;
    }
    //建表,jjs那边需要的一些参数
    /*参数1*/
    int columnNum=1;
    condition* swap=sql->data_list;
    while(swap!= nullptr){
        columnNum++;
        swap=swap->next;
    }
    data_type *type_arr = (data_type*)calloc(columnNum , sizeof (data_type));
    char **clum_arr = ( char**)calloc( columnNum,  sizeof( char*));

    type_arr[0] = TIMESTAMP;
    clum_arr[0] = str_copy("","timeStamp");

    condition* swap1=sql->data_list;
    for (int i = 1; i < columnNum; ++i) {
        clum_arr[i] = str_copy("",swap1->c_name);
        type_arr[i] = swap1->dataTypes;
        swap1=swap1->next;
    }

    bool result = DB_create_table(use_database,tab_name,clum_arr,type_arr, columnNum);


    return result;
}




char* create_memte(treenode *root){
    sql_operation *create_database = malloc_sqloperation();
    create_database->handler = CREATE_DATABASE;
    create_database->name = root->nodelist->tree->str;
    bool b = sql_oper_create_database(create_database);
    if (b){
        char* res = "Database created successfully of ";
        res = str_marge(res,create_database->name);
        return res;
    } else{
        char* res = "Syntax error&service exception！！";
        return res;
    }
}



char* create_memte_tb(treenode *root){

    tree_list *sql = root->nodelist;
    treenode *p = sql->tree;

    int list_lens = get_list_size(sql);
    //表名就放上了
    sql_operation *create_tb = malloc_sqloperation();
    create_tb->handler = CREATE_TABLE;
    create_tb->name = p->str;
    sql = sql->next;
    condition *l = create_tb->data_list;
    tree_list *child;
    for (int i = 1; i < list_lens; ++i) {
        if (sql != NULL)
            p = sql->tree;
        else return NULL;

        if (l == NULL)l = malloc_sqlcondition();
        if (p->strtype == 259) {
            child = p->nodelist;
            treenode *ran = child->tree;
            l->c_name = ran->str;
            child = child->next;
            ran = child->tree;
            switch (ran->strtype) {
                case 26:l->dataTypes = INT;break;
                case 29:l->dataTypes = TIMESTAMP;break;
                case 30:
                    l->dataTypes = VARCHAR;
                    child = child->next;
                    ran = child->tree;
                    l->c_value = ran->str;break;
                default:cout<<"未知的类型参数错误"<<endl;

            }
            if (i+1 < list_lens)
                l->next = malloc_sqlcondition();
            l = l->next;
            sql = sql->next;
        }
    }

    if(sql_oper_create_table(create_tb)){
        char* res = "Table created successfully of ";
        res = str_marge(res,create_tb->name);
        return res;
    } else{
        char* res = "Please use a database or database already exisit";
        return res;
    }
}





char* create_handle(char* sentence){
    char** sent = str_spilt(sentence,"\n");
    scan_word *words = scanWordInit();
    sqlsacnner(words,sent[0]);
    treenode *create = check_tree(words);
    if (create==NULL){return "Error: syntax error between statements, please try again";}
    char*res = NULL;
    switch (create->strtype) {
        case 23:res = create_memte(create);break;
        case 24:res = create_memte_tb(create);break;
        default:res = "Syntax error&service exception！！";
    }

    return res;


}































tree_list *branch_259(scan_word *scanWord,int start,int end){
    tree_list *res = (tree_list*)malloc(sizeof(tree_list));
    memset(res,0,sizeof(tree_list));
    if (start >= end){return NULL;}
    for (int i = start; i <= end; ++i) {
        sqlitWord num_word = get_word(scanWord,i);
        if (num_word.num == 40||num_word.num == 41)continue;
        treenode *column_name = (treenode *)malloc(sizeof(treenode));
        memset(column_name,0,sizeof(treenode));
        column_name->str = str_copy(column_name->str,num_word.arr);
        column_name->strlen = strlen(column_name->str);
        column_name->strtype = num_word.num;
        add_list(res,column_name);
    }
    return res;
}



tree_list * branch_256(scan_word *scan,int arrlen,int num){
    tree_list *res = (tree_list *)malloc(sizeof(tree_list));
    memset(res,0,sizeof(tree_list));
    treenode *trees[num];
    memset(trees,0,sizeof(trees));
    sqlitWord *w = scan->word;
    w = w+arrlen;
    char *set;
    for (int i = 0; i < num; i++) {
        trees[i] = (treenode *)malloc(sizeof(treenode));
        memset(trees[i],0,sizeof(treenode));
        trees[i]->str = (char *)malloc(strlen(w->arr)+1);
        memset(trees[i]->str,0,strlen(w->arr)+1);
        for(int j = 0;j < strlen(w->arr);j++){
            char c = w->arr[j];
            trees[i]->str[j] = c;
        }
        trees[i]->str += '\0';
        trees[i]->strlen = strlen(trees[i]->str);
        trees[i]->strtype = w->num;
        w+=2;
    }

    for(int i = 0;i < num;i++){
        add_list(res,trees[i]);
    }
    return res;
}


tree_list * branch_257(scan_word *scan,int arrlen){
    tree_list *res = (tree_list *)malloc(sizeof(tree_list));
    memset(res,0,sizeof(tree_list));
    sqlitWord *p = scan->word;
    p = p+arrlen+1;
    while (p->num != 41){
        if(p->num == 44){
            p+=1;
            continue;
        }
        treenode *tree = (treenode *)malloc(sizeof(treenode));
        memset(tree,0,sizeof(treenode));
        tree->str = str_copy(tree->str,p->arr);
        tree->strtype = p->num;
        tree->strlen = strlen(tree->str);
        add_list(res,tree);
        p+=1;
    }
    return res;
}

tree_list * branch_258(scan_word *scan,int arrlen){
    tree_list *res = (tree_list *)malloc(sizeof(tree_list));
    memset(res,0,sizeof(tree_list));
    sqlitWord *p = scan->word;
    p = p+arrlen+1;
    while (p->num != 41){
        if(p->num == 44){
            p+=1;
            continue;
        }
        treenode *tree = (treenode *)malloc(sizeof(treenode));
        memset(tree,0,sizeof(treenode));
        tree->str = str_copy(tree->str,p->arr);
        tree->strtype = p->num;
        tree->strlen = strlen(tree->str);
        add_list(res,tree);
        p+=1;
    }
    return res;
}







tree_list * branch_245(scan_word *scan,int arrlen){
    tree_list *res = (tree_list *)malloc(sizeof(tree_list));
    memset(res,0,sizeof(tree_list));
    treenode *trees[3];
    memset(trees,0,sizeof(trees));
    sqlitWord *w = scan->word;
    w = w+arrlen;
    for (int i = 0; i < 3; i++) {
        trees[i] = (treenode *)malloc(sizeof(treenode));
        trees[i]->str = (char *)malloc(strlen(w->arr)+1);
        memset(trees[i]->str,0,strlen(w->arr)+1);
        for(int j = 0;j < strlen(w->arr);j++){
            char c = w->arr[j];
            trees[i]->str[j] = c;
        }
        trees[i]->str += '\0';
        trees[i]->strlen = strlen(trees[i]->str);
        trees[i]->strtype = w->num;
        w++;
        arrlen++;
    }

    for(int i = 0;i < 3;i++){
        add_list(res,trees[i]);
    }
    return res;

}




