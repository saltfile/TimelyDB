//
// Created by saltfish on 23-4-19.
//

#ifndef TIMELYDB_V0_1_2_TREE_BASE_H
#define TIMELYDB_V0_1_2_TREE_BASE_H
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cstring>
#include <iostream>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <typeinfo>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <random>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <future>
#include <cstdlib>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <stdexcept>
//#include <exception>
#include "../tool/tool_base.h"
#include "../config_init/config_h.h"


using namespace std;
#define BUF_LEN 1024
#define SMALL_LEN 256
#define _END_ "END"
void word_test();

//词法分析
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
//typedef struct list{
//    struct treenode *tree;//树节点
//    struct list *prev;//后继
//    struct list *next;//前驱
//}list;
//
//typedef struct treenode{
//    char *str;
//    int strlen = 0;
//    int strtype = 0;
//    struct list *nodelist;//节点列表
//}treenode;
//链表函数


void test_fire();





#endif //TIMELYDB_V0_1_2_TREE_BASE_H
