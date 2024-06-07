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



char* memte_insert(treenode* root){
//    char **col_key =

//    TODO:获取所有列数-将对应的、key时列名 val是值

    tree_list* sql = root->nodelist->next;
    treenode* p = sql->tree;

    sql_operation* insert = malloc_sqloperation();
    insert->handler = INSERTINTO;
    insert->name = str_copy(insert->name,p->str);
    insert->timestamp = 0;
    sql = sql->next;
    tree_list *colnms = sql->tree->nodelist;
    return NULL;
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











