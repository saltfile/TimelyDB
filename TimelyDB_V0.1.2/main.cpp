#include "_startup.h"




void fun(void* a){
    int* b = (int*)a;
    cout<<"执行任务"<<&b<<endl;
}








//
int main() {

    thread_pool *pool = new thread_pool(10,3,100);

    for (int i = 0; i < 100; ++i) {
        void* arg = &i;
        pool->pool_add_task(fun, (void *)arg);
        sleep(1);
    }

    sleep(10);







    return 1;
}
