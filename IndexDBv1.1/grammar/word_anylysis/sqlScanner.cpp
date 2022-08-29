//
// Created by maomao on 2021/1/18.
//
#include "../Myall.h"


// group+by
/*
 * tpyenum表示数据类型
 * -1 ERROR
 * 1 select
 * 2 insert
 * 3 delete
 * 4 from
 * 5 into
 * 6 where
 * 7 group
 * 8 by
 * 9 betweennew sqlWord
 * 10 and
 * 11 or
 * 12 primary
 * 13 like
 * 14 values
 * 15 order
 * 16 mean
 * 17 max
 * 18 min
 * 19 count
 * 20 as
 * 21 time
 * 22 create
 * 23 database
 * 24 table
 * 25 use
 * 26 int
 * 27 float
 * 28 double
 * 29 timestamp
 * 30 varchar
 * 100 letter
 * 150 >=
 * 160 <=
 * 180 !=
 * 200 number
 * 38 &
 * 40 (
 * 41 )
 * 42 *
 * 44 ,
 * 45 -
 * 46 .
 * 58 :
 * 59 ;
 * 60 <
 * 61 =
 * 62 >
 * 127 |
 *
 *
 * 254 and或or之间的词类似于age>40
 * 255 ()内有另外的select语句
 * 256 数据库查询的列号select age,name,id from中的age,name,id下面分支分出来分别是age name id
 * 257 ()插入语句中的内有列名
 * 258 ()插入语句中后面的value即类似于(ssss,15,28,72)
 * 259 ccreate table时的列名及类型属性
 * 1000 \0
 * */

char *keywords[] = {"select", "insert", "delete", "from", "into", "where", "group", "by", "between", "and", "or",
                    "primary", "like", "values", "order", "mean", "max", "min", "count", "as", "time","create","database",
                    "table","use","int","float","double","timestamp","varchar",_END_};


scan_word * scanWordInit(){
   scan_word *res = (scan_word*)malloc(sizeof(scan_word));
   memset(res,0,sizeof(res));
    return res;
}




sqlWord *scanner(scan_word *scan);

void sqlsacnner(scan_word *scan,char *sqlsource) {
    int over = 1;
    int i = 0;
    sqlWord *oneword = new sqlWord;
    strcpy(scan->input, sqlsource);
    scan->p_input = 0;
    printf("your words:\n%s\n", scan->input);
    while (over < 1000 && over != -1) {
        oneword = scanner(scan);
        if (oneword->typenum < 1000) {
            cout << "[" << oneword->typenum <<"\t" << oneword->word << "]" << endl;
            char *str=oneword->word;
            char *aaa=str;
            //整体只加了这么一句 add_tree(oneword->typenum,aaa)
            // add_tree(oneword->typenum,aaa);
            strcpy(scan->word[i].arr, oneword->word);
            scan->word[i].num = oneword->typenum;
            i++;
        }
        over = oneword->typenum;
    }
    initNumber(scan);
//    get_wordlen(scan);
}

//从缓冲区读取一个字符道ch
char m_getch(scan_word *scan) {

    scan->ch = scan->input[scan->p_input];
    scan->p_input++;
    return scan->ch;
}

//去掉空白符号
void removeSpace(scan_word *scan) {
    while (scan->ch == ' ' || scan->ch == 32) {
        scan->ch = scan->input[scan->p_input];
        scan->p_input++;
    }
}

//回退一个字符
void retract(scan_word *scan) {
    scan->p_input--;
}

//拼接单词
void conTokens(scan_word *scan) {
    scan->token[scan->p_token] = scan->ch;
    scan->p_token++;
    scan->token[scan->p_token] = '\0';
}

//判断是否为字母
int letter(scan_word *scan) {
    if (scan->ch >= 'a' && scan->ch <= 'z' || scan->ch >= 'A' && scan->ch <= 'Z') {
        return 1;
    } else {
        return 0;
    }

}

//判断是否为数字
int digit(scan_word *scan) {
    if (scan->ch >= '0' && scan->ch <= '9') {
        return 1;
    } else {
        return 0;
    }
}

