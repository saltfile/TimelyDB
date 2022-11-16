//
// Created by maomao on 2021/8/26.
////#include "database_engine.h"
//#include "global_c.h"
#include "../grammar/Myall.h"
#include "database_engine.h"
#define strcompare(_p) (*reinterpret_cast<const uint32_t *>(_p))//比较字符串是否相等，比strcmp略快
extern int write_ahead_log(char * timestamp,char * databasename,char * tablename,value_tuple * values);
extern IBool load_ahead_log(head_tuple * load_list);
extern void * load_disk_method(head_tuple * load_list);
IBool insert_cir_node(head_tuple * headdata);

CircularList * list_head;//环形链表的头
head_tuple * list_tail;//环形链表的链尾

long int list_size_now=0;//环目前大小
pthread_key_t key_databasename=1;
char * databasename;

void * manager_full_writedisk();//full_flush

/**
 * 执行use databasename操作的语句
 *
 * */
int  use_database(char * databasename){
//    return (pthread_setspecific(key_databasename,databasename));
    databasename=databasename;
    return 0;
}
head_tuple *add_htuple(head_tuple *root,head_tuple *new_node){
}


head_tuple *add_htuple_null(head_tuple *root){
    head_tuple *sd = root;

    if (sd == NULL){
        sd  = (head_tuple *) malloc(sizeof(head_tuple));
        memset(sd,0, sizeof(head_tuple));
        return sd;
    }



    while (sd->next){
        sd = sd->next;
    }
    head_tuple *node = (head_tuple *) malloc(sizeof(head_tuple));
    memset(node,0, sizeof(head_tuple));
    sd->next = node;
    return root;
}

head_tuple *sreach_tail(head_tuple *root){
    head_tuple *p = root;
    while (p->next){
        p = p->next;
    }
    return p;
}


int use_detect(){
    return (pthread_setspecific(key_databasename,databasename));
}


char* marge_colum(tuple_column * root,tuple_column * new_node){
    tuple_column *rps = root;
    tuple_column *nps = new_node;
    char *res = (char *) malloc(strlen(new_node->datalist->timestamp));
    memset(res,0, strlen(new_node->datalist->timestamp));
    strcpy(res,new_node->datalist->timestamp);
    while (rps!=NULL&&nps!=NULL) {
        add_value_node(rps->datalist, nps->datalist);
        rps = rps->nextcolumn;
        nps = nps->nextcolumn;
    }

    return res;

}










/*创建一条insert into 插入的数据链
* 此函数对接给insert语句解析之后调用的
 * 该数据链会挂载到节点上
 * {@param databasename}库名
 * {@param tablename}表名
 * {@param columns}列列表
 * {@param datas}参数列表(数据列表)
 * 这里需要规划一下，当节点插入时应该合理插入并且做校验
 */
//新版函数
int create_cir_nodelist(char* databasename,char * tablename,tuple_column *columns,value_tuple * datas) {
    //TODO:注:这里的fork开始同步预写日志
//    databasename=(char *)pthread_getspecific(key_databasename);//获取数据库名
int pid = 0;
//TODO：解决这里的插入及日志问题
//pid_t pid=fork();
    if (pid<0){
        perror("[ERROR] fork write ahead log failed\n");
        return -1;
    }
    if (pid != 0) {
        if (write_ahead_log(datas->timestamp,databasename,tablename,datas)==1)return 1; //预写日志
        else perror("[ERROR] write ahead log failed\n");
    } else {//执行插入语句操作
        cout<<"insert start"<<endl;
        head_tuple *headtuple;
//        pthread_myrwlock_wrlock();
        head_tuple *headTuple_index = list_head->next;//从头开始找
        for (int i = 0; i < list_head->size; ++i) {
            if (!task_head_t(headTuple_index)) {
                if (strcmp(databasename, headTuple_index->databasename) == 0 &&
                    strcmp(tablename, headTuple_index->tablename) == 0) {
                    char *max = marge_colum(headTuple_index->fileds,columns);
                    if (strcmp(max,headTuple_index->max_time)!=0){
                        free_string(headTuple_index->max_time);
                        headTuple_index->max_time = str_copy(headTuple_index->max_time,max);
                    }
                    return 2;
                }
                headTuple_index = headTuple_index->next;
            }
        }
        //要么创建新节点，要么链头覆盖
        if (task_head_t(headTuple_index)){
            // 空的创建新节点
            headTuple_index->databasename = (char *) malloc(strlen(databasename)+1);
            strcpy(headTuple_index->databasename,databasename);

            headTuple_index->tablename = (char *) malloc(strlen(tablename)+1);
            strcpy(headTuple_index->tablename,tablename);

            headTuple_index->fileds = columns;

            headTuple_index->min_time = (char *) malloc(strlen(datas->timestamp)+1);
            headTuple_index->max_time = (char *) malloc(strlen(datas->timestamp)+1);
            strcpy(headTuple_index->min_time,datas->timestamp);
            strcpy(headTuple_index->max_time,datas->timestamp);
            return 3;
        } else{
            //覆盖先清空
            clear_head_t(headTuple_index);
            headTuple_index->databasename = (char *) malloc(strlen(databasename)+1);
            strcpy(headTuple_index->databasename,databasename);

            headTuple_index->tablename = (char *) malloc(strlen(tablename)+1);
            strcpy(headTuple_index->tablename,tablename);

            headTuple_index->fileds = columns;

            headTuple_index->min_time = (char *) malloc(strlen(datas->timestamp)+1);
            headTuple_index->max_time = (char *) malloc(strlen(datas->timestamp)+1);
            strcpy(headTuple_index->min_time,datas->timestamp);
            strcpy(headTuple_index->max_time,datas->timestamp);
            return 4;
        }
        return -1;
    }
}



