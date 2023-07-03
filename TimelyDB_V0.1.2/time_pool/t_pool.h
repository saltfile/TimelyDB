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


#define CONTAINER_OF(head,type,pos) \
   head = ((typeof(type) *)((char *)(pos)-(unsigned long )(&((typeof(type)*)0)->list)))






typedef struct tylist_node {
    tylist_node *prev;
    tylist_node *next;
} tylist_node;
//QUEUE
template<typename T>
class tylink_list {
private:
    T data;
    int length = -1;
    int aim = -1;
public:
    tylist_node list;
    tylink_list(T data) {
        this->data = data;
//        this->list = (tylist_node *) malloc(sizeof(tylist_node));
    }

    void set_data(T data) {
        this->data = data;
    }

    T get_data() {
        return this->data;
    }


};


//TODO:block_queue重做 c撰写内核链表




class task{
public:
    void* arg;
    void (*func)(void *arg);//被执行函数指针
};

class thread_pool{
public:
    vector<task> vector;
    int currt;//当前任务量
    int capacity;//队列容量
    int queue_head;//队列头   获取数据
    int queue_tail;//队列尾   放进数据

    pthread_t admin;//管理员线程
    pthread_t *works;//工作线程

    int max_size;//工作线程组最大容量
    int min_size;//工作线程组最小容量
    int working_num;//正在工作的线程数量
    int live_num;//存活的线程数量
    int kill_num;//杀死线程的个数

    pthread_mutex_t pool_lock;//线程池的互斥锁
    pthread_mutex_t working_lock;//给正在工作的线程数加一层锁保护

    pthread_cond_t full_vbe;//任务队列满
    pthread_cond_t empty_vbe;//任务队列空

    int poweroff;//销毁线程池 0开 1关

   thread_pool(int work_num,int min,int queue_size){
       do {
           this->currt = 0;
           if (work_num < 1)break;
           if (queue_size < 2)break;
           if (min > work_num||min < 0)break;
           this->max_size = work_num;
           this->min_size = min;
           this->live_num = min;
           this->working_num = 0;
           this->kill_num = 0;

           this->capacity = queue_size;
           this->queue_head = 0;
           this->queue_tail = 0;

           if (pthread_mutex_init(&this->pool_lock, NULL) != 0 ||
               pthread_mutex_init(&this->working_lock, NULL) != 0 ||
               pthread_cond_init(&this->empty_vbe, NULL) != 0 ||
               pthread_cond_init(&this->full_vbe, NULL) != 0) {

               perror("初始化锁失败");
               break;
           }




           pthread_create(&this->admin, NULL, reinterpret_cast<void *(*)(void *)>(contoller_p), this);
           for (int i = 0; i < min; ++i) {
               pthread_create(&this->works[i], NULL, reinterpret_cast<void *(*)(void *)>(work), pool);
           }





           this->poweroff = 1;

           cout<<"任务池初始化成功"<<endl;

           return;
       } while (0);

       this->poweroff = 0;


   }




};

















#endif //TIMELYDB_V0_1_2_T_POOL_H