int reserver(scan_word *scan) {
    int i = 0;
    //相同为0 表示读到末尾
    while (strcmp(keywords[i], _END_)) {
        if (!strcmp(keywords[i], scan->token))
            return i + 1;
        i++;
    }
    return 100; //不是关键字 普通字段

}

sqlWord *scanner(scan_word *scan) {
    sqlWord *myword = new sqlWord;
    myword->typenum = 0;
    myword->word = " ";
    scan->p_token = 0; //单词缓冲区
    m_getch(scan);
    removeSpace(scan);
    if (letter(scan)) //判断读取到首字母是字母
    {
        while (letter(scan) || digit(scan)) {
            conTokens(scan);
            m_getch(scan);
        }
        retract(scan);//回退一个字符
        myword->typenum = reserver(scan);
        myword->word = scan->token;
        return myword;
    } else if (digit(scan)) //判断是不是数字
    {
        while (digit(scan)) //所有数字连接起来
        {
            conTokens(scan);
            m_getch(scan);
        }
        retract(scan);
        myword->typenum = 200;
        myword->word = scan->token;
        return myword;
    } else
        switch (scan->ch) {
            case '<':
                m_getch(scan);
                if (scan->ch == '=') {
                    myword->typenum = 150;
                    myword->word = "<=";
                    return myword;
                }
                retract(scan);//读取到的下个字符不是=,则要回退
                myword->typenum = 60;
                myword->word = "<";
                return myword;
                break;
            case '>':
                m_getch(scan);
                if (scan->ch == '=') {
                    myword->typenum = 150;
                    myword->word = ">=";
                    return myword;
                }
                retract(scan);//读取到的下个字符不是=,则要回退
                myword->typenum = 62;
                myword->word = ">";
                return myword;
                break;
            case '=':
                myword->typenum = 61;
                myword->word = "=";
                return myword;
                break;

            case '!':
                m_getch(scan);
                if (scan->ch == '=') {
                    myword->typenum = 180;
                    myword->word = "!=";
                    return myword;
                    break;
                }
                retract(scan);
                myword->typenum = -1;
                myword->word = "ERROR";
                return myword;
                break;

            case '&':
                myword->typenum = 38;
                myword->word = "&";
                return myword;
                break;
            case '(':
                myword->typenum = 40;
                myword->word = "(";
                return myword;
                break;
            case ')':
                myword->typenum = 41;
                myword->word = ")";
                return myword;
                break;
            case '*':
                myword->typenum = 42;
                myword->word = "*";
                return myword;
                break;
            case ';':
                myword->typenum = 59;
                myword->word = ";";
                return myword;
                break;
            case ',':
                myword->typenum = 44;
                myword->word = ",";
                return myword;
                break;
            case '.':
                myword->typenum = 46;
                myword->word = ".";
                return myword;
                break;
            case '|':
                myword->typenum = 127;
                myword->word = "|";
                return myword;
                break;
            case '-':
                myword->typenum = 45;
                myword->word = "-";
                return myword;
                break;
            case ':':
                myword->typenum = 58;
                myword->word = ":";
                return myword;
                break;
            case '\0':
                myword->typenum = 1000;
                myword->word = "OVER";
                return myword;
                break;
            default:
                myword->typenum = -1;
                myword->word = "ERROR";
                return myword;
                break;
        }
}
//---------------------------------------------------------------------------

//从数组中拿一个单词或符号
void getWord(scan_word *scan) {
    scan->len++;
    scan->number = scan->word[scan->len].num;
}

//回退一个单词
void backGetWord(scan_word *scan) {
    scan->len--;
}

int isLetter(scan_word *scan) {
    if (scan->number == 100) {
        printf("\n单词 判断成功！种别码：%d  单词：%s\n", scan->number, scan->word[scan->len].arr);
        getWord(scan);
        return 1;
    }
//        printf(" error:单词错误");
        return 0;
}

int isNumber(scan_word *scan) {
    if (scan->number == 200) {
        printf("\n数字 判断成功！种别码：%d  单词：%s\n", scan->number, scan->word[scan->len].arr);
        getWord(scan);
        return 1;
    }
        printf(" error:数字错误");
        return 0;
}

//S





