//
// Created by maomao on 2021/2/9.
//
//跳表
#ifndef INDEXTSDB_SKIP_LIST_H
#define INDEXTSDB_SKIP_LIST_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <map>
#include "index_operation.h"

//#define MAX_LEVEL 30
//
//using namespace std;
//
//typedef struct Index_Entry{
//    int Offset;
//    int Size;
//};
////typedef list<char *> CHARLIST;
//typedef struct datalist{
//    char* tag;
//    char* value;
//    DataTypes dataTypes;
//    struct datalist* next;
//};
//
//typedef struct node {
//    node *right;  //后驱
//    node *down;   //下驱
//    long key;     //Key  timestame
////    CHARLIST list; //Value 数据容器,value是char*链表
//    struct  Index_Entry* indexEntry;//偏移量
//    struct datalist* list;//列
//} data_node;
//
//struct skip_list {
//    data_node **header;    //头指针
//    int max_level;    //最大层数
//    int size;   //基本链表中的节点数
//    char* database_tablename;    //database_tablename
//};
//static map<string, skip_list *> skip_tableMap;      //存放调表
//
//static map<skip_list**,int> Offset_size; //存放偏移量
//
////获取随机层
//int get_current_level();
//
////初始化跳表
//skip_list *skip_list_init(char* database_tablename);
//
//
////查找值
//data_node *find_x_from_skip_list(skip_list *sl, long timestamp);
//
////把数据插入到跳表中
//data_node *insert_x_into_list(node *head, long timestamp, char *data,tuple_column * columndata);
//
//int insert_x_into_skip_list(skip_list *sl, long timestamp, tuple_column * columndata);
//
//////删除跳表的数据
////int remove_data_from_list(node *head, long timestamp);
////删除跳表
//int remove_x_from_skip_list(skip_list *sl, long timestamp);
//
////销毁跳表
//int destory_skip_list(skip_list *sl);
//
////输出跳表
//int print_list(skip_list *sl);
//
////返回list中所有的元素
//void put_CharList(datalist* list);
//
////从map中查找调表
//skip_list *find_skiptable(char* database_tablename);



#endif //INDEXTSDB_SKIP_LIST_H
