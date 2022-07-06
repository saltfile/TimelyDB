//
// Created by saltfish on 2022/2/17.
//
#include "../Myall.h"
#define TREE_LEN 4
char databasename[255];
struct treenode *sel_tree[TREE_LEN];
struct treenode *ins_tree[TREE_LEN];
//被取走的树节点
int sql_len = 0;
int in_len = 0;

int wordlen = 0;

void create_sqltree(){
    memset(sel_tree,0,sizeof(treenode)*TREE_LEN);
    memset(ins_tree,0,sizeof(treenode)*TREE_LEN);
    for(int i = 0 ;i < TREE_LEN;i++){
        //node1是select//节点type是1
        treenode *node1 = (treenode *)malloc(sizeof(treenode));
        memset(node1,0,sizeof(node1));
        node1->strtype = 1;
        node1->str = "select";
        node1->strlen = strlen(node1->str);
        //node2是搜索结果*
        treenode *node2 = (treenode *)malloc(sizeof(treenode));
        memset(node2,0,sizeof(node2));
        node2->strtype = 42;
        node2->str = "*";
        node2->strlen = strlen(node2->str);
        node1->nodelist = (list *)malloc(sizeof(list));
        add_list(node1->nodelist,node2);
        //node3是from
        treenode *node3 = (treenode *)malloc(sizeof(treenode));
        memset(node3,0,sizeof(node3));
        node3->strtype = 4;
        node3->str = "from";
        node3->strlen = strlen(node3->str);
        node2->nodelist = (list *)malloc(sizeof(list));
        add_list(node1->nodelist,node3);
        //node4是表名就是个letter
        treenode *node4 = (treenode *)malloc(sizeof(treenode));
        memset(node4,0,sizeof(node4));
        node4->strtype = 100;
        node4->str = "xxx";//这个只是代替
        node4->strlen = strlen(node4->str);
        node3->nodelist = (list *)malloc(sizeof(list));
        add_list(node1->nodelist,node4);
        sel_tree[i] = node1;
    }
    sql_len = TREE_LEN-1;
    for(int i = 0 ;i < TREE_LEN;i++){

        treenode *node1 = (treenode *)malloc(sizeof(treenode));
        memset(node1,0,sizeof(node1));
        node1->strtype = 2;
        node1->str = "insert";
        node1->strlen = strlen(node1->str);
        treenode *node2 = (treenode *)malloc(sizeof(treenode));
        memset(node2,0,sizeof(node2));
        node2->strtype = 5;
        node2->str = "into";
        node2->strlen = strlen(node2->str);
        node1->nodelist = (list *)malloc(sizeof(list));
        add_list(node1->nodelist,node2);
        treenode *node3 = (treenode *)malloc(sizeof(treenode));
        memset(node3,0,sizeof(node3));
        node3->strtype = 100;
        node3->str = "t_name";
        node3->strlen = strlen(node3->str);
        node2->nodelist = (list *)malloc(sizeof(list));
        add_list(node1->nodelist,node3);
        ins_tree[i] = node1;
    }
    in_len = TREE_LEN-1;
}


treenode *check_tree(){
    wordlen = get_wordlen();
    treenode *root = NULL;
    sqlitWord head = get_word(0);

    switch (head.num) {
        case 1:
            log_info("查询语句");
            root = sel_tree[sql_len];
            sel_tree[sql_len] = NULL;
            sql_len--;
            sql_sel(root);
            break;
        case 2:
            log_info("插入语句");
            root = ins_tree[in_len];
            ins_tree[in_len] = NULL;
            in_len--;
            sql_ins(root);
            break;
        default:
            log_erro("错误，语句存在违规语法");
            break;


    }

    return root;
}

