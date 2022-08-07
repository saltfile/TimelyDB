//
// Created by saltfish on 2022/2/14.
//

#ifndef RESOLVE_MYALL_H
#define RESOLVE_MYALL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;

#define BUF_LEN 1024
#define SMALL_LEN 256
#define _END_ "END"
void log_info(string str);
void log_info(char *data);
void log_erro(char *data);
void log_erro(string data);
void log_debug(char *data);














//词法分析 代码:占林学长
typedef struct {
    int typenum;
    char *word;
} sqlWord;
typedef struct {
    int num;
    char arr[255];
} sqlitWord;




//接下来对分词的改变
typedef struct scan_word{
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
}scan_word;

sqlitWord get_word(scan_word *scan,int len);
scan_word * scanWordInit();
void initNumber(scan_word *scan);

int allFunc(scan_word *scan);
void sqlsacnner(scan_word *scan,char *sqlsource);
void clear_cache(scan_word *scan);
int get_wordlen(scan_word *scan);


//语法树
//此树是一颗语法树根据语法的一颗多叉树 //其中原理是先准备建立一颗树等语句进来在按个放进去用空间换取时间
typedef struct list{
    struct treenode *tree;//树节点
    struct list *prev;//后继
    struct list *next;//前驱
}list;

typedef struct treenode{
   char *str;
   int strlen = 0;
   int strtype = 0;
   struct list *nodelist;//节点列表
}treenode;
//链表函数

void add_list(list *root,treenode *node);
void dis_play(list *root);
int get_list_size(list *root);
treenode *get_list_node(list *root,int len);
list *remove_node(list *root,int len);
//程序运行初期建立一颗死树用来和后面程序语句作对照
treenode *check_tree(scan_word *scan);//先确定语句类型
//void create_sqltree();
void sql_sel(scan_word *scan,treenode *root);
void sql_ins(scan_word *scan,treenode *root);
void test();
//临时性传参结构体
typedef  struct colnm{
    int start;
    int type;
    int end;
    char *str;
};

colnm *get_colnm(scan_word *scan);
colnm *get_andcolum(scan_word *scan,int len);
void use_fun();
//字符串复制
char *str_copy(char *str,char *arr);
char * str_merge(char *str,char * merstr);
void tree_trim(treenode *root);


list * branch_245(scan_word *scan,int arrlen);
list * branch_256(scan_word *scan,int arrlen,int num);
list * branch_257(scan_word *scan,int arrlen);
list * branch_258(scan_word *scan,int arrlen);



treenode *init_sel();































#endif //RESOLVE_MYALL_H
