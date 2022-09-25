//
// Created by saltfish on 2022/9/23.
//

#include "basic_function.h"
//主要的功能函数实现

#define NUMBRE 2





void* work(void* arg){
    thead_pool* pool = (thread_pool*)arg;
    while (1){
        pthread_mutex_lock(&pool->pool_lock);

        //当前任务队列如果为空并且线程池没有关闭
        while (pool->current == 0&& !pool->poweroff){
            //阻塞工作线程
            pthread_cond_wait(&pool->empty_vbe,&pool->pool_lock);

            if (pool->live_num > 0){
                pool->kill_num--;
                if (pool->live_num > pool->min_size){
                pool->live_num--;
                pthread_mutex_unlock(&pool->pool_lock);
                pool_exit(pool);
                }
            }
        }

        //判断线程池是否被关闭
        if (pool->poweroff){
            pthread_mutex_unlock(&pool->pool_lock);
            pool_exit(pool);
        }

        //开始消费线程
        task task;
        task.func = pool->tasks[pool->queue_head].func;
        task.arg = pool->tasks[pool->queue_head].arg;
        //循环队列->如果对其中的长度进行取余那么运行到最后一个的时候+1取余刚好为0，就刚好回到队列的开头
        pool->queue_head = (pool->queue_head+1)%pool->capacity;
        pool->current--;
        pthread_cond_signal(&pool->full_vbe);
        pthread_mutex_unlock(&pool->pool_lock);
        //正在忙的线程需要处理
        pool->working_num++;
        pthread_mutex_lock(&pool->working_lock);
        task.func(task.arg);
        task.arg = NULL;

        pthread_mutex_unlock(&pool->working_lock);
        pool->working_num--;
        pthread_mutex_unlock(&pool->working_lock);


    }
    return NULL;

}

void* admin(void* arg){
    thead_pool* pool = (thread_pool*)arg;

    while ( pool->poweroff != 0){
        sleep(5);

        //取出线程池中任务数量和当前线程数量
        pthread_mutex_lock(&pool->pool_lock);
        int present = pool->current;
        int live = pool->live_num;
        pthread_mutex_unlock(&pool->pool_lock);

        //取出正在忙的线程数量
        pthread_mutex_lock(&pool->working_lock);
        int busy = pool->working_num;
        pthread_mutex_unlock(&pool->working_lock);

        //添加线程
        //当当前任务个数大于存活线程个数并且存活线程数小于最大线程数
        if (present > live && live < pool->max_size){
            int count = 0;
            for(int i = 0 ;i < pool->max_size&&count < 2&&pool->live_num < pool->max_size;i++){
                if (pool->works[i] == 0){
                    pthread_create(&pool->works[i],NULL,work,pool);
                    count++;
                    pool->live_num++;
                }

            }
        }


        //销毁线程
        //忙的线程*2小于存活的线程并且存活的线程小于最小线程数
        if (busy*2 < live&&live < pool->min_size){

            pthread_mutex_lock(&pool->pool_lock);
            pool->kill_num = NUMBRE;
            pthread_mutex_unlock(&pool->pool_lock);
            //杀死线程
            for (int i = 0; i < NUMBRE; ++i) {
                pthread_cond_signal(&pool->empty_vbe);
            }
        }

    }






}



