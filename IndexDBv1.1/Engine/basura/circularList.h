////
//// Created by mikasa on 2022/4/15.
////
//
//#ifndef G_TEST_CIRCULARLIST_H
//#define G_TEST_CIRCULARLIST_H
//
//#include "global_c.h"
//#include "vfsTree.h"
//#include "../com.h"
//
////#include "wal.h"
//typedef struct tuple{
//
//    char * timestamp;
//    //数据的值
//    char * value;
////    //数据的类型
////    enum DataTypes dataType;
//
//    struct tuple * next;
//}value_tuple;
//
//
//typedef struct tuple_column{
//    //列名
//    char * columnname;
//    //数据类型
//    enum DataTypes dataTypes;
//
//    //数据
//    value_tuple * datalist;
//
//
//    value_tuple * listtail;
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
//
//    struct tuple_head * next;
//
//    char * min_time;//当前链还未落盘的最早时间戳
//
//    char * max_time;//当前链的最晚时间戳
//
//
//}head_tuple;
////
//
////typedef struct circularList;
////用于存放数据
////typedef struct circularListNode{
////    //index
////    long index;
////    //数据类型
////    enum DataTypes datatype;
////    //数据
////    value_tuple * values;
////偏移量
////    int offsetSize;
////    //下一个数据
////    struct circularListNode* next;
////
////    head_tuple * headdata;
//
////    struct circularList * head;
//
////}CircularNode;
//
//
//
////用于存数据上层信息
//typedef struct circularList{
////    //数据库名
////    char* databaseName;
////    //表名
////    char* tableName;
////    //文件路径
////    char* filePath;
////    //头节点
////    CircularNode *head;
//
////    head_tuple * headdata;
//
//    time_t earliest_time;
//
//    long int size;  //单位为MB
//
////    long index;
//
//    head_tuple * next;
//
//    int is_fulied;
//}CircularList;
//
////执行 use databasename操作的函数
//int use_database(char * databasename);
////执行插入语句的函数
//void * create_cir_nodelist(char * databasename,char * tablename,tuple_column * columns,value_tuple * datas);
////初始化环形列表的函数
//CircularList *initCircularList(long int cyclelength);
////遍历环形链表的函数
//void foreach_cirlist();
////获取窗口数据的函数
//tuple_column * time_window(char * tablename,char * start,char * end);
//tuple_column * search_disk(char * tablename,char * targetpath,int begin,int end);
//
//void * manager_writedisk(long int reserve_time);
//#endif //G_TEST_CIRCULARLIST_H
