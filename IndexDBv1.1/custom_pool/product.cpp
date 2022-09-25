//
// Created by saltfish on 2022/9/23.
//
#include "basic_function.h"


void pool_add_task(thead_pool *pool, void (*func)(void *), void *arg) {


    pthread_mutex_lock(&pool->pool_lock);
    cout<<"我添加了"<<endl;


    while (pool->current == pool->capacity && !pool->poweroff) {
        pthread_cond_wait(&pool->full_vbe, &pool->pool_lock);
    }


    if (pool->poweroff) {
        pthread_mutex_unlock(&pool->pool_lock);
    }


    //添加任务
    pool->tasks[pool->queue_head].func = func;
    pool->tasks[pool->queue_head].arg = arg;
    pool->queue_tail = (pool->queue_tail + 1) % pool->capacity;
    pool->current++;


    pthread_cond_signal(&pool->empty_vbe);


    pthread_mutex_unlock(&pool->pool_lock);



}






