#include "_startup.h"
static bloking_queue<int> *task = new bloking_queue<int>();


void* fun1(void *arg){
    for (int i = 0; i < 100; ++i) {
        task->push(i);
         int *num = (int *)arg;
        cout<<"线程 "<<num<<" :添加任务"<<task->size()<<endl;
        sleep(0.1);
    }
}













//
int main() {
//    if (CONFIG_INIT() < 0)
//        return -10;

    pthread_t tid;
    pthread_create(&tid, NULL, fun1,(void *)1);
    pthread_t tid2;
    pthread_create(&tid2, NULL, fun1,(void *)2);

    void *ptr;
    pthread_join(tid,&ptr);
    pthread_join(tid2,&ptr);
    int a = task->size();
    for (int i = 0; i < a; ++i) {
        printf("%d",task->front());
    }


    return 1;
}
