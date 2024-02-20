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

enum data_type{
    BYTE=0,
    INT=1,
    FLOAT=2,
    DOUBLE=3,
    DECIMAL=4,
    VARCHAR=5,
    TEXT=5,
    TIMESTAMP=8
};

typedef struct integer{
    int val;

    integer(int v) : val(v) {}

    int operator=(integer &order){
        return order.val;
    }
    void operator=(int i)
    {
        val = i;
    }
};

typedef struct varchar{
    int size = 255;
    char *val = (char *) malloc(sizeof(char)*size);

    void operator=(char* str){
        if(size > strlen(str)){
            memset(val,0,size);
            strcpy(val,str);
        }
    }


};

typedef struct boolbean{
    bool val;
    void operator=(bool data){
        val = data;
    }

};

typedef struct doubles{
    double val;
    void operator=(double data){
        val = data;
    }
};

typedef struct timestramp{
    time_t timestramp;
    long time_val;
    void operator=(time_t t){
        time_val = (long)t;
        timestramp = t;
    }
};







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
    int max_data_size;
    map<string ,data_type> type_map;
    map<string ,arr_list*> data_map;
};







//初始化表
bool DB_init_memery_tab();
//创建表
bool DB_create_table(char *base_name, char *tab_name, char **clonms, data_type *types, int clonms_size);











#endif //TIMELYDB_V0_1_2_ENG_BASE_H
