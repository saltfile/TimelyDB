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



/**
 * push() 在队尾插入一个元素

pop() 删除队列第一个元素

size() 返回队列中元素个数

empty() 如果队列空则返回true

front() 返回队列中的第一个元素

back() 返回队列中最后一个元素
 */
template<typename T>
class bloking_queue{
private:
    queue<T> task_queue;
    pthread_mutex_t lock;
public:
    bloking_queue();

    bool is_empty();

    int size();

    void push(T data);

    void pop();

    T front();

};


template<typename T>
bloking_queue<T>::bloking_queue() {
    if (pthread_mutex_init(&lock,NULL) != 0){
        perror("queue lock init fail");
    }
}

template<typename T>
bool bloking_queue<T>::is_empty(){
    bool res = true;
    pthread_mutex_lock(&this->lock);
    res = !this->task_queue.empty();
    pthread_mutex_unlock(&this->lock);
    return res;
}


template<typename T>
int bloking_queue<T>:: size(){
    int res;
    pthread_mutex_lock(&this->lock);
    res = this->task_queue.size();
    pthread_mutex_unlock(&this->lock);
    return res;

}

template<typename T>
void bloking_queue<T>::push(T data){

    pthread_mutex_lock(&this->lock);
    this->task_queue.push(data);
    pthread_mutex_unlock(&this->lock);

}


template<typename T>
void bloking_queue<T>::pop(){
    pthread_mutex_lock(&this->lock);
    this->task_queue.pop();
    pthread_mutex_unlock(&this->lock);

}

template<typename T>
T bloking_queue<T>::front(){
    T res;
    pthread_mutex_lock(&this->lock);
    res = this->task_queue.front();
    this->task_queue.pop();
    pthread_mutex_unlock(&this->lock);

    return res;
}






#endif //TIMELYDB_V0_1_2_T_POOL_H
