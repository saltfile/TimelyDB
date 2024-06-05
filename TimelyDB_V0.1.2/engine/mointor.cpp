//
// Created by saltfish on 24-5-19.
//
#include "eng_base.h"
#include "../tool/tool_base.h"



#define WHEEL_SIZE 60
mointor_event arr[WHEEL_SIZE];//时间任务准备
int time_idx = 0;//60格
bool time_flag = false;
ThreadPool mointor_pool(4);//处理任务的池子



void* time_fun(void *arg){
    while (1){
        if (!arr[time_idx].funcs.empty()){
            mointor_pool.enqueue([]{
            for (int i = 0; i < arr[time_idx].funcs.size(); ++i) {
                arr[time_idx].funcs[i].start();
            }
            });
        }
        sleep(1);
        time_idx++;
        if (WHEEL_SIZE == time_idx){
            time_idx = 0;
        }
        if (time_flag)break;
    }
    return NULL;
}




void run_mointor_loading(){

    pthread_t tid;
    pthread_create(&tid,NULL,time_fun,NULL);

}

//TODO:添加时间任务
void mointor_add_task(char *base_name,char *tab_name,char *file,vector<string> colums,int time){
    mointor_handler m_handler;
    m_handler.base_name = str_copy("",base_name);
    m_handler.tab_name = str_copy("",tab_name);
    m_handler.file = str_copy("",file);
    m_handler.colums = colums;
//
    int now_t = time_idx;

    for (int i = now_t; i < WHEEL_SIZE; i+=time) {
        arr[i].funcs.push_back(m_handler);
    }
    for (int i = now_t - time; i >=0 ; i -= time) {
        arr[i].funcs.push_back(m_handler);
    }



}



void stop_mointor_pool(){
    time_flag = true;
    mointor_pool.set_stop(true);
}