//
// Created by mikasa on 2022/4/24.
//
#ifndef INDEXDBV1_1_DATABASE_INDEX_H
#define INDEXDBV1_1_DATABASE_INDEX_H
#define RED        0    // 红色节点
#define BLACK    1    // 黑色节点
#include "../Engine/database_engine.h"
#include "../primitive/primitive.h"
struct sql_operation;
////////////////////////////////////////////cprocess.h
//存红黑树（二级索引）的时间戳集
typedef struct rbtree_result_timestamp{
    char* timestamp;
    struct rbtree_result_timestamp* next;
}Result;
//生成过滤的结构体，之后将数据填入，运行刘闯的方法。
typedef struct pri{
    char* res;
    int columNum;
    int aim_values;
    TokenType ty;

}PRI;


tuple_head * create_rbtree_index(tuple_head *pHead);
void create_skip_index(tuple_head* tupleHead);

void delete_index(tuple_head* tupleHead);
void delete_rbtree_index(char* database_tablename,sql_operation* sql,tuple_head* tupleHead);
void delete_skip_index(char* database_tablename, char* timestamps);

void find_rbtree_data(char* swar, sql_operation* b, tuple_head* tupleHead);
char* find_skip_data(char* database_tablename, char* timestamps, char*  databasename);
char* dbname_tname(tuple_head* tupleHead);

///////////////////////////////////////////////////rb_tree.h
using namespace std;

typedef int Type;


// 红黑树的节点
typedef struct RBTreeNode{
    unsigned char color;        // 颜色(RED 或 BLACK)
//    Type   key;     // 关键字(键值)
    tuple_column* tag_values;
    struct RBTreeNode *left;    // 左孩子
    struct RBTreeNode *right;    // 右孩子
    struct RBTreeNode *parent;    // 父结点
}Node, *RBTree;

// 红黑树的根
typedef struct rb_root{
    Node ** rbhead;
    Node *node;
    char *database_tablename;

}RBRoot;

// 创建红黑树，返回"红黑树的根"！
RBRoot* create_rbtree();

// 销毁红黑树
void destroy_rbtree(RBRoot *root);

// 将结点插入到红黑树中。插入成功，返回0；失败返回-1。
void rbtree_insert(RBRoot *root, Node* node);

// 删除结点(key为节点的值)
void rbtree_delete(RBRoot *root, sql_operation* sql);


// 前序遍历"红黑树"
void preorder_rbtree(RBRoot *root);
// 中序遍历"红黑树"
void inorder_rbtree(RBRoot *root);
// 后序遍历"红黑树"
void postorder_rbtree(RBRoot *root);

// (递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
rbtree_result_timestamp* rbtree_search(RBRoot *root, char* tag,char* dest,TokenType symbol);

// (非递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
int iterative_rbtree_search(RBRoot *root,  char* tag,char* dest,TokenType symbol);

// 返回最小结点的值(将值保存到val中)。找到的话，返回0；否则返回-1。
int rbtree_minimum(RBRoot *root, int *val);
// 返回最大结点的值(将值保存到val中)。找到的话，返回0；否则返回-1。
int rbtree_maximum(RBRoot *root, int *val);

// 打印红黑树
void print_rbtree(RBRoot *root);


/**
 * 存入表的结构在map中
 */
void set_map_node(char* database_tablename,sql_operation* sql);
/**
 * 查找要插入数据的表的结构，生成Node,方便数据的插入
 */
sql_operation *get_map_node(char* database_tablename);

RBRoot *rbTree_init(char* database_tablename); //初始化红黑树
static map<string , RBRoot *> rbtree_tableMap;      //存放红黑树
RBRoot *find_rbTree(char* database_tablename);//从map中查找红黑树
static map<string, sql_operation *> map_node;      //存放表结构

////////////////////////////////////////////////////skip_list.h
#define MAX_LEVEL 30

using namespace std;

typedef struct Index_Entry{
    int Offset;
    int Size;
};
//typedef list<char *> CHARLIST;
typedef struct datalist{
    char* tag;
    char* value;
    DataTypes dataTypes;
    struct datalist* next;
};

typedef struct node {
    node *right;  //后驱
    node *down;   //下驱
    long key;     //Key  timestame
//    CHARLIST list; //Value 数据容器,value是char*链表
    struct  Index_Entry* indexEntry;//偏移量
    struct datalist* list;//列
} data_node;

struct skip_list {
    data_node **header;    //头指针
    int max_level;    //最大层数
    int size;   //基本链表中的节点数
    char* database_tablename;    //database_tablename
};
static map<string, skip_list *> skip_tableMap;      //存放调表

static map<skip_list**,int> Offset_size; //存放偏移量

//获取随机层
int get_current_level();

//初始化跳表
skip_list *skip_list_init(char* database_tablename);


//查找值
data_node *find_x_from_skip_list(skip_list *sl, long timestamp);

//把数据插入到跳表中
data_node *insert_x_into_list(node *head, long timestamp, char *data,tuple_column * columndata);

int insert_x_into_skip_list(skip_list *sl, long timestamp, tuple_column * columndata);

////删除跳表的数据
//int remove_data_from_list(node *head, long timestamp);
//删除跳表
int remove_x_from_skip_list(skip_list *sl, long timestamp);

//销毁跳表
int destory_skip_list(skip_list *sl);

//输出跳表
int print_list(skip_list *sl);

//返回list中所有的元素
void put_CharList(datalist* list);

//从map中查找调表
skip_list *find_skiptable(char* database_tablename);
////////////////////////////////////////////////////////////sql.h
enum Handler{
    CREATE_DATABASE,
    CREATE_TABLE,
    INSERTINTO,
    SELECTS,
    DELETE,
    USE,
    DROP_DATABASE,
    DROP_TABLE
};

struct condition{

    char* c_name;//tag名
    enum TokenType c_symbol;//> < =
    char* c_value;//值
    enum TokenType cTypes;
    enum DataTypes dataTypes;

    struct condition* next;
};
struct sql_operation{
    enum Handler handler;
    char* name;// databasename or tbname
    char* field;//*
    char * timestamp;//时间戳
//    int condition_size;//默认为0
    struct condition* data_list;

};

void sql_oper_insrtinto(sql_operation* sql);
void sql_oper_delete(sql_operation* sql);
void sql_oper_select(sql_operation* sql);
void sql_oper_drop_table(sql_operation* sql);
void sql_oper_drop_database(sql_operation* sql);
void sql_oper_use(sql_operation* sql);
void sql_oper_create_table(sql_operation* sql);
void sql_oper_create_database(sql_operation* sql);
/////////////////////////////////////////////////////zmalloc.h
condition* malloc_sqlcondition(void);
sql_operation* malloc_sqloperation(void);
/*
 * skip.malloc
 * */
Index_Entry* malloc_sk_index_entry(void);
datalist* malloc_sk_datalist(void);
data_node * malloc_sk_node(void);
skip_list * malloc_sk_head(void);

/*rbtree.malloc
 * */
RBTreeNode * malloc_rb_node(void);
rb_root* malloc_rb_root(void);

rbtree_result_timestamp* malloc_rb_timestamp(void);
/*
 * sql_operation.malloc
 * */
value_tuple * malloc_tuple(void);
tuple_column* malloc_tuple_colum(void);

tuple_head* malloc_tuple_head(void);
///////////////////////////////////////////test.h
int z_index();
#endif //INDEXDBV1_1_DATABASE_INDEX_H
