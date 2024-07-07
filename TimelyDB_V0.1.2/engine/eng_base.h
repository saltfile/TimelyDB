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
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <stdexcept>
//#include <exception>

using namespace std;
#include "../tool/tool_base.h"

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
    bool display = true;
    int max_data_size = 1024;
    char *col_together_name = NULL;
    map<string ,data_type> type_map;
    map<string ,ring_list*> data_map;
};

typedef void(*file_func)();
enum func_type {
   FILE_FUN = 0,
   TIME_FUN = 1
};

typedef struct handler_event{
    bool is_task = false;
    func_type fun_tpye;
    file_func f_fun;

}handler_event;

typedef void(*mointor_fun) (char *base_name,char *tab_name,char *file,vector<string> colnms);









void run_file_loading();
void stop_file_pool();


void run_mointor_loading();
void stop_mointor_pool();

void mointor_add_task(char *base_name,char *tab_name,char *file,vector<string> colums,int time);

//初始化表
bool DB_init_memery_tab();
//创建表
bool DB_create_table(char *base_name, char *tab_name, char **clonms, data_type *types, int clonms_size);
//单行插入
bool DB_insert_table(char *base_name,char *tab_name,char **colum_key,int key_size,char** colum_val,int val_size);
//单行获取
vector<string> get_DB_once_row(char *base_name,char *tab_name,int idx_nums);
//获取环形数据
vector<string> get_DB_data(char *base_name,char *tab_name);
//获取所有库表名称用;隔开
vector<string> get_all_tab_name();
//获取单个表的所有列
vector<string> get_tab_colums(char* base_name,char* tab_name);
//获取列map
map<string,string> get_tab_map_colums(char* base_name,char* tab_name);
//use语句
bool use_database(char *basename);
//返回use 数据库
char *is_use_database();
//create database语句
bool create_database_db(char *basename);
char *get_tab_cols(char *base_name,char *tab_name);
//查看是否存在表
bool DB_tab_is_exist(char *tab_name);
//查看列是否存在
bool DB_colum_is_exist(char *tab_name,char *col_name);
//执行时间任务
void mointor_s(char *base_name,char *tab_name,char *file,vector<string> colnms);
void load_disk();
void run_file_loading();
void del_tab(char *base_name,char *tab_name);
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




typedef struct mointor_handler{
    char *base_name;
    char *tab_name;
    char *file;
    int time;
    vector<string> colums;
    void start(){
        mointor_s(base_name,tab_name,file,colums);
//cout<<base_name<<endl;
//cout<<tab_name<<endl;
//cout<<file<<endl;
    }
}mointor_handler;


typedef struct mointor_event{

    vector<mointor_handler> funcs;
};


#endif //TIMELYDB_V0_1_2_ENG_BASE_H
