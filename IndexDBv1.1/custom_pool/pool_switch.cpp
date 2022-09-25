//
// Created by saltfish on 2022/9/23.
//

#include "basic_function.h"

void pool_exit(thead_pool *pool){
    pthread_t tid = pthread_self();
    for (int i = 0; i < pool->max_size; ++i) {
        if (pool->works[i] == tid){
            pool->works[i] = 0;
            cout<<"线程"<<tid<<"退出"<<endl;
        }
    }
    pthread_exit(NULL);
}

//毁灭线程池 等于0为成功   1 是空   2是异常
int pool_destory(thead_pool* pool){
    if (pool==NULL){
        return 1;
    }
    //首先更改关闭线程池状态码
    pool->poweroff = 1;
    //阻塞回收管理者线程
    pthread_join(pool->admin,NULL);
    for (int i = 0; i < pool->live_num; ++i) {
        pthread_cond_signal(&pool->empty_vbe);
    }

    //释放内存
    //工作线程队列
    if (pool->works){
        free(pool->works);
    }
    //任务队列
    if (pool->tasks){
        free(pool->tasks);
    }
    //锁
    pthread_mutex_destroy(&pool->pool_lock);
    pthread_mutex_destroy(&pool->working_lock);
    pthread_cond_destroy(&pool->empty_vbe);
    pthread_cond_destroy(&pool->full_vbe);
    //最后的池子
    thread_pool* p = pool;
    pool = NULL;
    free(p);

cout<<"自制线程池----bye~~"<<endl;
    return 0;
}








int get_pool_live_num(thread_pool* pool){
    pthread_mutex_lock(&pool->pool_lock);
    int res = pool->live_num;
    pthread_mutex_unlock(&pool->pool_lock);
    return res;
}




int get_pool_working_num(thread_pool* pool){
    pthread_mutex_lock(&pool->working_lock);
    int res = pool->working_num;
    pthread_mutex_unlock(&pool->working_lock);
    return res;

}