//旧版函数
//int create_cir_nodelist(char* databasename,char * tablename,tuple_column *columns,value_tuple * datas) {
//    //TODO:注:这里的fork开始同步预写日志
////    databasename=(char *)pthread_getspecific(key_databasename);//获取数据库名
//    int pid = 0;
////TODO：解决这里的插入及日志问题
////pid_t pid=fork();
//    if (pid<0){
//        perror("[ERROR] fork write ahead log failed\n");
//        return -1;
//    }
//    if (pid != 0) {
//        if (write_ahead_log(datas->timestamp,databasename,tablename,datas)==1)return 1; //预写日志
//        else perror("[ERROR] write ahead log failed\n");
//    } else {//执行插入语句操作
//        cout<<"insert start"<<endl;
//        head_tuple *headtuple;
////        pthread_myrwlock_wrlock();
//        head_tuple *headTuple_index = list_head->next;//从头开始找
//        //TODO:2022-10-25   while 原：(headTuple_index != NULL && headTuple_index != list_head->next)
//        if (headTuple_index->next != NULL){
//
////        while (headTuple_index != NULL) {
//            while (!task_head_t(headTuple_index)) {
////            cout<<"这里"<<endl;
//                if (headTuple_index->databasename != NULL
//                    && headTuple_index->tablename != NULL
//                    && strcompare((headTuple_index->databasename)) == strcompare(databasename)
//                    && strcompare((headTuple_index->tablename)) == strcompare(tablename)
//                        ) { //如果原环上有数据就往后插入
//                    tuple_column *tupleColumn = headTuple_index->fileds;
//                    if (strcmp(headTuple_index->max_time,datas->timestamp)<=0) {//正常的数据
//                        headTuple_index->max_time = datas->timestamp;
//                    } else{//已经落盘的数据，插入回内存环,多条数据
//                        do {
//                            value_tuple *datas_begin = datas;
//                            while (datas != NULL && datas->timestamp!=NULL &&
//                                   strcmp(tupleColumn->datalist->timestamp, datas->timestamp) > 0) {//将数据插入到前部分
//                                if (datas->next != NULL)
//                                    datas = datas->next;
//                            }
//                            datas->next = tupleColumn->datalist;
//                            tupleColumn->datalist = datas_begin;
//
//                            columns=columns->nextcolumn;//重新入环的数据列
//                            if (columns!=NULL){
//                                if (columns->datalist!=NULL){
//                                    datas=columns->datalist;
//                                }
//                            }
//                            tupleColumn=tupleColumn->nextcolumn;//原环的数据列
//                        }while (columns!=NULL&&tupleColumn!=NULL);//遍历插入的每条列
//                        return NULL;
//                    }
////                while (datas != NULL) {
////                    datas = datas->next;//正常的新数据,一条数据
//                    while (tupleColumn != NULL&&columns != NULL) {
//                        if (tupleColumn->listtail != NULL){
//                            tupleColumn->listtail->next = columns->datalist;
//                            tupleColumn->listtail = tupleColumn->listtail->next;
//                        } else{
//
//                            tupleColumn->datalist->next = columns->datalist;
//
//                        }
//
//
//
//                        columns = columns->nextcolumn;
//                        tupleColumn = tupleColumn->nextcolumn;
//
//                    }
////                    datas = datas->next;
////                    tupleColumn->listtail = tupleColumn->listtail->next;
////                }
//                    return 2;
//                }
//                headTuple_index = headTuple_index->next;
//            }
//
//        }
////        pthread_myrwlock_unlock();
//
//        headtuple = (head_tuple *) malloc(sizeof(head_tuple)); //初始化 元数据 节点
//
//        if (headtuple==NULL){//说明内存已经无法分配了
////            pthread_myrwlock_wrlock();
//            manager_full_writedisk();
////            pthread_myrwlock_unlock();
//        }
//        if (list_head != NULL) { //链表初始化完成才能插入节点
//            insert_cir_node(headtuple);
//        } else {
//            perror("[ERROR] circular list has not been created\n");
//        }
//
////        pthread_myrwlock_wrlock();
//        headtuple->fileds = columns;//初始化 属性 节点
//        tuple_column *tuple_column_index = headtuple->fileds;
//        headtuple->databasename = (char *) malloc(strlen(databasename));
//        headtuple->databasename = databasename;
//        headtuple->tablename = (char *) malloc(strlen(tablename));
//        headtuple->tablename = tablename;
//        headtuple->min_time = (char *) malloc(15);
//        headtuple->min_time = datas->timestamp;
//        headtuple->max_time = (char *) malloc(15);
//        headtuple->max_time = datas->timestamp;
//        cout<<"这里2"<<endl;
//
//        while (tuple_column_index != NULL) {
//            tuple_column_index->listtail = tuple_column_index->datalist;
//            tuple_column_index = tuple_column_index->nextcolumn;
//        }
//        if (list_head->next!=NULL)
//            cout<<list_head->next->databasename<<endl;
//        cout<<"xxx"<<endl;
////        pthread_myrwlock_unlock();
////        exit(0);
//        return 3;
//    }
//}


