//
// Created by saltfish on 23-5-23.
//
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <error.h>
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
#include <iostream>
#include <queue>

using namespace std;
#ifndef TIMELYDB_V0_1_2_T_POOL_H
#define TIMELYDB_V0_1_2_T_POOL_H

#define LIST_LAST(pos, head) \
    for (pos =(head) ;pos->next ;pos = pos->next)

#define LIST_FOREACH(pos, head) \
    for (pos =(head) ;pos->next ;pos = pos->next)

#define LIST_ADD_TAIL(head, pos, node) \
    for (pos =(head) ;pos->next ;pos = pos->next);            \
    pos->next = node;                  \
    node->prev = pos;                  \



typedef struct tylist_node {
    tylist_node *prev;
    tylist_node *next;
} tylist_node;

template<typename T>
class tylink_list {
private:
    struct tylist_node list;

    T data;
    int length = -1;
    int aim = -1;
public:
    void init_node(T data) {
        this->data = data;
    }

    void set_data(T data) {
        this->data = data;
    }

    T get_data() {
        return this->data;
    }


};


//TODO:block_queue重做 c撰写内核链表






#endif //TIMELYDB_V0_1_2_T_POOL_H
