//
// Created by saltfish on 2022/10/4.
//

#ifndef EPOLL_CLIENT_MY_BASES_H
#define EPOLL_CLIENT_MY_BASES_H
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cstring>
#include <iostream>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <typeinfo>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <random>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <future>
#include <cstdlib>
#include <exception>
#include <assert.h>
using namespace std;

int client_run(int port,char* address);
int buf_send(int sfd,char *buf);
int buf_read(int sfd,char* buf);

typedef unsigned char u8;


//以下的参数就是用来做一些异或或者是一些计算用的
static int SELECT = -113;
static int BITS_OF_BYTE = 8;
static int POLYNOMIAL = 0xA001;
static int INIT_VALUE = 0xFFFF;

//协议头
static u8 MESS_SUCCESS=192;

static u8 SELECT_VALUE=65;

static u8 OPER_FAIL=193;

static u8 CONN_FAIL=137;

static u8  CONN_SUCCESS=201;

static u8 CONN_REQUIRE=128;

static u8 RESP_REQUIRE=129;

static u8 DONE_DISCONN=-121;

static u8 USE_DATABASE = 9;

static u8 SHOW_DATABASE = 8;

static u8 CREATE_HANDLE = 3;

static u8 SELECT_HANDLE = 12;

static u8 INSERT_HANDLE = 15;

static u8 SHOW_TABLE = 14;


//这里是协议包的解析包括各个报文头和报文体
class packge{
public:
    u8 head;
    u8 *all;
    u8 pack_head;
    u8 crc[2];
    u8 version = 0;
    u8 len[4];
    int alllen = 0;
    char* result;

    void solve_package(u8 *arr);

    void create_package(char* result,u8 head);

    char* GetResult();

};
//拥来实验的无所谓的函数
u8 * lab_fun();
//将一个4大小的u8数组变成整数
int toInt(u8 *b);
//讲一个整数转换为4大小的数组
u8 *int_to_byte(int len);
//将字符串转换为u8数组
u8 *to_Char(string result);




//全程传递这一个值就行了
void cen_process(packge *packge);


//crc校验

//这个是用来读取一个数组有多长的函数
int size_of_buf(u8 *buf);


//crc用来校验的校验位
int crc16(u8 *bytes);
//封装协议中的crc
u8 * to_crc16(short x);


//未来可能用到的函数（试验用）
void int_unbyte(u8 *arr,int num);
//解析协议查看crc值
int getShort(u8 a,u8 b);

//读功能
void read_runtable(int socketfd);
//写功能
void send_runtable(int sockfd,u8 *cp,int len);

//server开始
int ser_start(int port);
//异或处理
u8* fun_xor(u8 *bytes,int size);


//读取协议报文
string get_Result(u8 *bytes);




//lab
/////////////////////////////字符串轮子2
//字符串轮子
char * str_copy(char *str,char *arr);
//分割时用的方法
//获取长度
int spilt_size(char *a,char *b);
//分割字符
char ** split(char *str,char *dent);
//字符合并
char * str_merge(char *str,char * merstr);

char *strrpc(char *dest,char *src,char *before,char *after);

//////////////////////////////////lab
int sckt_bind_fun(int port);
int epollser_start(int port);
void run_epoll(int listenfd);
void add_event(int epollfd,int fd,int state);
void delete_event(int epollfd,int fd,int state);
void modify_event(int epollfd,int fd,int state);
void handler_eventsserver(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf);
void send_runtable(int new_fd,char *buf);
void rec_runtable(int epollfd,int fd,char *buf);
void handler_accpet(int epollfd,int listenfd);
int epollser_start(int port);


u8 grammer_check(char* mes);


class person{
public:
    int a;
    person(int a){
        a=a;
    }
    int persons(int a){
        return a;
    }
};




#endif //EPOLL_CLIENT_MY_BASES_H
