//
// Created by saltfish on 2022/9/7.
//

#ifndef MYPOOL_BASIC_FUNCTION_H
#define MYPOOL_BASIC_FUNCTION_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <cstring>
#include <zconf.h>
using namespace std;


typedef struct task{
    void* arg;
    void (*func)(void *arg);//被执行函数指针
};

typedef struct thread_pool{
    task* tasks;//任务队列

    int capacity;//队列容量
    int current;//当前任务个数
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
}thead_pool;

thead_pool *pool_init(int work_num,int min,int queue_size);


void* admin(void* arg);
void* work(void* arg);
void pool_exit(thead_pool *pool);

void pool_add_task(thead_pool *pool,void (*func)(void*),void* arg);


int get_pool_live_num(thread_pool* pool);
int get_pool_working_num(thread_pool* pool);

int pool_destory(thead_pool* pool);
//测试用函数
int test_pool();
#endif //MYPOOL_BASIC_FUNCTION_H