bool task_head_t(head_tuple* root){
    if (root == NULL)return true;
    head_tuple *p = root;
    bool db_name = p->databasename == NULL;
    bool tb_name = p->tablename == NULL;
    bool filte = p->fileds == NULL;
    bool mintime = p->min_time == NULL;
    bool maxtime = p->max_time == NULL;
    return db_name&&tb_name&&filte&&mintime&&maxtime;

}
//void free
void free_val_tupl(value_tuple *p){
    while (p->next){

        value_tuple *as = p;
        p = p->next;
        free(as);
        as = NULL;
    }
    value_tuple *as = p;
    as = NULL;
}

void free_string(char* root){
    if (root){
        char *p = root;
        free(p);
        root = NULL;
    }
}


void free_tup_conlum(tuple_column *ptr){
    while (ptr->nextcolumn){
        tuple_column *as = ptr;
        ptr = ptr->nextcolumn;
        free_val_tupl(as->datalist);
        free_val_tupl(as->listtail);
        free(as);
        as = NULL;
    }
    tuple_column *as = ptr;
    as = NULL;
}
//后期用来清除节点中已经落盘之后的函数
void clear_head_t(head_tuple* root){
    char *dname = root->databasename;
    free(dname);
    root->databasename = NULL;
    char *table = root->tablename;
    free(table);
    root->tablename = NULL;
    char *mtime = root->min_time;
    free(mtime);
    root->min_time = NULL;
    char*matime = root->max_time;
    free(matime);
    root->max_time = NULL;
    free_tup_conlum(root->fileds);
}










