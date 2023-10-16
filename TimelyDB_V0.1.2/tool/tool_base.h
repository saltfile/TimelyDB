//
// Created by saltfish on 23-4-17.
//

#ifndef TIMELYDB_V0_1_2_TOOL_BASE_H
#define TIMELYDB_V0_1_2_TOOL_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;
//基本的list宏

#define LIST_LAST(pos, head) \
    for (pos =(head) ;pos->next ;pos = pos->next)

#define LIST_FOREACH(pos, head) \
    for (pos =(head) ;pos->next ;pos = pos->next)

#define LIST_FOR(pos, head, idx) \
    pos = head;                \
    for(int i = 0;i < idx-1;i++){\
    pos = pos->next;           \
    }                            \
pos = pos->next;

#define LIST_ADD_TAIL(head, pos, node) \
    for (pos =(head) ;pos->next ;pos = pos->next);            \
    pos->next = node;                  \
    node->prev = pos;                  \


#define CONTAINER_OF(head, type, pos) \
   head = ((typeof(type) *)((char *)(pos)-(unsigned long )(&((typeof(type)*)0)->list)));

#define CREATE_BASE_LIST(ptr) \
ptr = (tylist_node*) malloc(sizeof (tylist_node));\
memset(ptr,0,sizeof(ptr))


#define CREATE_COLLECTION(ptr) \
ptr = (collection *) malloc(sizeof(collection)); \
memset(ptr, 0, sizeof(ptr));

#define CREATE_ARRLIST(ptr) \
ptr = (arr_list *)malloc(sizeof(arr_list)); \
memset(ptr,0,sizeof(arr_list));             \
ptr->arr_list(); \





typedef struct tylist_node {
    tylist_node *prev;
    tylist_node *next;
} tylist_node;


//QUEUE
struct collection {
public:
    void *data;
    struct tylist_node list;

    void set_data(void *data) {
        this->data = data;
    }

    void *get_data() {
        return this->data;
    }
};

struct arr_list {
public:
    int length = 0;
    int aim = -1;
    collection *collect = NULL;

    void initialization() {
        this->collect = CREATE_COLLECTION(this->collect);
    }

    void arr_list_add(void *data) {
        //1.拿到当前list句柄
        collection *ptr = this->collect;
        //2.初始化新节点
        collection *new_node = NULL;
        CREATE_COLLECTION(new_node);
        //3.赋值NULL
        new_node->list.next = NULL;
        new_node->list.prev = NULL;
        new_node->set_data(data);
        //4.添加到末尾
        tylist_node *temp = NULL;

        for (temp =(&ptr->list) ;temp->next ;temp = temp->next);
        temp->next = &new_node->list;
        new_node->list.prev = temp;
//        LIST_ADD_TAIL(&ptr->list, temp, &new_node->list);
        //5.长度加一
        this->length++;
    }


    void *get(int idx) {
        //1.拿到句柄
        tylist_node *ptr = &this->collect->list;
        tylist_node *p = NULL;
        //2.拿到对应的下标
        LIST_FOR(p, ptr, idx);
//        //3.置换出来返回结果
        collection *res = NULL;
        CONTAINER_OF(res,collection,p);
        return res->data;
    }

    void arr_list_remove(int idx) {

    }


};









//字符串框架

//字符串赋值
char *str_copy(char *str1, char *str2);

//字符串合并
char *str_marge(char *str1, char *str2);

//字符穿拆分
int str_spilt_size(char *a, char *b);

char **str_spilt(char *str, char *dent);


//释放字符串函数
char *free_str(char *str);


#endif //TIMELYDB_V0_1_2_TOOL_BASE_H
