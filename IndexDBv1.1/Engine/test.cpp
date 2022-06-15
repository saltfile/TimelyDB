//#include <iostream>
//#include <snappy.h>
#include "database_engine.h"
//#include "stdarg.h"
//#include "iostream"
//#include "global_c.h"
//#include "circularList.h"
//#include "engine.h"
//#include "loaddisk.h"
//#include "ops.h"
//#include "pthread_myrwlock.h"
//#include "vfsTree.h"
//#include "wal.h"
//#include "snappy/snappy.h"
#include "../index/database_index.h"
#define UNALIGNED_LOAD32(_p) (*reinterpret_cast<const uint32_t *>(_p))
using namespace std;
struct stu{
    char * name;
};
char ** split(char * src,char * flag){
    char ** ptr;
    char * part=strtok(src,flag);
//    char * part=src;
    *ptr=part;
    char ** result=ptr++;
    while (part!=NULL) {
        part=strtok(NULL,flag);
        *ptr++ = part;
    }
    return result;
}
//void Hl(char * one,char * two){
////    char *
//    char * result=(char *)malloc(strlen(one));
//    strcat(result,one);
//    memcpy(result+strlen(one),two,strlen(two));
//    cout<<result<<endl;
//}
#include "fstream"
using namespace std;

pthread_key_t t;
pthread_t tid;
pthread_t tid1;
pthread_t tid2;
void aaad(){
    char * a=(char *)pthread_getspecific(t);
    cout<<"aaad"<<a<<endl;


}
void * ters(char * database){
    pthread_setspecific(t,database);
    char * dataname=(char *)pthread_getspecific(t);
    aaad();
    cout<<dataname<<endl;
    stu * st=(stu *)malloc(sizeof(stu));
    st->name=(char *)malloc(8);
    st->name=dataname;
    pthread_key_delete(t);
    cout<<"st.name"<<st->name<<endl;
}
void hello(char ** yes){
    cout<<"yesyese"<<endl;
    cout<<*yes++<<endl;
    cout<<*yes++<<endl;
    cout<<*yes<<endl;
}

#include <hash_map>
#include <string>
using namespace std;
int main() {

    z_index(); //调这个函数测试，会出现未定义引用错误





    //文件树的代码测试
//    InitRootNode();
//    VfsNode  * databaseNode = createNode(1,"test",1,NULL,NULL,NULL);
//    databaseNode->filepath=(char *)malloc(sizeof("/home/mikasa/indexTSDB"));
//    databaseNode->filepath="/home/mikasa/indexTSDB";
//    VfsNode  * table1Node = createNode(2,"user",1,NULL,NULL,NULL);
//    VfsNode  * column1Node = createNode(3,"username|char*",1,NULL,NULL,NULL);
//    VfsNode  * column1Node2 = createNode(3,"password|char*",1,NULL,NULL,NULL);
//    VfsNode  * column1Node3 = createNode(3,"age|int",1,NULL,NULL,NULL);
//
//    VfsTree * vfs=createVfsTreeRoot();
//    addVfsTreeNode(vfs->root,databaseNode);
//    addVfsTreeNode(databaseNode,table1Node);
//    addVfsTreeNode(table1Node,column1Node);
//    addVfsTreeNode(table1Node,column1Node2);
//    addVfsTreeNode(table1Node,column1Node3);
//
//    VfsNode * database=findDataBaseByName("test");
//
//    cout<<database->cList->head->name<<endl;
//    cout<<"文件路径"<<database->filepath<<endl;
//
//    char* allColumn = showColumn("test","user");
//
//    char ** result=split(allColumn,",");
//    while (*result!=NULL){
//        char ** reresult=split(*result,"|");
//        while (*reresult!=NULL){
//            printf("split %s\n",(*reresult++));
//            *reresult++;
//        }
//        *result++;
//    }



    //插入环形链表的测试数据
//    value_tuple * dataone=(value_tuple *)malloc(sizeof(value_tuple));
//    tuple_column * username=(tuple_column *)malloc(sizeof(tuple_column));
//    username->columnname=(char *)malloc(8);
//    username->columnname="username";
//    value_tuple * datatwo=(value_tuple *)malloc(sizeof(value_tuple));
//    tuple_column * password=(tuple_column *)malloc(sizeof(tuple_column));
//    value_tuple * datathree=(value_tuple *)malloc(sizeof(value_tuple));
//    tuple_column * age=(tuple_column *)malloc(sizeof(tuple_column));
//    password->columnname=(char *)malloc(8);
//    password->columnname="password";
//    age->columnname=(char *)malloc(3);
//    age->columnname="age";
//    datathree->value="18";
//    long timethree=time(NULL);
//    datathree->timestamp=(char *)malloc(12);
//    sprintf(datathree->timestamp,"%lld",timethree);



//    username->nextcolumn=password;
//    dataone->value=  "hello";
//    datatwo->value=  "123456";
//    dataone->timestamp=(char *)malloc(12);
//    sprintf(dataone->timestamp,"%lld",time(NULL));
//    datatwo->timestamp=(char *)malloc(12);
////    datatwo->timestamp="2345511122";
//    sprintf(datatwo->timestamp,"%lld",time(NULL));
//    dataone->next=datatwo;
//    datatwo->next=datathree;
//    password->nextcolumn=age;
//    initCircularList(1024*1024*25);
////    char * databasename=(char *)malloc(strlen("test"));
////    databasename="test";
////    if (use_database(databasename)!=0){
////        perror("执行失败");
////    }
//    //插入
//    create_cir_nodelist("test","user",username,dataone);
//    pid_t pid;
////    if(pid>0) {
//    foreach_cirlist();
//    cout<<"落盘前"<<endl;
//    manager_writedisk(2);
//    cout<<"落盘后"<<endl;
//
//    foreach_cirlist();
//    }

//    load_disk_method()


//      search_disk("user","/home/mikasa/CLionProjects/G++Test/test.txt",40,55);
//    int fd=open("/home/mikasa/CLionProjects/G++Test/log/log1.txt",O_RDONLY);
//    struct stat statbuf;
//    stat("/home/mikasa/CLionProjects/G++Test/log/log1.txt",&statbuf);
//    int size=statbuf.st_size;
//    char * context=(char *)mmap(NULL,4,PROT_READ,MAP_SHARED,fd,0);
//    cout<<context+5<<endl;
//    char * ptr=(char *)malloc(4);
//    strncpy(ptr,context+5,4);
//    cout<<ptr<<endl;
//    pthread_key_create(&t,NULL);
//
//    pthread_create(&tid, NULL, reinterpret_cast<void *(*)(void *)>(ters), (void *) "user");
//    pthread_create(&tid1, NULL, reinterpret_cast<void *(*)(void *)>(ters), (void *) "teacher");
//    pthread_create(&tid2, NULL, reinterpret_cast<void *(*)(void *)>(ters), (void *) "class");
//
//    sleep(5);




    return 0;
}
