//
// Created by saltfish on 24-5-5.
//
#include "eng_base.h"

#define WHEEL_SIZE 60
int arr[WHEEL_SIZE] = {0};//时间任务准备
int wheel_idx = 0;//60秒
bool time_flag = false;

ThreadPool handler_pool(20);//处理任务的池子

void* time_fun(void *arg){
    while (1){
        cout<<wheel_idx<<" "<<arr[wheel_idx]<<endl;
        sleep(1);
        wheel_idx++;
        if (WHEEL_SIZE == wheel_idx){
            wheel_idx = 0;
        }
        if (time_flag)break;
    }
    return NULL;
}


void* push_task(void *avg){
    int interval = 3;
    sleep(2);
    int flag = wheel_idx;
    for (int i = flag; i >= 0; i-=interval) {
        arr[i] = 1;
    }
    for (int i = flag+interval; i < WHEEL_SIZE; i+=interval) {
        arr[i] = 1;
    }
    return NULL;
}


void stop_time_pool(){
    time_flag = true;
    handler_pool.set_stop(true);
}














