//
// Created by saltfish on 23-5-23.
//

#ifndef TIMELYDB_V0_1_2_T_POOL_H
#define TIMELYDB_V0_1_2_T_POOL_H
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
    queue<T> queue;

public:


};









#endif //TIMELYDB_V0_1_2_T_POOL_H
