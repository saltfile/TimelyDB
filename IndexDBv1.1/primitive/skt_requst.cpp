//
// Created by saltfish on 2021/10/26.
//


#include <string>
#include <list>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <error.h>
#include <netinet/in.h>
#include <cstring>
#include "primitive.h"


using namespace std;

#define MAX_SIZE 4096


void read_data(int sockfd) {
    ssize_t n;
    char buf[1024];
    char *ptr = (char *)buf;

    int time = 0;
    for (;;) {
        fprintf(stdout, "block in read\n");
        if ((n = read(sockfd, buf, 1024)) == 0)
            return;
        string str = buf;

        time++;
        cout<<buf<<endl;
        usleep(1000);
    }
}


void send_data(int sockfd){
    string query;
    cin>>query;
    const char *cp;
    cp = query.data();

    size_t remaining = query.size();
    while (remaining) {
        int n_written = send(sockfd, cp, remaining, 0);
        fprintf(stdout, "send into buffer %ld \n", n_written);
        if (n_written <= 0) {
            error(1, errno, "send failed");
            return;
        }
        remaining -= n_written;
        cp += n_written;
    }

    return;
}


int ser_lab() {
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(7878);

    /* bind到本地地址，端口为12345 */
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    /* listen的backlog为1024 */
    listen(listenfd, 1024);

    /* 循环处理用户请求 */
    for (;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        send_data(connfd);/* 读取数据 */

    }
    close(connfd);
    return 0;
}






















void ser_start(){

    int lisent,conntion;

    struct sockaddr_in ser_addr;

    char buf[4096];

    int n;

    if( (lisent = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return ;
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_addr.sin_port = htons(8081);

    if( bind(lisent, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        return ;
    }

    printf("======waiting for client's request======\n");
        if( (conntion = accept(lisent, (struct sockaddr*)NULL, NULL)) == -1){
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            return;
        }
        n = recv(conntion, buf, MAX_SIZE, 0);
        buf[n] = '\0';
        printf("recv msg from client: %s\n", buf);

    close(conntion);

}