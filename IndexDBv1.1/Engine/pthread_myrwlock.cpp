//
// Created by mikasa on 2021/7/20.
//

#include "database_engine.h"
//#include "pthread_myrwlock.h"
//#include "global_c.h"
using namespace std;

volatile int writernum=0;
volatile int readernum=0;

pthread_mutex_t my_lock;
pthread_cond_t my_cond;
extern int pthread_myrwlock(){

}

extern void pthread_myrwlock_rdlock(){
    pthread_mutex_lock(&my_lock);
    while(writernum>0){
        pthread_cond_wait(&my_cond,&my_lock);
    }
    readernum++;
    pthread_mutex_unlock(&my_lock);
}
extern void pthread_myrwlock_wrlock(){
    pthread_mutex_lock(&my_lock);
    cout<<writernum<<endl;
    cout<<readernum<<endl;
    while(writernum>0||readernum>0){
        pthread_cond_wait(&my_cond,&my_lock);
    }
    writernum=1;
    pthread_mutex_unlock(&my_lock);
}
extern void pthread_myrwlock_unlock(){
    pthread_mutex_lock(&my_lock);
    while(writernum>0){
        writernum=0;
        pthread_cond_broadcast(&my_cond);
        pthread_mutex_unlock(&my_lock);
        return;
    }
    readernum--;

    if (readernum<=0){
        pthread_cond_broadcast(&my_cond);//唤醒所有等待条件的thread
        pthread_mutex_unlock(&my_lock);
    }
    pthread_mutex_unlock(&my_lock);

}
extern int pthread_myrwlock_init(){
    my_lock=PTHREAD_MUTEX_INITIALIZER;
    my_cond=PTHREAD_COND_INITIALIZER;
    return 0;
}