//
// Created by zy on 2022/1/22.
//

#ifndef INDEX_ZY_INDEX_OPERATION_H
#define INDEX_ZY_INDEX_OPERATION_H

#include <ctime>
#include "sql.h"
#include "../../Engine/database_engine.h"
//#include "../Engine/circularList.h"
//#include "sql.h"

//元组数据
//typedef struct tuple{
//
//    char * timestamp;//时间戳
//    char * value;//数据的值
//
//    struct tuple * next;
//}value_tuple;
//
//typedef struct tuple_column{
//    //列名
//    char * columnname;
//    //数据类型
//    DataTypes dataTypes;
//
//    //数据
//    struct tuple * datalist;
//
//    struct tuple_column * nextcolumn;
//};
//
//
////元组数据的元数据头节点
//typedef struct tuple_head{
//    //数据库名
//    char * databasename;
//    //表名
//    char * tablename;
//
//    //属性
//    struct tuple_column * fileds;
//}head_tuple;

////存红黑树（二级索引）的时间戳集
//typedef struct rbtree_result_timestamp{
//    char* timestamp;
//    struct rbtree_result_timestamp* next;
//}Result;
//
//////用于存数据上层信息
////typedef struct circularList{
////    //数据库名
////    char* databaseName;
////    //表名
////    char* tableName;
////    //文件路径
////    char* filePath;
////
////    //头节点
//////    CircularNode *head;
////    time_t earliest_time;
////
////    long int size;  //单位为MB
//////
////////    long index;
//////    CircularNode * next;
////
////    int is_fulied;
////}CircularList;
//
//
////生成过滤的结构体，之后将数据填入，运行刘闯的方法。
//typedef struct pri{
//    char* res;
//    int columNum;
//    int aim_values;
//    TokenType ty;
//
//}PRI;
//
//
//void create_rbtree_index(tuple_head *pHead);
//void create_skip_index(tuple_head* tupleHead);
//
//void delete_index(tuple_head* tupleHead);
//void delete_rbtree_index(char* database_tablename,sql_operation* sql,tuple_head* tupleHead);
//void delete_skip_index(char* database_tablename, char* timestamps);
//
//void find_rbtree_data(char* swar, sql_operation* b, tuple_head* tupleHead);
//char* find_skip_data(char* database_tablename, char* timestamps, char*  databasename);
//char* dbname_tname(tuple_head* tupleHead);

#endif //INDEX_ZY_INDEX_OPERATION_H
