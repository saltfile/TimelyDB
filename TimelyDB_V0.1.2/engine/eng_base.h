//
// Created by saltfish on 23-4-19.
//

#ifndef TIMELYDB_V0_1_2_ENG_BASE_H
#define TIMELYDB_V0_1_2_ENG_BASE_H
#include <error.h>
#include <stdio.h>
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
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <future>
#include <cstdlib>
//#include <exception>
#include "../tool/tool_base.h"
using namespace std;


//早期做法
typedef struct DB_table{
    int clonms_size;
    char **clonms;
    char *tab_name;
    char *base_name;
    int val_size;
    int val_max;
    arr_list *val_;//数据节点
};
//最懒省事做法
typedef struct tab_struct{
    int max_data_size = 1024;
    char *col_together_name = NULL;
    map<string ,data_type> type_map;
    map<string ,ring_list*> data_map;
};







//初始化表
bool DB_init_memery_tab();
//创建表
bool DB_create_table(char *base_name, char *tab_name, char **clonms, data_type *types, int clonms_size);
//单行插入
bool DB_insert_table(char *base_name,char *tab_name,char **colum_key,int key_size,char** colum_val,int val_size);
//单行获取
vector<string> get_DB_once_row(char *base_name,char *tab_name,int idx_nums);



//线程处理
class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        for(size_t i = 0; i < threads; ++i) {
            workerThreads.emplace_back(
                    [this] {
                        while(true) {
                            std::function<void()> task;

                            {
                                unique_lock<std::mutex> lock(this->queueMutex);
                                this->condition.wait(lock,
                                                     [this]{ return this->stop || !this->tasks.empty(); });
                                if(this->stop && this->tasks.empty())
                                    return;
                                task = move(this->tasks.front());
                                this->tasks.pop();
                            }

                            task();
                        }
                    }
            );
        }
    }

    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args) {
        auto task = bind(forward<F>(f), forward<Args>(args)...);

        {
            unique_lock<mutex> lock(queueMutex);
            if(stop)
                throw runtime_error("enqueue on stopped ThreadPool");

            tasks.emplace(task);
        }
        condition.notify_one();
    }

    void set_stop(bool stop){
        this->stop = stop;
    }

    ~ThreadPool() {
        {
            unique_lock<std::mutex> lock(queueMutex);
//            stop = true;
        }
        condition.notify_all();
        for(thread &worker : workerThreads)
            worker.join();
    }

private:
    vector<std::thread> workerThreads;
    queue<std::function<void()>> tasks;

    mutex queueMutex;
    condition_variable condition;
    bool stop;
};




#endif //TIMELYDB_V0_1_2_ENG_BASE_H
