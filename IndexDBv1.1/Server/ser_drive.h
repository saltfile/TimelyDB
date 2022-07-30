//
// Created by saltfish on 2022/1/9.
//

#ifndef SERVER_SER_DRIVE_H
#define SERVER_SER_DRIVE_H
#include <error.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <vector>
#include <time.h>
#include <iconv.h>
#include <bitset>
using namespace std;
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

//这里是协议包的解析包括各个报文头和报文体
class packge{
public:
    u8 *all;
      u8 pack_head;
      u8 crc[2];
      u8 version = 0;
      u8 len[4];
      int alllen = 0;
      string result;

      void solve_package(u8 *arr);

      void create_package(string result,u8 head);

      string GetResult();

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







#endif //SERVER_SER_DRIVE_H
