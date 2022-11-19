////
//// Created by mikasa on 2022/1/20.
////

#ifndef G__TEST_DATABASE_ENGINE_H
#define G__TEST_DATABASE_ENGINE_H
#pragma once
#include <dirent.h>
#include "../global_c.h"
#include "../snappy/snappy.h"
//#include "../index/database_index.h"

using namespace std;
/////////////////////////////////////////////////////////////circularlist.h
//#define DEFAULT_PATH="/home/maomao/CLionProjects/index-tsdb/IndexTSDB_v1.0/data/"
////FILE *readFile;
////char buf[1024]={0};
////元组数据
typedef struct tuple{

    char * timestamp;
    //数据的值
    char * value;
    //数据的类型
//    enum DataTypes dataType;

    struct tuple * next;
}value_tuple;
typedef struct tuple_column{
    //列名
    char * columnname;
    //数据类型
    enum DataTypes dataTypes;

    //数据
    value_tuple * datalist;


    value_tuple * listtail;

    struct tuple_column * nextcolumn;
};


//元组数据的元数据头节点
typedef struct tuple_head{
    //数据库名
    char * databasename;
    //表名
    char * tablename;

    //属性
    struct tuple_column * fileds;

    struct tuple_head * next;

    char * min_time;//当前链还未落盘的最早时间戳

    char * max_time;//当前链的最晚时间戳


}head_tuple;
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
//用于存数据上层信息
typedef struct circularList{
//    //数据库名
//    char* databaseName;
//    //表名
//    char* tableName;
//    //文件路径
//    char* filePath;
//    //头节点
//    CircularNode *head;

//    head_tuple * headdata;

    time_t earliest_time;

    long int size;  //单位为MB

//    long index;

    head_tuple * next;

    int is_fulied;
}CircularList;
//
////执行 use databasename操作的函数
int use_database(char * databasename);
//检测用户是否use成功
int use_detect();
////执行插入语句的函数
int create_cir_nodelist(char * databasename,char * tablename,tuple_column * columns,value_tuple * datas);
////初始化环形列表的函数
CircularList *initCircularList(long int cyclelength);
////遍历环形链表的函数
void foreach_cirlist();
////获取窗口数据的函数
tuple_column * time_window(char * tablename,char * start,char * end);
tuple_column * search_disk(char * tablename,char * targetpath,int begin,int end);
//
void * manager_writedisk(long int reserve_time);
////////////////////////////////////////////////////////////engine.h
//
///////////////////////////////////////////////////////////loaddisk.h
void * load_disk_method(head_tuple * load_list);
//
//////////////////////////////////////////////////////////ops.h
typedef struct database{
    char * location;
}Database;
//
char *mkdir_database(char * databasename);
bool touch_table(char * databasename,char * tablename,char** columns,int columnSize);
void rm_database(char * databasename);
void rm_table(char * databasename,char * tablename);
/////////////////////////////////////////////////////////pthread_myrwlock.h
extern int pthread_myrwlock();
extern void pthread_myrwlock_rdlock();
extern void pthread_myrwlock_wrlock();
extern void pthread_myrwlock_unlock();
extern int pthread_myrwlock_init();
/////////////////////////////////////////////////////////vfsTree.h
typedef  enum{
    IFalse=0,ITrue=1,Ierror=-1
}IBool;

////文件树节点
typedef struct vfsNode{
    int level;         //节点等级
    char* name;        //name
    int flag;          //标志位
    struct vfsNode *parentNode; //父节点
    struct vfsNode *next;       //下一个节点的位置
    struct childList *cList;    //孩子链表
    char * filepath;
}VfsNode;
//
////文件树
typedef struct vfsTree{
    VfsNode *root;
    struct vfsTree * next;
}VfsTree;
//文件树节点中的子链表
typedef struct childList{
    int size;
    VfsNode *head;
    VfsNode *tail;
}ChildList;

////初始化孩子链表头节点
ChildList * InitHeadNode();
//
////生成节点
VfsNode * createNode(int level,char *name,int flag,VfsNode* next,VfsNode *parentNode,ChildList * cList);
//
////遍历链表查看是否有相同的名字  -1表示错误
IBool   foreachListByName(ChildList *list ,char *name);
//
////查找节点
VfsNode *findNodeByName(ChildList *list,char* name);
//
////遍历子链表
char *  foreachList(ChildList* list);
//
////销毁节点
void * deleteNode(VfsNode* node);
//
////删除节点
IBool removeNode(ChildList *list,char* name);
//
////销毁链表
void  deleteList(ChildList *list);
//
////初始化VfsTree
VfsTree * InitRootNode();
//
////遍历数据库
char* showDataBase();
//
////添加数据库信息
IBool addVfsTreeNode(VfsNode *parentNode,VfsNode* childNode);
//
////遍历表
char* showTables(char* databaseName);
//
////遍历列
char* showColumn(char* databaseName,char* tableName);
//
//销毁列节点
void* destroyVfsTree(VfsTree* vfsTree );
//
VfsTree * createVfsTreeRoot();
//
//
VfsNode* findDataBaseByName(char* dbName);
extern VfsTree *vfsTreeRoot;
extern VfsNode *root;
/////////////////////////////////////////////////////////////////wal.h
typedef struct ahead_log{
    char * message;
}ahead_log;

char * read_meta_log();
void * update_meta_log(char * timestamp);
int write_ahead_log(char * timestamp,char * databasename,char * tablename,value_tuple * values);
IBool load_ahead_log(head_tuple * load_list);
//////////////////////////////////////////////////////////////////
//
void add_value(value_tuple *root,char *timestamp,char* value);

passwd* get_user();





//通过数据库名字和表名查询是否存在这个表
VfsNode *find_table_by_name(char* tab);

//查看数据库的数量
int get_databse_num();
//获取所有数据库名字
char** find_database();
//获取所有表名
char ** find_tables(char *database_path);
int get_tables_num(char *database_path);
int get_conlum_size(char *conms_path);
char **conlum_apply(char* clonms_path);

char*show_database_panle();
void engine_init(int mem_size);
char* show_table_panle();


typedef struct load_node{
    value_tuple *data;
    load_node *next;
}load_node;

//落盘
typedef struct load_lists{
    int size;
    load_node *head;
    load_node *tail;
    load_node *next;
}load_lists;

bool task_head_t(head_tuple* root);
//  清空所有的数据除了next
void clear_head_t(head_tuple* root);

void add_value_node(value_tuple *root,value_tuple *new_node);



void free_string(char* root);
//关于节点数据之间的拷贝
void head_tuple_data_copy(head_tuple * root, head_tuple *copied);
#endif //G__TEST_DATABASE_ENGINE_H