int sList(scan_word *scan) {
    int i = 1;
    //TODO
    //if(aggregate)

    while (scan->number != 4) {
        if (scan->number == 42) {
            getWord(scan);
            return 1;
        } else if (scan->number == 44) {//,
            getWord(scan);
        } else if (scan->number == 100) {
            scan->selectList[i] = scan->word[scan->len];
            getWord(scan);
            i++;
            return i;
        }
    }
}


void getTableName(scan_word *scan) {
    if (isLetter(scan)) {
        scan->setTableName[0] = scan->word[scan->len - 1];
        printf("setTableName[0]:%s", scan->setTableName[0].arr);
        return;
    }
}

void params(scan_word *scan) {
    int i = 0;
    if (scan->number == 40) {//(
        getWord(scan);
        while (scan->number != 41) {//)
            if (scan->number == 44) {//,
                getWord(scan);
            } else if (isLetter(scan) || isNumber(scan)) {
                scan->setParams[i] = scan->word[scan->len];
                getWord(scan);
                i++;
            }

        }
        return;
    } else {
        printf(" error:参数错误");
        return;
    }
}

void andFunc(scan_word *scan) {

    if (scan->number == 10) {
        getWord(scan);
        if (isLetter(scan)) {
            scan->setKeys[scan->counts] = scan->word[scan->len];

            if (scan->number == 61)//=
            {
                if (isLetter(scan) || isNumber(scan)) {
                    scan->setValues[scan->counts] = scan->word[scan->len - 1];
                    scan->counts++;
                    scan->level += 2;
                    allFunc(scan);
                }
            }
        }
    }
}

//聚合 TODO
void aggregate() {

}

int isWhere(scan_word *scan) {
    if (isLetter(scan)) {
        //不初始化会有 浅拷贝问题
        // memset(setKeys[counts],0,sizeof (setKeys[counts]));
        //strcpy(setKeys[counts],word[len-1].arr);
        sqlitWord setKey, setValue;
        setKey = scan->word[scan->len - 1];
        scan->counts++;
        if (scan->number == 61)//=
        {
            if (isLetter(scan) || isNumber(scan)) {
                scan->setValues[scan->counts] = scan->word[scan->len - 1];
                andFunc(scan);
            }
        }
    }
    return 0;
}

int isBetweenAnd(scan_word *scan,int i) {
    int flag = 0;
    while (scan->number != 59) {
        switch (scan->number) {
            case 9:
                getWord(scan);
                flag++;
                break;
            case 100:
                scan->setBetween[i] = scan->word[scan->len];
                getWord(scan);
                i++;
                flag++;
            case 10:
                getWord(scan);
                flag++;
            default:
                break;
        }
        isBetweenAnd(scan,i);
    }
    if (flag == 4) {
        return 1;
    }
    return 0;
}

int isOrderBy(scan_word *scan,int i) {
    int flag = 0;
    while (scan->number != 59) {
        switch (scan->number) {
            case 15:
                getWord(scan);
                flag++;
                break;
            case 100:
                scan->setOrderBy[i] = scan->word[scan->len];
                getWord(scan);
                i++;
                flag++;
            case 10:
                getWord(scan);
                flag++;
            default:
                break;
        }
        isOrderBy(scan,i);
    }
    if (flag == 4) {
        return 1;
    }
    return 0;
}

int isGroupBy(scan_word *scan,int i) {
    int flag = 0;
    while (scan->number != 59) {
        switch (scan->number) {
            case 7:
                getWord(scan);
                flag++;
                break;
            case 100:
                scan->setGroupBy[i] = scan->word[scan->len];
                getWord(scan);
                i++;
                flag++;
            case 10:
                getWord(scan);
                flag++;
            default:
                break;
        }
        isOrderBy(scan,i);
    }
    if (flag == 4) {
        return 1;
    }
    return 0;
}

int isEnd(scan_word *scan) {
    if (scan->number == 59) {
        return 1;
    }
    return 0;
}

int allFunc(scan_word *scan) {
    int i = 0;
    switch (scan->number) {
        case 6: //where
            getWord(scan);
            isWhere(scan);
            return (scan->level += 1);
            break;
        case 7: //group
            getWord(scan);
            isGroupBy(scan,i);
            return (scan->level += 3);
            break;
        case 9: //between
            getWord(scan);
            isBetweenAnd(scan,i);
            return (scan->level += 4);
            break;
        case 15: //order
            getWord(scan);
            isOrderBy(scan,i);
            return (scan->level += 5);
            break;
        default:
            printf("error!");
            return 0;
            break;
    }
}

