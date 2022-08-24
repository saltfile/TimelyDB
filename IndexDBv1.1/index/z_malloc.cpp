//
// Created by zy on 2022/4/2.
//

//
//#include "../Engine/database_engine.h"
//#include "../Server/ser_drive.h"
//#include "../primitive/primitive.h"
//#include "sql.h"
//#include "skip_list.h"
//#include "rb_tree.h"

#include "database_index.h"

tuple_column* malloc_tuple_colum(void);
/*sql.malloc
 * */
condition* malloc_sqlcondition(void){
    condition* con;
    con=(condition*)malloc(sizeof(condition));
    return con;
}

sql_operation* malloc_sqloperation(void){
    sql_operation* sqlOperation;
    sqlOperation=(sql_operation*)malloc(sizeof(sql_operation));

    sqlOperation->data_list=malloc_sqlcondition();
    return sqlOperation;
}
/*
 * skip.malloc
 * */
Index_Entry* malloc_sk_index_entry(void){
    Index_Entry* indexEntry;
    indexEntry=(Index_Entry*) malloc(sizeof(indexEntry));
    return  indexEntry;
}

datalist* malloc_sk_datalist(void){
    datalist*Datalist;
    Datalist=(datalist*)malloc(sizeof(datalist));
    return Datalist;
}

data_node * malloc_sk_node(void){
    data_node *dataNode;
    dataNode=(data_node*) malloc(sizeof(data_node));

    dataNode->indexEntry=malloc_sk_index_entry();
    dataNode->list=malloc_sk_datalist();

    return dataNode;
}
skip_list * malloc_sk_head(void){
    skip_list *head;
    head=(skip_list*)malloc(sizeof(skip_list));

    head->header=(data_node**)malloc_sk_node();
    return head;
}

/*rbtree.malloc
 * */
RBTreeNode * malloc_rb_node(void){
    RBTreeNode* node;
    node=(RBTreeNode*)malloc(sizeof(RBTreeNode));
    node->tag_values=malloc_tuple_colum();

    return node;
}

rb_root* malloc_rb_root(void){
    rb_root* rbRoot;
    rbRoot=(rb_root*)malloc(sizeof(rb_root));

    rbRoot->node=malloc_rb_node();
    rbRoot->rbhead=(Node **)malloc_rb_node();
    return rbRoot;
}

rbtree_result_timestamp* malloc_rb_timestamp(void){
    rbtree_result_timestamp* rbtreeResultTimestamp;
    rbtreeResultTimestamp=(rbtree_result_timestamp*)malloc(sizeof(rbtree_result_timestamp));
    return rbtreeResultTimestamp;
}
/*
 * sql_operation.malloc
 * */
value_tuple * malloc_tuple(void){
    value_tuple* tuple;
    tuple= (value_tuple*)malloc(sizeof(tuple));
    return tuple;
}
tuple_column* malloc_tuple_colum(void){
    tuple_column* tupleColumn;
    tupleColumn=(tuple_column*)malloc(sizeof(tuple_column));

    tupleColumn->datalist=malloc_tuple();
    return tupleColumn;
}

tuple_head* malloc_tuple_head(void){
    tuple_head* tupleHead;
    tupleHead=(tuple_head*)malloc(sizeof(tuple_head));
    tupleHead->fileds=malloc_tuple_colum();
    return tupleHead;
}
