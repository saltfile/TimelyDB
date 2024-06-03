//
// Created by saltfish on 24-5-5.
//
#include "eng_base.h"

#define WHEEL_SIZE 60
handler_event arr[WHEEL_SIZE];//时间任务准备
extern int wheel_idx = 0;//60格
bool time_flag = false;

ThreadPool handler_pool(4);//处理任务的池子

void* time_fun(void *arg){
    while (1){
        if (arr[wheel_idx].is_task){
            handler_pool.enqueue([]{
                arr[wheel_idx].f_fun();
            });

        }
        sleep(1);
        wheel_idx++;
        if (WHEEL_SIZE == wheel_idx){
            wheel_idx = 0;
        }
        if (time_flag)break;
    }
    return NULL;
}


void* setting_task(void *avg){
    int interval = atoi(get_load_time());
    int flag = wheel_idx;
    for (int i = flag; i >= 0; i-=interval) {
        arr[i].is_task = true;
        arr[i].f_fun = load_disk;
    }
    for (int i = flag+interval; i < WHEEL_SIZE; i+=interval) {
        arr[i].is_task = true;
        arr[i].f_fun = load_disk;
    }
    return NULL;
}


void stop_time_pool(){
    time_flag = true;
    handler_pool.set_stop(true);
}

void run_file_loading(){

    pthread_t tid;
    pthread_create(&tid,NULL,time_fun,NULL);
    pthread_t  tid2;
    pthread_create(&tid2,NULL,setting_task,NULL);

}




void load_disk(){

    cout<<"落盘操作"<<endl;
    vector<string> result=get_all_tab_name();
    for (int i = 0; i < result.size(); ++i) {
        cout<<result[i]<<endl;
        char *lis_base = const_cast<char *>(result[i].c_str());
        char **cols = str_spilt(lis_base,";");
        vector<string> arr = get_DB_data(cols[0],cols[1]);
        string push_str = "";

        for (int j = 0; j < arr.size(); ++j) {
            push_str+=arr[j]+"\n";
        }
        file_write(cols[0], cols[1],const_cast<char *>(push_str.c_str()));
        cout<<push_str<<endl;
        cout<<endl;

    }


}












