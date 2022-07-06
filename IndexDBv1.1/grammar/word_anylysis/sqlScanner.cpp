//
// Created by maomao on 2021/1/18.
//
#include "../Myall.h"

#define BUF_LEN 1024
#define SMALL_LEN 256
#define _END_ "END"
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
 * 1000 \0
 * */

char *keywords[] = {"select", "insert", "delete", "from", "into", "where", "group", "by", "between", "and", "or",
                    "primary", "like", "values", "order", "mean", "max", "min", "count", "as", "time", _END_};
char input[BUF_LEN];
char token[SMALL_LEN] = "";
sqlitWord word[BUF_LEN]; //存放分词后的结果
sqlitWord setParams[SMALL_LEN]; //存放insert参数
sqlitWord setTableName[SMALL_LEN];//存放表名
sqlitWord setKeys[SMALL_LEN];//存放key
sqlitWord setValues[SMALL_LEN];//存放values
sqlitWord setBetween[SMALL_LEN];//存放between and 参数
sqlitWord setOrderBy[SMALL_LEN];//存放order by参数
sqlitWord setGroupBy[SMALL_LEN];//存放group by参数
sqlitWord selectList[SMALL_LEN];//存放selectList
int nowlen = 0;

int len = 0;
int p_input;//指针
int p_token;
int level;//函数汇总
char ch;
int number;
int counts = 0;


sqlWord *scanner();

void sqlsacnner(char *sqlsource) {
    int over = 1;
    int i = 0;
    sqlWord *oneword = new sqlWord;
    strcpy(input, sqlsource);
    p_input = 0;
    printf("your words:\n%s\n", input);
    while (over < 1000 && over != -1) {

        oneword = scanner();
        if (oneword->typenum < 1000) {
            cout << "[" << oneword->typenum <<"\t" << oneword->word << "]" << endl;
            char *str=oneword->word;
            char *aaa=str;
            //整体只加了这么一句 add_tree(oneword->typenum,aaa)
           // add_tree(oneword->typenum,aaa);
            strcpy(word[i].arr, oneword->word);
            word[i].num = oneword->typenum;
            i++;
        }
        over = oneword->typenum;
    }
    initNumber();
    get_wordlen();
}

//从缓冲区读取一个字符道ch
char m_getch() {
    ch = input[p_input];
    p_input++;
    return ch;
}

//去掉空白符号
void removeSpace() {
    while (ch == ' ' || ch == 32) {
        ch = input[p_input];
        p_input++;
    }
}

//回退一个字符
void retract() {
    p_input--;
}

//拼接单词
void conTokens() {
    token[p_token] = ch;
    p_token++;
    token[p_token] = '\0';
}

//判断是否为字母
int letter() {
    if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {
        return 1;
    } else {
        return 0;
    }

}

//判断是否为数字
int digit() {
    if (ch >= '0' && ch <= '9') {
        return 1;
    } else {
        return 0;
    }
}

int reserver() {
    int i = 0;
    //相同为0 表示读到末尾
    while (strcmp(keywords[i], _END_)) {
        if (!strcmp(keywords[i], token))
            return i + 1;
        i++;
    }
    return 100; //不是关键字 普通字段

}