///**
// * 保留策略
// * 数据到点落盘
// * {@param reserve_time}落盘时间周期
// * */
void * manager_writedisk(long int reserve_time){
    int check_alive=0;
    head_tuple * headtuple_index=list_head->next;//原链
    while (1){
//        pthread_myrwlock_rdlock();
        if (list_head==NULL){
            check_alive++;
            if (check_alive>=8){ //如果管理线程检测8次环上都无数据就默认系统关闭退出程序
                exit(0);
            }
//            pthread_myrwlock_unlock();
            sleep(reserve_time);
            continue;
        } else {
//            cout<<"活着继续检查"<<endl;
            check_alive=0;
        }
//TODO：这里需要更新一个函数查看headtuple_index除了next 不为空的函数
        if (task_head_t(headtuple_index)){
            if (headtuple_index == NULL){
                //TODO:抛错
                sleep(reserve_time);
                continue;
            }
            if (headtuple_index->next!=NULL)
                headtuple_index = headtuple_index->next;
//            sleep(reserve_time);
//            perror("[ERROR] list_head.next is NULL\n");
            continue;
        }







//        if(headtuple_index->min_time==NULL) {
////            if (headtuple_index->next != NULL)
//            headtuple_index = headtuple_index->next;
////            cout<<"min_time Wei null"<<endl;
//            continue;
//        };
        time_t flush_cond=time(NULL)-reserve_time;//需要执行回收的是时间条件 当前时间减去周期时间
//        pthread_myrwlock_unlock();//放读锁

//        pthread_myrwlock_wrlock();//加写锁
        head_tuple * load_list=(head_tuple *)malloc(sizeof(head_tuple));//准备落盘的数据链的链头
        memset(load_list,0,sizeof(head_tuple));
        head_tuple * load_list_index=load_list;
        do{//遍历当前表下的列
            if (headtuple_index->min_time == NULL)continue;
            long times = atol(headtuple_index->min_time)-flush_cond;
            if (times<=0){//符合flush条件
                //复制一份元数据,当数据链上没有数据时元数据结构要free
                load_list_index->databasename=(char *)malloc(strlen(headtuple_index->databasename));
                load_list_index->databasename=headtuple_index->databasename;
                load_list_index->tablename=(char *)malloc(strlen(headtuple_index->tablename));
                load_list_index->tablename=headtuple_index->tablename;
                //TODO:2022-10-25 在插入完成后这里的值依然调用不到
                //TODO:2022-10-26 明天要完成插入后值被穿丢的情况
                tuple_column * flush_list_index=headtuple_index->fileds;//要flush列的指针
                //复制列的元数据
                tuple_column * flush_list=(tuple_column *)malloc(sizeof(tuple_column));
                load_list_index->fileds=flush_list;
                while (flush_list_index!=NULL){//遍历当前列的数据
                    value_tuple * flush_value=flush_list_index->datalist;
                    value_tuple * cut_value_list=flush_value;//当前符合条件的数据链
                    while (flush_value!=NULL&&atol(flush_value->timestamp)-flush_cond<=0) {//遍历数据,当前节点符合条件
                        if (flush_value->next!=NULL)
                        long a = atol(flush_value->next->timestamp)-flush_cond;
                        if (flush_value->next!=NULL&&
                        flush_value->next->timestamp!=NULL
                         &&atol(flush_value->next->timestamp)-flush_cond > 0){//说明要截取落盘的链到此为止

                            flush_list_index->datalist=flush_value->next;
                            headtuple_index->min_time=flush_list_index->datalist->timestamp;
                            flush_value->next=NULL;

                            break;
                        }
                        flush_value=flush_value->next;
                    }
                    //填充列的数据链和复制列的元数据
                    flush_list->datalist=cut_value_list;

                    flush_list->columnname = str_copy(flush_list->columnname,flush_list_index->columnname);
                    flush_list_index=flush_list_index->nextcolumn;

                    if (flush_list_index!=NULL){

                        flush_list->nextcolumn=(tuple_column *)malloc(sizeof(tuple_column));
                        flush_list=flush_list->nextcolumn;
                    } else{
                        flush_list->nextcolumn=NULL;
                    }
                }
            }
//            if (headtuple_index->next !=NULL)
            headtuple_index=headtuple_index->next;
            //TODO:11-12  这里额list_head变成空的所以需要写一个清空head_tuple的值
            if (headtuple_index != NULL&&headtuple_index != list_head->next){
                load_list_index->next=(head_tuple *)malloc(sizeof(head_tuple));
                load_list_index=load_list_index->next;
            }
            //TODO:修改headtuple_index!=NULL&&headtuple_index!=list_head->next)
            bool _a = headtuple_index!=NULL;
            bool b = headtuple_index!=list_head->next;
        }while (headtuple_index!=NULL&&headtuple_index!=list_head->next);
        load_list_index->next=NULL;
//        pthread_myrwlock_unlock();//放写锁
        cout<<"我是闲置信息"<<load_list->databasename<<endl;
        if (load_ahead_log(load_list)==ITrue){
            pthread_t load;
            int iRet=pthread_create(&load, NULL, reinterpret_cast<void *(*)(void *)>(&load_disk_method),
                                    reinterpret_cast<void *>(load_list));
            if (iRet){
                perror("[ERROR] load disk pthread join error\n");
                return NULL;
            }
        }
        sleep(reserve_time);
    }
}