void check_fun(treenode *sql){
    int type = sql->strtype;
    switch (type) {
        case 1:

            break;

        default:
            break;
    }
}
//TODO:这里是处理insert语句简单实例
//先对比前面四个语法是否正确
//插入语句树
void sql_ins(treenode *root){
    treenode *p = root;
    list * sel = p->nodelist;
    treenode *sql = sel->tree;
    int arrlen = 1;
    int wordlen = get_wordlen();
    sqlitWord word = get_word(arrlen);
    //into
    if(word.num == sql->strtype){
        sel = sel->next;
        sql = sel->tree;
        arrlen++;
    } else{
        log_erro("插入语句错误,缺少into");
    }
    if(wordlen <= arrlen){
        //封装语法错误
        log_erro("语句残缺");
        return;
    }
    //tname
    word = get_word(arrlen);
    if(word.num == sql->strtype){
        sql->str = str_copy(sql->str,word.arr);
        sql->strlen = strlen(sql->str);
        arrlen++;
    } else{
        log_erro("表名位置，缺少后续语句");
        return;
    }

    if(wordlen <= arrlen){
        //封装语法错误
        log_erro("语句残缺");
        return;
    }
    //列名字表
    word = get_word(arrlen);
    char *str="\0";
    int col_list = arrlen;
    if(word.num == 40){

        arrlen++;
        while (true){
            if(wordlen <= arrlen){
                //封装语法错误
                log_erro("列表名，语句残缺");
                return;
            }
            word = get_word(arrlen);
            if(word.num == 41){
                break;
            }
            str = str_merge(str,word.arr);
            arrlen++;
        }
    } else{
        log_erro("错误，语句不完整");
        return;
    }
    list *slist = branch_257(col_list);
    treenode *colomn = (treenode *)malloc(sizeof(treenode));
    memset(colomn,0,sizeof(treenode));
    colomn->str = str;
    colomn->strtype = 257;
    colomn->strlen = strlen(colomn->str);
    colomn->nodelist = slist;
    add_list(sel,colomn);
    sel = sel->next;
    arrlen++;

    //values
    word = get_word(arrlen);
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
        log_erro("语句残缺");
        return;
    }


    //values后面的列表
    word = get_word(arrlen);
    while (true){

        if(wordlen <= arrlen){
            break;
        }
        word = get_word(arrlen);
        int val_len;
        char *val_str = "\0";
        if (word.num == 40){
            val_len = arrlen;
            arrlen++;
            while (true){
                if(wordlen <= arrlen){
                    //封装语法错误
                    log_erro("列表名，语句残缺");
                    return;
                }
                word = get_word(arrlen);
                if(word.num == 41){
                    break;
                }
                val_str = str_merge(val_str,word.arr);//前继
                arrlen++;
            }
        } else{
            log_erro("语法错误");
            return;
        }

        treenode *val_list =  (treenode *)malloc(sizeof(treenode));
        memset(val_list,0,sizeof(val_list));
        val_list->str = str_copy(val_list->str,val_str);
        val_list->strtype = 258;
        val_list->strlen = strlen(val_list->str);
        val_list->nodelist = branch_258(val_len);
        add_list(sel,val_list);
        arrlen++;
        sel = sel->next;
    }

    clear_cache();
}



