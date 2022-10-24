//
// Created by mikasa on 2022/1/15.
//

#include "database_engine.h"
//#include "global_c.h"
//#include "wal.h"
using namespace std;
char * log_path="/opt/git_Pro/indexDb/IndexDBv1.1/Engine/log/";//测试路径
char * meta_log="/opt/git_Pro/indexDb/IndexDBv1.1/Engine/log/metalog.txt";//测试路径,正式时更改
char * file_path=(char *)malloc(100);//当前日志文件路径
/**
 * 初始化,当第一次写日志时初始化meta日志文件
 * 追加,当日志文件将要大于4096之后，更新metalog 将file_number更新，写入下一个log文件的基本信息和最小的timestamp
 * {@param timestamp}将要更新的日志文件的最小timestamp
 *
 * */
void * update_meta_log(char * timestamp){

    struct stat statbuf;
    stat(meta_log,&statbuf);
    int size=statbuf.st_size;

    if (size<=0){//初始化
        FILE * fp;
        fp=fopen(meta_log,"w");
        if (fp==NULL){
            perror("[ERROR] open log failed\n");
            exit(1);
        }
        char * initmessage=(char *)malloc(125);
        memset(initmessage,0,125);
        strcat(initmessage,"file_number=1\n[filelist]\nfile_name=log1.txt\nmin_timestamp=");
        strcat(initmessage,timestamp);
        strcat(initmessage,"\nfile_path=");
        strcat(initmessage,log_path);
        strcat(initmessage,"log1.txt\n");
        fputs(initmessage,fp);
        fflush(fp);
        memset(file_path,0,strlen(file_path));
        strcat(file_path,log_path);
        strcat(file_path,"log1.txt");
        fclose(fp);

    } else{ //追加
        char * context=read_meta_log();
        int contextlen=strlen(context);
        char * file_number=strtok(context,"\n");
        int valuesize=strlen(file_number)-12;//12是字符串“file_number=”的长度
        char value[valuesize];
        for (int i = 12,j=0; i < 12+valuesize&&j<valuesize; i++,j++) {
            value[j]=file_number[i];
        }
        int ivalue=atoi(value);
        ivalue++;
        sprintf(value,"%d",ivalue);
        char * newfilename=(char *)malloc(3+valuesize);
        memset(newfilename,0,sizeof(newfilename));
        strcat(newfilename,"log");
        strcat(newfilename,value);
        strcat(newfilename,".txt");
        memset(file_path,0,strlen(file_path));
        strcat(file_path,log_path);
        strcat(file_path,newfilename);


        char * updatemessage=(char *)malloc(124+valuesize);
        memset(updatemessage,0,sizeof(updatemessage));
        strcat(updatemessage,"file_number=");
        strcat(updatemessage,value);
        strcat(updatemessage,"\n");
        memcpy(context,updatemessage,strlen(updatemessage));
        munmap(context,contextlen);
        memset(updatemessage,0,12);
        strcat(updatemessage,"\nfile_name=");
        strcat(updatemessage,newfilename);
        strcat(updatemessage,"\nmin_timestamp=");
        strcat(updatemessage,timestamp);
        strcat(updatemessage,"\nfile_path=");
        strcat(updatemessage,log_path);
        strcat(updatemessage,newfilename);

        int fd=open(meta_log,O_WRONLY|O_APPEND);
        if (fd<0){
            perror("[ERROR] open log failed\n");
            exit(1);
        }
        write(fd,updatemessage,strlen(updatemessage));
        close(fd);
    }

}
/**
 * 写入之前的日志，记录加入数据的部分元数据和数据
 * {@param timestamp}数据的时间戳
 * {@param databasename}要插入的库
 * {@param tablename}要插入的表
 * {@param values}要插入的数据列表
 * */
int write_ahead_log(char * timestamp,char * databasename,char * tablename,value_tuple * values){
    if (strlen(file_path)==0){
        update_meta_log(timestamp);
    }
    value_tuple * head=values;
    int valuesize=0;
    while (values!=NULL){
        valuesize+=strlen((char *)values->value);
        values=values->next;
    }
//    char ** ptr;
    char ** ptr=(char **)malloc(valuesize);
    char *temp=(char *)head->value;
    *ptr=temp;
    char ** start=ptr++;
    int cat_times=0;
    head=head->next;
    while (head!=NULL){
        cat_times++;
        (*ptr)=(char *)head->value;
        head=head->next;
        ptr++;
    }
    int messagesize=strlen(timestamp)+strlen(databasename)+strlen(tablename)+valuesize*2+4;
    char * message=(char *)malloc(messagesize);
    memset(message,0,messagesize);
    strcat(message,databasename);
    strcat(message,";");
    strcat(message,tablename);
    strcat(message,";");
    strcat(message,timestamp);
    strcat(message,";");
    for (int i = 0; i <=cat_times; ++i) {
        strcat(message,*start++);
        strcat(message,";");
    }
    strcat(message,"\n");
    struct stat statbuf;
    stat(file_path,&statbuf);
    int size=statbuf.st_size;
    if (messagesize+size>4096) {//更新meta log 并获取新的日志文件路径
        update_meta_log(timestamp);
    }
    FILE * fp;
    fp=fopen(file_path,"a+");
    if (fp==NULL){
        perror("[ERROR] open log failed\n");
        return 0;
    }
    fseek(fp,size,SEEK_SET);
    fputs(message,fp);
    fclose(fp);
    return 1;
}
/**
 * 映射日志文件返回要读取的内容
 *
 *  meta log格式：
 *  file_number //当前到了第几个文件
 *  [file_list]
 *  file_name //日志文件名
 *  min_timestamp
 *  //日志记录最早时间
 *  file_path //日志文件路径
 *
 * */
char * read_meta_log(){
    char * ptr;
    int fd=open(meta_log,O_RDWR);
    if (fd<0){
        perror("[ERROR] open log failed\n");
        exit(1);
    }
    struct stat statbuf;
    stat(meta_log,&statbuf);
    int size=statbuf.st_size;
    ptr=(char *)mmap(NULL,size,PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    return ptr;
}
IBool load_ahead_log(head_tuple * load_list){
    return ITrue;
}