/**
 * 环满落盘策略
 *  将环上全部数据落盘
 * */
void * manager_full_writedisk(){
    if (list_head==NULL){
        printf("the cirlist is NULL\n");
    }
//    pthread_myrwlock_wrlock();

    head_tuple * headtuple_index=list_head->next;
    head_tuple * load_list=(head_tuple *)malloc(sizeof(head_tuple));//准备落盘的数据链的链头
    head_tuple * load_list_index=load_list;
    do {
        if (headtuple_index==NULL)break;
        if (headtuple_index->databasename==NULL||headtuple_index->tablename==NULL){
            if (headtuple_index->next!=NULL) {
                headtuple_index = headtuple_index->next;
                continue;
            }
        }

        load_list_index->databasename=(char *)malloc(strlen(headtuple_index->databasename));
        load_list_index->databasename=headtuple_index->databasename;
        load_list_index->tablename=(char *)malloc(strlen(headtuple_index->tablename));
        load_list_index->tablename=headtuple_index->tablename;


        tuple_column * flush_list_index=headtuple_index->fileds;//要flush列的指针，遍历原环的指针
        //复制列的元数据
        tuple_column * flush_list=(tuple_column *)malloc(sizeof(tuple_column));//复制出来要落盘的列
        load_list_index->fileds=flush_list;
        while (flush_list_index!=NULL){

            value_tuple * flush_value=flush_list_index->datalist;//原环的value数据
            value_tuple * cut_value_list=flush_value;//当前符合条件的数据链
            while (flush_value!=NULL){
               if (flush_value!=NULL&&
                       flush_value->timestamp!=NULL&&
               strcmp(flush_value->timestamp,headtuple_index->min_time)<0){//说明数据落过盘了，忽略
                   free(flush_value->timestamp);
                   free(flush_value->value);
                   value_tuple * temp=flush_value;
                   flush_value = flush_value->next;//指向下一个
                   if (flush_value!=NULL) {
                       cut_value_list=flush_value;
                   }
                   free(temp);//落过盘的数据清除掉，free上一个
                   continue;
               } else{//说明之后就是新数据了
                   if (flush_value->next!=NULL&&
                       flush_value->next->timestamp!=NULL){
                       flush_value=flush_value->next;
                   }

               }
            }
            flush_list->datalist=cut_value_list;


            flush_list_index=flush_list_index->nextcolumn;
            if (flush_list_index!=NULL){
                flush_list->nextcolumn=(tuple_column *)malloc(sizeof(tuple_column));
                flush_list=flush_list->nextcolumn;
            } else{
                flush_list->nextcolumn=NULL;
            }
        }
        headtuple_index=headtuple_index->next;
        if (headtuple_index!=NULL&&headtuple_index!=list_head->next){
            load_list_index->next=(head_tuple *)malloc(sizeof(head_tuple));
            load_list_index=load_list_index->next;
        }
    }while (headtuple_index!=NULL&&headtuple_index!=list_head->next);
    load_list_index->next=NULL;

//    pthread_myrwlock_unlock();
    if (load_ahead_log(load_list)==ITrue){
        pthread_t load;
        int iRet=pthread_create(&load, NULL, reinterpret_cast<void *(*)(void *)>(&load_disk_method),
                                reinterpret_cast<void *>(load_list));
        if (iRet){
            perror("[ERROR] load disk pthread join error\n");
            return NULL;
        }
    }
    return NULL;
}


/*
 * 创建环形链表
 * {@param cyclelength}设定链表的长度
 *
 * */