//TODO:这里是处理select语句简单实例
//先对比前面四个语法是否正确
void sql_sel(treenode *root){
    treenode *p = root;
    list * sel = p->nodelist;
    treenode *sql = sel->tree;
    int arrlen = 1;
    int wordlen = get_wordlen();
    sqlitWord word = get_word(arrlen);
    if(word.num != sql->strtype){
        colnm *s = get_colnm();
        sql->strtype = s->type;
        sql->str = s->str;
        sql->strlen = strlen(sql->str);
        int nums =  s->end-arrlen-1;
        sql->nodelist = branch_256(arrlen,nums);
        arrlen+=s->end;
    }else{
        arrlen += 1;
        log_info("对比成功");
    }
    sqlitWord wfrom = get_word(arrlen);
    if(wfrom.num == 0){
        //要封包
        log_erro("未知语法无法分辨");
        return;
    }
    sel = sel->next;
    sql = sel->tree;
    if(wordlen <= arrlen){
        //封装语法错误
        log_erro("语句错误,缺少表名");
        return;
    }
    if(wfrom.num == sql->strtype){
        //检测到from并且识别成功开始识别后面的表名
        sel = sel->next;
        sql = sel->tree;
        arrlen++;
    }else{
        //清空并封装一个语句做返回
        log_erro("语句错误");
        return;
    }
    int tablelen = strlen(databasename)+sql->strlen+2;
    char name_tab[tablelen];
    word = get_word(arrlen);
    if(word.num == sql->strtype){
        sql->str = (char *)malloc(sizeof(strlen(word.arr)+1));
        sql->str = str_copy(sql->str,word.arr);
        sql->strlen = strlen(sql->str);
        sql->str += '\0';
    }

    if(strlen(databasename) != 0){
    memset(name_tab,0,tablelen);
    strcat(name_tab,databasename);
    strcat(name_tab,".");
    strcat(name_tab,sql->str);
    //这里需要链接文件树确定表存在
    } else{
        //封装错误包
        log_erro("未引用数据库");
        return;
    }
//一级初级查找到这里是完成了的后面是where
/*
 * TODO:明确标志----->
 * 这里未来要改成switch 后面要补全成为一个支持join功能 + on 和逻辑链接等
 * */
    arrlen++;
    if(arrlen >= wordlen){
        //证明后面没东西
        log_info("简易树建立成功");
        return;
    }

   sqlitWord where_word = get_word(arrlen);
    if(where_word.num == 6){
        log_debug("发现where");
        treenode *node = (treenode *)malloc(sizeof(treenode));
        node->strtype = 6;
        node->str = (char *)malloc(sizeof(strlen(where_word.arr)+1));
        node->str = where_word.arr;
        node->str += '\0';
        add_list(sel,node);
        sel = sel->next;
        sql = sel->tree;
        arrlen++;
    } else{
        log_erro("错误语法，缺少[where]类似标识");
        //这里需要封装错误包
    }
    if(wordlen <= arrlen){
        //封装语法错误
        log_erro("语句错误,缺少where后续语句");
        return;
    }

    sqlitWord and_word = get_word(arrlen);

    if(and_word.num == 100) {
        while (true){
            //先形成小链表
        colnm *s = get_andcolum(arrlen);
        if(s->type == -234){
            log_erro("语法错误:条件语句不可接受and/or语句");
            return;
        } else if(s->type == -235){
            log_erro("语法错误:条件语句缺少元素");
            return;
        }
        int p_len = arrlen;
        treenode *annode = (treenode *) malloc(sizeof(treenode));
        annode->nodelist = (struct list*)malloc(sizeof(list));
        memset(annode->nodelist,0,sizeof(list));

        annode->nodelist = branch_245(arrlen);
        //这里指针逃逸需要去解决


        //生成下面的条件语句链表
//        for(int i = p_len ; i < arrlen+3;i++){
//            sqlitWord sql_word = get_word(i);
//            treenode *prevs = (treenode *)malloc(sizeof(treenode));
//            prevs->str = sql_word.arr+'\0';
//            prevs->strlen = strlen(prevs->str);
//            prevs->strtype = sql_word.num;
//            add_list(annode->nodelist,prevs);
//        }

        annode->str = s->str;
        annode->strlen = strlen(annode->str);
        annode->strtype = s->type;
        add_list(sel, annode);
        sel = sel->next;
        sql = sel->tree;
        arrlen = s->end;

        if (wordlen <= arrlen) {
                //封装语法错误
                log_debug("语句结束");
            break;
        }

            sqlitWord rela_word = get_word(arrlen);
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
                log_debug("where后面缺少相应语句");
                return;
            }
        }else{
            log_erro("语法错误:条件语句缺少对应的运算符");
            return;
        }
        }
        log_info("语句结束");
    } else{
        string str = "语句where后面不可加上: ";
        string  str1 = and_word.arr;
        string sss = str+str1;
        log_erro(sss);
    }
    clear_cache();
}
















void sel_254(treenode *node){
    treenode *p = node;
    char *str = p->str;
    char *strs[3];
    char pstr[p->strlen];
    int p_pstr = 0;
    int p_strs = 0;
    for(int i = 0;i < p->strlen;i++){
        if(str[i] == ' '){
            strs[p_strs] = pstr;
            p_pstr = 0;
            memset(pstr,0,p->strlen);
            continue;
        } else{
            pstr[p_pstr] = str[i];
            p_pstr++;
        }

    }








}




void tree_trim(treenode *root){
    treenode *p = root;
    while (p->nodelist!=NULL){
        list *list = p->nodelist;

        while (list = list->next){
            treenode *node = list->tree;
            switch (node->strtype) {
                case 254:{
                    sel_254(node);
                }break;

            }
        }



    }











}





void use_fun(){
    char *str = "sasd";
    strcat(databasename,str);
}













