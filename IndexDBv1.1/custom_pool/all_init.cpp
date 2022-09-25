//
// Created by saltfish on 2022/9/7.
//

#include "basic_function.h"

thead_pool *pool_init(int work_num,int min,int queue_size){
    thead_pool *pool = (thread_pool *)malloc(sizeof(thread_pool));
    memset(pool,0,sizeof(thread_pool));

    do {
        if (pool == NULL) {
            perror("pool创建失败");
            break;
        }

        pool->max_size = work_num;
        pool->min_size = min;
        pool->live_num = min;
        pool->working_num = 0;
        pool->kill_num = 0;

        pool->works = (pthread_t *) malloc(sizeof(pthread_t) * work_num);
        memset(pool->works, 0, sizeof(pthread_t) * work_num);
        if (pool->works == NULL) {
            perror("工作线程组创建失败");
            break;
        }

        pool->tasks = (task *) malloc(sizeof(task) * queue_size);
        memset(pool->tasks, 0, sizeof(task) * queue_size);
        if (pool->tasks == NULL) {
            perror("创建任务队列错误");
            break;
        }
        pool->capacity = queue_size;
        pool->current = 0;
        pool->queue_head = 0;
        pool->queue_tail = 0;

        if (pthread_mutex_init(&pool->pool_lock,NULL) != 0||
        pthread_mutex_init(&pool->working_lock,NULL) != 0||
        pthread_cond_init(&pool->empty_vbe,NULL) !=0 ||
        pthread_cond_init(&pool->full_vbe,NULL) != 0){

            perror("初始化锁失败");
            break;
        }
        pool->poweroff = 0;


        pthread_create(&pool->admin, NULL, reinterpret_cast<void *(*)(void *)>(admin), pool);
        for (int i = 0; i < min; ++i) {
            pthread_create(&pool->works[i], NULL, reinterpret_cast<void *(*)(void *)>(work), pool);
        }

        return pool;
    }while (0);
    //如果报错就释放资源

    if (pool->tasks)free(pool->tasks);
    if (pool->works)free(pool->works);
    if (pool)free(pool);


    return NULL;
}












