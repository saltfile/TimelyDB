#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

//#define RED        0    // 红色节点
//#define BLACK    1    // 黑色节点
//#include <map>
//#include "index_operation.h"
//#include "sql.h"
//
//using namespace std;
//
//typedef int Type;
//
//
//// 红黑树的节点
//typedef struct RBTreeNode{
//    unsigned char color;        // 颜色(RED 或 BLACK)
////    Type   key;     // 关键字(键值)
//    tuple_column* tag_values;
//    struct RBTreeNode *left;    // 左孩子
//    struct RBTreeNode *right;    // 右孩子
//    struct RBTreeNode *parent;    // 父结点
//}Node, *RBTree;
//
//// 红黑树的根
//typedef struct rb_root{
//    Node ** rbhead;
//    Node *node;
//    char *database_tablename;
//
//}RBRoot;
//
//// 创建红黑树，返回"红黑树的根"！
//RBRoot* create_rbtree();
//
//// 销毁红黑树
//void destroy_rbtree(RBRoot *root);
//
//// 将结点插入到红黑树中。插入成功，返回0；失败返回-1。
//void rbtree_insert(RBRoot *root, Node* node);
//
//// 删除结点(key为节点的值)
//void rbtree_delete(RBRoot *root, sql_operation* sql);
//
//
//// 前序遍历"红黑树"
//void preorder_rbtree(RBRoot *root);
//// 中序遍历"红黑树"
//void inorder_rbtree(RBRoot *root);
//// 后序遍历"红黑树"
//void postorder_rbtree(RBRoot *root);
//
//// (递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
//rbtree_result_timestamp* rbtree_search(RBRoot *root, char* tag,char* dest,TokenType symbol);
//
//// (非递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
//int iterative_rbtree_search(RBRoot *root,  char* tag,char* dest,TokenType symbol);
//
//// 返回最小结点的值(将值保存到val中)。找到的话，返回0；否则返回-1。
//int rbtree_minimum(RBRoot *root, int *val);
//// 返回最大结点的值(将值保存到val中)。找到的话，返回0；否则返回-1。
//int rbtree_maximum(RBRoot *root, int *val);
//
//// 打印红黑树
//void print_rbtree(RBRoot *root);
//
//
///**
// * 存入表的结构在map中
// */
//void set_map_node(char* database_tablename,sql_operation* sql);
///**
// * 查找要插入数据的表的结构，生成Node,方便数据的插入
// */
//sql_operation *get_map_node(char* database_tablename);
//
//RBRoot *rbTree_init(char* database_tablename); //初始化红黑树
//static map<string , RBRoot *> rbtree_tableMap;      //存放红黑树
//RBRoot *find_rbTree(char* database_tablename);//从map中查找红黑树
//static map<string, sql_operation *> map_node;      //存放表结构


#endif