sqlWord *scanner() {
    sqlWord *myword = new sqlWord;
    myword->typenum = 0;
    myword->word = " ";
    p_token = 0; //单词缓冲区
    m_getch();
    removeSpace();
    if (letter()) //判断读取到首字母是字母
    {
        while (letter() || digit()) {
            conTokens();
            m_getch();
        }
        retract();//回退一个字符
        myword->typenum = reserver();
        myword->word = token;
        return myword;
    } else if (digit()) //判断是不是数字
    {
        while (digit()) //所有数字连接起来
        {
            conTokens();
            m_getch();
        }
        retract();
        myword->typenum = 200;
        myword->word = token;
        return myword;
    } else
        switch (ch) {
            case '<':
                m_getch();
                if (ch == '=') {
                    myword->typenum = 150;
                    myword->word = "<=";
                    return myword;
                }
                retract();//读取到的下个字符不是=,则要回退
                myword->typenum = 60;
                myword->word = "<";
                return myword;
                break;
            case '>':
                m_getch();
                if (ch == '=') {
                    myword->typenum = 150;
                    myword->word = ">=";
                    return myword;
                }
                retract();//读取到的下个字符不是=,则要回退
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
                m_getch();
                if (ch == '=') {
                    myword->typenum = 180;
                    myword->word = "!=";
                    return myword;
                    break;
                }
                retract();
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
void getWord() {
    len++;
    number = word[len].num;
}

//回退一个单词
void backGetWord() {
    len--;
}

int isLetter() {
    if (number == 100) {
        printf("\n单词 判断成功！种别码：%d  单词：%s\n", number, word[len].arr);
        getWord();
        return 1;
    }
//        printf(" error:单词错误");
        return 0;
}

int isNumber() {
    if (number == 200) {
        printf("\n数字 判断成功！种别码：%d  单词：%s\n", number, word[len].arr);
        getWord();
        return 1;
    }
        printf(" error:数字错误");
        return 0;
}







int sList() {
    int i = 1;
    //TODO
    //if(aggregate)

    while (number != 4) {
        if (number == 42) {
            getWord();
            return 1;
        } else if (number == 44) {//,
            getWord();
        } else if (number == 100) {
            selectList[i] = word[len];
            getWord();
            i++;
            return i;
        }
    }
}


void getTableName() {
    if (isLetter()) {
        setTableName[0] = word[len - 1];
        printf("setTableName[0]:%s", setTableName[0].arr);
        return;
    }
}

void params() {
    int i = 0;
    if (number == 40) {//(
        getWord();
        while (number != 41) {//)
            if (number == 44) {//,
                getWord();
            } else if (isLetter() || isNumber()) {
                setParams[i] = word[len];
                getWord();
                i++;
            }

        }
        return;
    } else {
        printf(" error:参数错误");
        return;
    }
}

void andFunc() {

    if (number == 10) {
        getWord();
        if (isLetter()) {
            setKeys[counts] = word[len];

            if (number == 61)//=
            {
                if (isLetter() || isNumber()) {
                    setValues[counts] = word[len - 1];
                    counts++;
                    level += 2;
                    allFunc();
                }
            }
        }
    }
}

//聚合 TODO
void aggregate() {

}

int isWhere() {
    if (isLetter()) {
        //不初始化会有 浅拷贝问题
        // memset(setKeys[counts],0,sizeof (setKeys[counts]));
        //strcpy(setKeys[counts],word[len-1].arr);
        sqlitWord setKey, setValue;
        setKey = word[len - 1];
        counts++;
        if (number == 61)//=
        {
            if (isLetter() || isNumber()) {
                setValues[counts] = word[len - 1];
                andFunc();
            }
        }
    }
    return 0;
}

int isBetweenAnd(int i) {
    int flag = 0;
    while (number != 59) {
        switch (number) {
            case 9:
                getWord();
                flag++;
                break;
            case 100:
                setBetween[i] = word[len];
                getWord();
                i++;
                flag++;
            case 10:
                getWord();
                flag++;
            default:
                break;
        }
        isBetweenAnd(i);
    }
    if (flag == 4) {
        return 1;
    }
    return 0;
}

int isOrderBy(int i) {
    int flag = 0;
    while (number != 59) {
        switch (number) {
            case 15:
                getWord();
                flag++;
                break;
            case 100:
                setOrderBy[i] = word[len];
                getWord();
                i++;
                flag++;
            case 10:
                getWord();
                flag++;
            default:
                break;
        }
        isOrderBy(i);
    }
    if (flag == 4) {
        return 1;
    }
    return 0;
}

int isGroupBy(int i) {
    int flag = 0;
    while (number != 59) {
        switch (number) {
            case 7:
                getWord();
                flag++;
                break;
            case 100:
                setGroupBy[i] = word[len];
                getWord();
                i++;
                flag++;
            case 10:
                getWord();
                flag++;
            default:
                break;
        }
        isOrderBy(i);
    }
    if (flag == 4) {
        return 1;
    }
    return 0;
}

int isEnd() {
    if (number == 59) {
        return 1;
    }
    return 0;
}

int allFunc() {
    int i = 0;
    switch (number) {
        case 6: //where
            getWord();
            isWhere();
            return (level += 1);
            break;
        case 7: //group
            getWord();
            isGroupBy(i);
            return (level += 3);
            break;
        case 9: //between
            getWord();
            isBetweenAnd(i);
            return (level += 4);
            break;
        case 15: //order
            getWord();
            isOrderBy(i);
            return (level += 5);
            break;
        default:
            printf("error!");
            return 0;
            break;
    }
}

int selectSql() {

    if (sList() == 1) {
        printf("全表扫描");
    }
    if (number == 4)//from
    {
        getWord();
        isLetter();
        isEnd();
        if (!allFunc()) {
//            printf("delete from error:语句错误");
            printf("select from error:语句错误");//修改处
            return 0;
        }
        return level;
    }
    return 0;
}

int insertSql() {
    if (number == 5) //into
    {
        printf("\ninsert into判断成功！种别码：%d  单词：%s\n", number, word[len].arr);
        getWord();
        getTableName();
        if (number == 14) {
            params();
        }
    } else {
        printf("insert into error:语句错误");
        return 0;
    }

}

int deleteSql() {

    if (number == 4) {//from
        printf("\ndelete from判断成功！种别码：%d  单词：%s\n", number, word[len].arr);
        getWord();
        getTableName();
        if (!allFunc()) {
            printf("delete from error:语句错误");
            return 0;
        }

    }
    return level;
}

//采用自顶向下的方式解析 LL
void llParser() {

    switch (number) {

        case 1: //select
            printf("\nselect判断成功！种别码：%d  单词：%s\n", number, word[len].arr);
            getWord();

            level = selectSql();
            //TODO 取出tableName 转化为tableId
//            mymap() 1 between and group by 2
            //根据原语的等级调用
            /* switch (level) {

             }*/
            break;
        case 2://insert
            printf("\ninsert判断成功！种别码：%d  单词：%s\n", number, word[len].arr);
            getWord();
            level = insertSql();
            break;
        case 3://delete
            printf("\ndelete判断成功！种别码：%d  单词：%s\n", number, word[len].arr);
            getWord();
            level = deleteSql();
            break;
        default:
            printf("error:语句错误");
            break;
    }
    return;

}

void test(){
  int a =  strlen(word[0].arr);
  printf("%d",a);


}


//初始化number 并调用llParser
void initNumber() {
    number = word[len].num;
    llParser();
}
sqlitWord get_word(int len){
    return word[len];
}






void clear_cache(){
   memset(word,0,sizeof(word));
   nowlen = 0;
   len = 0;
}
int get_wordlen(){
    nowlen = 0;
    for(int i = 0;i < SMALL_LEN;i++){
        if(word[i].num != 0){
            nowlen++;
        } else{
            break;
        }
    }
    return nowlen;
}
colnm *get_colnm(){
    int arr = 0;

    for(int i = 1;i < nowlen;i++){
        if(word[i].num != 4){
            arr++;
        } else{
            break;
        }
    }
    int get_len = 1;

    for(int i = 1;i <= arr;i++){
       get_len += strlen(word[i].arr);
    }
    char res[get_len];
    memset(res,0,get_len);
    for(int i = 1;i <= arr;i++){
        strcat(res,word[i].arr);
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

colnm *get_andcolum(int len){
    int end = len;
    if(len+3 > nowlen){
        colnm *c = (colnm *)malloc(sizeof(colnm));
        c->type = -235;
        return c;
    }
    for(int i = len;i < len+3;i++){
        if(word[i].num == 10||word[i].num == 11){
            colnm *c = (colnm *)malloc(sizeof(colnm));
            c->type = -234;
            return c;
        } else{
            end++;
        }
    }
    int get_strlen = 1;

    for(int i = len;i < end;i++){
        get_strlen += strlen(word[i].arr);
        get_strlen++;
    }
    char res[get_strlen];
    memset(res,0,get_strlen);
    for(int i = len;i < end;i++){
        strcat(res,word[i].arr);
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


list * branch_245(int arrlen){
    list *res = (list *)malloc(sizeof(list));
    memset(res,0,sizeof(list));
    treenode *trees[3];
    memset(trees,0,sizeof(trees));
    sqlitWord *w = word;
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
list * branch_256(int arrlen,int num){
    list *res = (list *)malloc(sizeof(list));
    memset(res,0,sizeof(list));
    treenode *trees[num];
    memset(trees,0,sizeof(trees));
    sqlitWord *w = word;
    w = w+arrlen;
    char *set;
    for (int i = 0; i < num; i++) {
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
        w+=2;
    }

    for(int i = 0;i < num;i++){
        add_list(res,trees[i]);
    }
    return res;
}
list * branch_257(int arrlen){
    list *res = (list *)malloc(sizeof(list));
   sqlitWord *p = word;
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

list * branch_258(int arrlen){
    list *res = (list *)malloc(sizeof(list));
    sqlitWord *p = word;
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