CircularList *initCircularList(long int cyclelength){
    if (list_head==NULL){
        list_head=(CircularList *)malloc(sizeof(CircularList));
        memset(list_head,0,sizeof(CircularList));
        if (list_head==NULL){
            perror("[ERROR] init circularlist fail\n");
            return NULL;
        }
//        list_head->index=0;
        printf("cyclelength is %d\n",cyclelength);
        list_head->size=cyclelength;
        //循环建立
        //TODO:11-09由于前面的系统崩了导致我这里的代码出了问题，更新初始化的问题也没更新上，哎，加油吧



//        list_head->next=

        for (int i = 0; i < cyclelength; ++i) {
            list_head->next = add_htuple_null(list_head->next);
        }

        list_tail= sreach_tail(list_head->next);
        list_tail->next = list_head->next;
    }else {
        list_head->size=cyclelength;
    }
//    pthread_t manager;
//    int reserve_time=5;
//
//    int iRet=pthread_create(&manager, NULL, reinterpret_cast<void *(*)(void *)>(&manager_writedisk),
//                            reinterpret_cast<void *>(reserve_time));
//    if (iRet){
//        perror("[ERROR] pthread join error\n");
//        return NULL;
//    }

//    printf("the thread id is %ld\n",manager);
    return list_head;

}
/*
 * 添加数据链表的节点
 * {@param headdata}参数链
 *
 * */
IBool insert_cir_node(head_tuple * headdata){
//    pthread_myrwlock_rdlock();

    if (list_head==NULL){
        //如果没有自定义初始化的话，就默认创建
        initCircularList(60);
    }
    if (list_head->next!=NULL&&list_head->size<=list_size_now){//是否覆盖
        list_tail=list_head->next;
        list_tail=headdata;
        list_tail=list_tail->next;
        list_head->is_fulied=1;
//        pthread_myrwlock_unlock();
        return ITrue;
    }
    if (list_tail==NULL){
        perror("[ERROR] the list_tail can not be NULL\n");
//        pthread_myrwlock_unlock();
        return IFalse;
    }
    if (!list_head->is_fulied)
        list_tail=list_head->next; //没覆盖就继续新建节点
//    else list_head->earliest_time=list_tail->headdata->timestamp; //覆盖了就更新环上当前最早的数据时间
    list_tail->next=headdata;
    list_tail=list_tail->next;

//    pthread_myrwlock_unlock();
    return ITrue;
}
/**
 * 遍历环形链表打印元数据
 *
 * */
void foreach_cirlist(){
//    pthread_myrwlock_rdlock();
    if (list_head==NULL){
        printf("the cirlist is NULL\n");
    }
    int time=0;
    head_tuple * list_index=list_head->next;
    do {
        if (list_index==NULL)break;
        if (list_index->databasename==NULL||list_index->tablename==NULL||strlen(list_index->databasename)<=0){
            if (list_index->next!=NULL) {
                list_index = list_index->next;
                time++;
                continue;
            }
        }
//        printf("timestamp is %ld\n",list_index->headdata->timestamp);
        printf("databasename %s, tablename %s\n",
               list_index->databasename,list_index->tablename);
        tuple_column * tupleColumn=list_index->fileds;
        while (tupleColumn!=NULL){
            printf("column name is %s\n",tupleColumn->columnname);
            value_tuple * valueTuple=tupleColumn->datalist;
            while (valueTuple!=NULL){
                printf("valuetimestamp is %s,value is %s\n",valueTuple->timestamp,valueTuple->value);
                valueTuple=valueTuple->next;
            }
            tupleColumn=tupleColumn->nextcolumn;
        }
        list_index=list_index->next;
    }while (list_index!=list_head->next);
//    pthread_myrwlock_unlock();
//cout<<time<<endl;
}
/**
 * 查找磁盘的数据
 *  {@param tablename}查找的表
 *  {@param targetpath}目标表的路径
 *  {@param begin}目标数据的偏移量
 *  {@param end}目标数据的截止位置
 *
 * */