int selectSql(scan_word *scan) {

    if (sList(scan) == 1) {
        printf("全表扫描");
    }
    if (scan->number == 4)//from
    {
        getWord(scan);
        isLetter(scan);
        isEnd(scan);
        if (!allFunc(scan)) {
//            printf("delete from error:语句错误");
            printf("select from error:语句错误");//修改处
            return 0;
        }
        return scan->level;
    }
    return 0;
}

int insertSql(scan_word *scan) {
    if (scan->number == 5) //into
    {
        printf("\ninsert into判断成功！种别码：%d  单词：%s\n", scan->number, scan->word[scan->len].arr);
        getWord(scan);
        getTableName(scan);
        if (scan->number == 14) {
            params(scan);
        }
    } else {
        printf("insert into error:语句错误");
        return 0;
    }

}

int deleteSql(scan_word *scan) {

    if (scan->number == 4) {//from
        printf("\ndelete from判断成功！种别码：%d  单词：%s\n", scan->number, scan->word[scan->len].arr);
        getWord(scan);
        getTableName(scan);
        if (!allFunc(scan)) {
            printf("delete from error:语句错误");
            return 0;
        }

    }
    return scan->level;
}

//采用自顶向下的方式解析 LL
void llParser(scan_word *scan) {

    switch (scan->number) {

        case 1: //select
            printf("\nselect判断成功！种别码：%d  单词：%s\n", scan->number, scan->word[scan->len].arr);
            getWord(scan);
            scan->level = selectSql(scan);
            //TODO 取出tableName 转化为tableId
//            mymap() 1 between and group by 2
            //根据原语的等级调用
            /* switch (level) {

             }*/
            break;
        case 2://insert
            printf("\ninsert判断成功！种别码：%d  单词：%s\n", scan->number, scan->word[scan->len].arr);
            getWord(scan);
            scan->level = insertSql(scan);
            break;
        case 3://delete
            printf("\ndelete判断成功！种别码：%d  单词：%s\n", scan->number, scan->word[scan->len].arr);
            getWord(scan);
            scan->level = deleteSql(scan);
            break;
        case 22:
            printf("\ncreate判断成功！ 种别码 :%d   单词 %s\n",scan->number,scan->word[scan->len+1].arr);
            break;
        case 25:
            printf("\nuse判断成功！ 种别码 :%d\n",scan->number);
            break;
        default:
            printf("error:语句错误\n");
            break;
    }
    return;

}

void test(scan_word *scan){
  int a =  strlen(scan->word[0].arr);
  printf("%d",a);


}


//初始化number 并调用llParser
void initNumber(scan_word *scan) {
    scan->number = scan->word[scan->len].num;
    llParser(scan);
}
sqlitWord get_word(scan_word *scan,int len){
    return scan->word[len];
}






void clear_cache(scan_word *scan){
   memset(scan->word,0,sizeof(scan->word));
   scan->nowlen = 0;
   scan->len = 0;
}
int get_wordlen(scan_word *scan){
    scan->nowlen = 0;
    for(int i = 0;i < SMALL_LEN;i++){
        if(scan->word[i].num != 0){
            scan->nowlen++;
        } else{
            break;
        }
    }
    return scan->nowlen;
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


list * branch_245(scan_word *scan,int arrlen){
    list *res = (list *)malloc(sizeof(list));
    memset(res,0,sizeof(list));
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






list *branch_259(scan_word *scanWord,int start,int end){
    list *res = (list*)malloc(sizeof(list));
    memset(res,0,sizeof(list));
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
list * branch_256(scan_word *scan,int arrlen,int num){
    list *res = (list *)malloc(sizeof(list));
    memset(res,0,sizeof(list));
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
list * branch_257(scan_word *scan,int arrlen){
    list *res = (list *)malloc(sizeof(list));
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

list * branch_258(scan_word *scan,int arrlen){
    list *res = (list *)malloc(sizeof(list));
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


