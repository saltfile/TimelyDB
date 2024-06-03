//
// Created by saltfish on 24-5-19.
//
#include "eng_base.h"




#define WHEEL_SIZE 60
mointor_event arr[WHEEL_SIZE];//时间任务准备
int wheel_idx = 0;//60格
bool time_flag = false;
ThreadPool mointor_pool(4);//处理任务的池子



void* time_fun(void *arg){
    while (1){
//        if (arr[wheel_idx].is_task){
//            mointor_pool.enqueue([]{
//                arr[wheel_idx].f_fun();
//            });
//
//        }
        sleep(1);
        wheel_idx++;
        if (WHEEL_SIZE == wheel_idx){
            wheel_idx = 0;
        }
        if (time_flag)break;
    }
    return NULL;
}