tuple_column * search_disk(char * tablename,char * targetpath,int begin,int end){
//    int targetpath_len=strlen(targetpath);
    int fd;
//    pthread_myrwlock_rdlock();
    fd=open(targetpath,O_RDONLY);
    if (fd<=0){
        perror("[ERROR] open target file error!\n");
        exit(1);
    }
    struct stat statbuf;
    stat(targetpath,&statbuf);
    int size=statbuf.st_size;
    char * target=(char *)mmap(NULL,size,PROT_READ,MAP_SHARED,fd,0);
    string column_name;//查找列名
    int target_len=strlen(target);
    for (int i = 0; i < target_len; ++i) {
        if (target[i]!='\n'){
            column_name+=target[i];
        } else break;
    }
    char * column_name_char= const_cast<char *>(column_name.data());
    close(fd);
//    pthread_myrwlock_unlock();
    char * do_target=(char *)malloc(end-begin);
    strncpy(do_target,target+begin,end-begin);
    string output;

    //解压缩
    snappy::Uncompress(do_target,strlen(do_target),&output);

    //解压缩的内容
    char * output_context= const_cast<char *>(output.data());

    //解压缩的内容分块
    char * block=strtok(output_context,"\n");


    char * columnname=strtok(column_name_char,";");


    tuple_column * search_result=(tuple_column *)malloc(sizeof(tuple_column));//要查找的列数据结构
    tuple_column * index_search_result=search_result;

    index_search_result->columnname=(char *)malloc(strlen(columnname));
    index_search_result->columnname=columnname;

    while (block!=NULL&&columnname!=NULL){
        char * data=strtok(block,";");
        while (data!=NULL){
            index_search_result->datalist=(value_tuple *)malloc(sizeof(value_tuple));
            index_search_result->datalist->timestamp=(char *)malloc(strlen(data));
            index_search_result->datalist->timestamp=data;
            data=strtok(NULL,";");
            if (data==NULL)break;
            index_search_result->datalist->value=(char *)malloc(strlen(data));
            index_search_result->datalist->value=data;
        }
        block=strtok(NULL,"\n");
        columnname=strtok(NULL,";");
        if (block!=NULL&&columnname!=NULL){
            index_search_result->nextcolumn=(tuple_column *)malloc(sizeof(tuple_column));
            index_search_result=index_search_result->nextcolumn;
            index_search_result->columnname=(char *)malloc(strlen(columnname));
            index_search_result->columnname=columnname;
        }
    }

    create_cir_nodelist(databasename,tablename,search_result,search_result->datalist);//添加到环上
    return search_result;

}


///**
// * 获取设定窗口大小的数据链
// * {@param tablename}查找的表
// * {@param start}窗口开始时间
// * {@param end}窗口结束时间
// *
// * */
tuple_column * time_window(char * tablename,char * start,char * end){
    char * databasename=(char *)pthread_getspecific(key_databasename);
//    pthread_myrwlock_rdlock();
//    //如果所要获得的时间窗口数据不在环上，要查磁盘
    if (list_head==NULL){
        perror("[ERROR] can not set the time window because of the cirlist is NULL\n");
//        pthread_myrwlock_unlock();
        return NULL;
    }
    head_tuple * headTuple_index=list_head->next;
    tuple_column * target_column;
    while (headTuple_index!=NULL&&headTuple_index!=list_head->next){
        if (headTuple_index->databasename!=NULL
            && headTuple_index->tablename!=NULL
            && strcompare((headTuple_index->databasename))==strcompare(databasename)
            && strcompare((headTuple_index->tablename))==strcompare(tablename)
                ){//在环上匹配到key即databasename和tablename
                if (strcmp(start,headTuple_index->min_time)<0){
                    return NULL;//交给索引部分判断
                } else{
                    target_column=headTuple_index->fileds;
                    break;
                }
        } else {//没匹配到就找下一个
            headTuple_index=headTuple_index->next;
        }
    }
    tuple_column * result_list=(tuple_column *)malloc(sizeof(tuple_column));
    tuple_column * result_list_index=result_list;
    while (target_column!=NULL){
        value_tuple * data=target_column->datalist;
        result_list_index->datalist=(value_tuple *)malloc(sizeof(value_tuple));
        while (data!=NULL){
            if (strcmp(start,data->timestamp)>=0&&strcmp(end,data->timestamp)<=0){//符合时间范围
                result_list_index->datalist->timestamp=(char *)malloc(15);
                result_list_index->datalist->timestamp=data->timestamp;
                result_list_index->datalist->value=(char *)malloc(strlen((char *)data->value));
                result_list_index->datalist->value=data->value;
                data=data->next;
                if (data!=NULL){
                    result_list_index->datalist->next=(value_tuple *)malloc(sizeof(value_tuple));
                    result_list_index->datalist=result_list_index->datalist->next;
                }
            }
            target_column=target_column->nextcolumn;
            if (target_column!=NULL){
                result_list_index->nextcolumn=(tuple_column *)malloc(sizeof(tuple_column));
                result_list_index=result_list_index->nextcolumn;
            }
        }
    }
    return result_list;

}




/////////////////////////////////////////////////////////////////////

