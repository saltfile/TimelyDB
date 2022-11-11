//
// Created by mikasa on 2021/11/12.
//


#include "database_engine.h"

struct passwd *username=getpwuid(getuid());
IBool isinit;
void mkdir_indexdb(){//初始化数据库
    int size_mkdir=strlen("/home/")+strlen(username->pw_name)+strlen("/indexTSDB/");

    char * path=(char *)malloc(size_mkdir);
    memset(path,0,size_mkdir);
    strcat(path,"/home/");
    strcat(path,username->pw_name);
    strcat(path,"/indexTSDB");
    if (access(path,F_OK)){
        int isCreate = mkdir(path,S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
        if( !isCreate )
            printf("成功创建:%s\n",path);
        else
            printf("创建目录失败! error : %s \n",isCreate,path);
    } else{
        printf("创建完成");
    }

}



passwd* get_user(){
    return username;
}

//void mkdir_indexdb(){//初始化数据库
//    int size_mkdir=sizeof(strlen("/home/")+strlen(username->pw_name)+strlen("/indexTSDB/"));
//    char * mkdir=(char *)malloc(size_mkdir);
//    memset(mkdir,0,size_mkdir);
//    strcat(mkdir,"mkdir /home/");
//    strcat(mkdir,username->pw_name);
//    strcat(mkdir,"/indexTSDB");
//    if (system(mkdir)<0){
////        perror("[ERROR] mkdir the indexTSDB fail\n");
//    };
//    isinit=ITrue;
//    memset(mkdir,0,size_mkdir);
//    strcat(mkdir,"touch /home/");
//    strcat(mkdir,username->pw_name);
//    strcat(mkdir,"/user");
//    if (system(mkdir)<0){
////        perror("[ERROR] touch the user table fail\n");
//    }
//    memset(mkdir,0,size_mkdir);
//    free(mkdir);
//}
char *mkdir_database(char * databasename){//创建数据库,并返回数据库路径
    if (isinit!=ITrue){
        mkdir_indexdb();
    }
    int yy = strlen("/home/")+strlen(username->pw_name)+strlen("/indexTSDB/")+strlen(databasename);
    char *path=(char *)malloc(yy);

    memset(path,0,yy);
    strcat(path,"/home/");
    strcat(path,username->pw_name);
    strcat(path,"/indexTSDB/");
    strcat(path,databasename);
    if (access(path,F_OK)){
        int isCreate = mkdir(path,S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
        if( !isCreate ){
            printf("成功创建:%s\n",path);
            return path;
        }else{
            printf("创建数据库失败! error : %s \n",isCreate,databasename);
            return NULL;
        }
    } else{
        printf("\n已有相同的数据库\n");
    }
    return NULL;
}
//旧
//void touch_table(char * databasename,char * tablename,char** columns,int columnSize){//创建表
//    int size_touch=sizeof(strlen("touch /home/")+strlen(username->pw_name)+strlen("/indexTSDB/")+strlen(databasename)+strlen("/")+strlen(tablename));
//    char * touch=(char *)malloc(size_touch);
//    memset(touch,0,size_touch);
//    strcat(touch,"touch /home/");
//    strcat(touch,username->pw_name);
//    strcat(touch,"/indexTSDB/");
//    strcat(touch,databasename);
//    strcat(touch,"/");
//    strcat(touch,tablename);
//    if (system(touch)<0){
//        perror("[ERROR] create table fail\n");
//    }
//    char * filepath=(char *)malloc(size_touch-1);
//    memset(filepath,0,size_touch-6);
//    strcat(filepath,"/home/");
//    strcat(filepath,username->pw_name);
//    strcat(filepath,"/indexTSDB/");
//    strcat(filepath,databasename);
//    strcat(filepath,"/");
//    strcat(filepath,tablename);
//    strcat(filepath,".tsdb");
//    FILE *write=fopen(filepath,"a");
//    if (write==NULL){
//        perror("[ERROR] open file fail\n");
//    }
//    for (int i = 0; i < columnSize; ++i) {
//        fwrite(columns[i],strlen(columns[i]),1,write);
//        fwrite(";",1,1,write);
//    }
//}

//新
bool touch_table(char * databasename,char * tablename,char** columns,int columnSize){//创建表
    int size_touch=strlen("/home/")+strlen(username->pw_name)+strlen("/indexTSDB/")+strlen(databasename)
                          +strlen("/")+strlen(tablename);
    char * touch=(char *)malloc(size_touch);
    memset(touch,0,size_touch);
    strcat(touch,"/home/");
    strcat(touch,username->pw_name);
    strcat(touch,"/indexTSDB/");
    strcat(touch,databasename);
    strcat(touch,"/");
    strcat(touch,tablename);

    if (access(touch,F_OK)){
        FILE *fd = fopen(touch,"a");
        fclose(fd);
    } else{
        perror("表已存在");
        return false;
    }
    char * filepath=(char *)malloc(size_touch+5);
    memset(filepath,0,size_touch+5);
    strcat(filepath,"/home/");
    strcat(filepath,username->pw_name);
    strcat(filepath,"/indexTSDB/");
    strcat(filepath,databasename);
    strcat(filepath,"/");
    strcat(filepath,tablename);
    strcat(filepath,".tsdb");
    FILE *write=fopen(filepath,"a");
    if (write==NULL){
        perror("[ERROR] open file fail\n");
    }
    for (int i = 0; i < columnSize; ++i) {
        char *s = columns[i];
        fwrite(columns[i],strlen(columns[i]),1,write);
        fwrite(";",1,1,write);
    }
    fflush(write);
    return true;
//    fclose(write);
}


void rm_database(char * databasename){//删除数据库
    int size_rm=strlen("rm -rf /home/")+strlen(username->pw_name)+strlen("/")+strlen(databasename);
    char * rm_database=(char * )malloc(size_rm);
    strcat(rm_database,"rm -rf /home/");
    strcat(rm_database,username->pw_name);
    strcat(rm_database,"/");
    strcat(rm_database,databasename);
    if (system(rm_database)<0){
        perror("[ERROR] rm the database fail\n");
    }
}
void rm_table(char * databasename,char * tablename){//删除表
    int size_rm=strlen("rm /home/")+strlen(username->pw_name)+strlen("/")+strlen(databasename)+strlen("/")+strlen(tablename);
    char * rm_table=(char *)malloc(size_rm);
    strcat(rm_table,"rm /home/");
    strcat(rm_table,username->pw_name);
    strcat(rm_table,"/");
    strcat(rm_table,databasename);
    strcat(rm_table,"/");
    strcat(rm_table,tablename);
    if (system(rm_table)<0){
        perror("[ERROR] rm the table fail\n");
    }
}