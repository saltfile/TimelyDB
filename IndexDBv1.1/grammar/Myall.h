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
sqlitWord get_word(int len);
void initNumber();

int allFunc();
void sqlsacnner(char *sqlsource);
void clear_cache();
int get_wordlen();


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
treenode *check_tree();//先确定语句类型
void check_fun(treenode *sql);
void create_sqltree();
void sql_sel(treenode *root);
void sql_ins(treenode *root);
void test();
//临时性传参结构体
typedef  struct colnm{
    int start;
    int type;
    int end;
    char *str;
};

colnm *get_colnm();
colnm *get_andcolum(int len);
void use_fun();
//字符串复制
char *str_copy(char *str,char *arr);
char * str_merge(char *str,char * merstr);
void tree_trim(treenode *root);


list * branch_245(int arrlen);
list * branch_256(int arrlen,int num);
list * branch_257(int arrlen);
list * branch_258(int arrlen);



#endif //RESOLVE_MYALL_H