//添加环形链表
//IBool addCirNode(CircularList *cirList,CircularNode *cirNode,char * filePath,char* databaseName,char * tableName){
//    if (cirList == NULL|| cirNode == NULL)
//    {
//        return IFalse;
//    }
//    if (cirList->head == NULL){
//        cirList->head = cirNode;
//        cirList->filePath=filePath;
//        cirList->databaseName = databaseName;
//        cirList->tableName = tableName;
//        return ITrue;
//    }
//    cirList->head->next=cirNode;
//    cirList->filePath=filePath;
//    cirList->databaseName = databaseName;
//    cirList->tableName = tableName;
//    return ITrue;
//}

//遍历环形链表
//void* foreachCirList(CircularList *cirList){
//
//    if (cirList == NULL){
//      printf("链表内容为空！！！");
//    }
//
//    CircularNode *temp;
//    for (temp = cirList->head; temp!=NULL ;temp = temp->next) {
//        printf("数据类型=%s,数据值=%s",temp->datatype,temp->values);
//    }
//
//}
////销毁环形链表节点
//void destroyCircularNode(CircularNode *node){
//    free(node);
//    node->next = NULL;
//
//}


////删除节点
//IBool removeNode(CircularNode *cirNode){
//    if (cirNode->next == NULL)
//    {
//        destroyCircularNode(cirNode);
//        return ITrue;
//    }
//    CircularNode *temp=cirNode->next;
//    destroyCircularNode(cirNode);
//    cirNode->next = temp->next;
//    cirNode->values = temp->values;
//    cirNode->datatype = temp->datatype;
//    cirNode->index = temp->index;
//    cirNode->offsetSize = temp->offsetSize;
//    return ITrue;
//}

////删除环形链表
//void removeCircularList(CircularList *circularList){
//
//    CircularNode  *temp;
//    temp = circularList->head;
//    while (temp)
//    {
//        circularList->head = circularList->head->next;
//        temp->next = NULL;
//        destroyCircularNode(temp);
//        temp=circularList->head;
//    }
//    free(circularList);
//    circularList = NULL;
//
//}



//
////读取文件数据
//char* readData(char* filePath){
//
//    //r模式从文件头开始读 文件必须存在
//    readFile = fopen(filePath,"r");
//    if (readFile == NULL){
//        printf("open error!\n");
//        return NULL;
//    }
//
//    fread(buf,102400,1,readFile);
//   // printf("%s\n",buf);
//    fclose(readFile);
//    return buf;
//
//}


//写文件数据
IBool writeData(char* filePath,char * data){

    //a模式从文件尾开始写 文件不存在进行创建，存在则追加
    FILE *write = fopen(filePath,"a");
    if (write == NULL){
        printf("open error!\n");
        return Ierror;
    }

    /**
     * 数据块写入
     * 参数1：要获取的数据的地址
     * 参数2：要写入内容的单字节数
     * 参数3：要写入size字节的数据项的个数
     * 参数4：目标文件指针
     */
    fwrite(data,strlen(data),1,write);
    fclose(write);
    return ITrue;
}

void deleteFile(char *filePath){

    char* cmd ="rm -rf ";

    char* s = (char*)malloc(strlen(cmd)+strlen(filePath));
    //清零操作
    memset(s,0,sizeof(s));
    strcat(s,cmd);
    strcat(s,filePath);
    system(s);
}

/**
 * time,age,name,school;
 * @return
 */
//int main(){


//  char* value = "0011001012445,12,mike,qinghua;0011001112445,13,tom,qinghua;0011001012645,18,joke,qinghua;0011001018445,18,chris,qinghua;";
//  if (writeData("/home/maomao/CLionProjects/index-tsdb/IndexTSDB_v1.0/data/user.tsdb",value)==ITrue)
//  {
//      printf("写入成功！！！\n");
//  }
//
//  char* reString =readData("/home/maomao/CLionProjects/index-tsdb/IndexTSDB_v1.0/data/user.tsdb");
//  printf("readFile=%s\n",reString);
//
//  char * reBuf =strtok(reString,";");
//  printf("     time     age name  school\n");
//  while (reBuf != NULL){
//      printf("%s\n",reBuf);
//      reBuf =strtok(NULL,";");
//  }

  //deleteFile("/home/maomao/CLionProjects/index-tsdb/IndexTSDB_v1.0/data/user.tsdb");
//}
