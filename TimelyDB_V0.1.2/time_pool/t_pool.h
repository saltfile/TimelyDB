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



#define NUMBRE 2
void* contoller_p(void* arg);
void* work(void* arg);









//TODO:block_queue重做 c撰写内核链表





























class task{
public:
    void* arg;
    void (*func)(void *arg);//被执行函数指针
};

class thread_pool{
public:
    vector<task> tasks;
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

           this->works = (pthread_t *) malloc(sizeof(pthread_t) * work_num);
           memset(this->works, 0, sizeof(pthread_t) * work_num);
           if (this->works == NULL) {
               perror("工作线程组创建失败");
               break;
           }

           if (pthread_mutex_init(&this->pool_lock, NULL) != 0 ||
               pthread_mutex_init(&this->working_lock, NULL) != 0 ||
               pthread_cond_init(&this->empty_vbe, NULL) != 0 ||
               pthread_cond_init(&this->full_vbe, NULL) != 0) {

               perror("初始化锁失败");
               break;
           }

           pthread_create(&this->admin, NULL, reinterpret_cast<void *(*)(void *)>(contoller_p), this);
           for (int i = 0; i < min; ++i) {
               pthread_create(&this->works[i], NULL, reinterpret_cast<void *(*)(void *)>(work), this);
           }

           this->poweroff = 1;

           cout<<"任务池初始化成功"<<endl;

           return;
       } while (0);

       this->poweroff = 0;

   }
void pool_add_task(void (*func)(void *), void *arg) {
        pthread_mutex_lock(&this->pool_lock);
        cout<<"我添加了"<<endl;


        while (this->currt == this->capacity && !this->poweroff) {
            pthread_cond_wait(&this->full_vbe, &this->pool_lock);
        }


        if (this->poweroff) {
            pthread_mutex_unlock(&this->pool_lock);
        }


        //添加任务
      //TODO:这里需要大改一波将vector使用熟练

        pthread_cond_signal(&this->empty_vbe);


        pthread_mutex_unlock(&this->pool_lock);



    }




};

void pool_exit(thread_pool *pool);

void* contoller_p(void* arg){
    thread_pool *pool = (thread_pool*)arg;

    while (pool->poweroff != 0){
        sleep(5);
        //取出线程池中任务数量和当前线程数量
        pthread_mutex_lock(&pool->pool_lock);
        int present = pool->currt;
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




void* work(void* arg){
    thread_pool* pool = (thread_pool*)arg;
    while (1){



        pthread_mutex_lock(&pool->pool_lock);

        //当前任务队列如果为空并且线程池没有关闭
        while (pool->currt == 0&& !pool->poweroff){
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
        pool->currt--;
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


}





void pool_exit(thread_pool *pool){
    pthread_t tid = pthread_self();
    for (int i = 0; i < pool->max_size; ++i) {
        if (pool->works[i] == tid){
            pool->works[i] = 0;
            cout<<"线程"<<tid<<"退出"<<endl;
        }
    }
    pthread_exit(NULL);
}




#endif //TIMELYDB_V0_1_2_T_POOL_H
