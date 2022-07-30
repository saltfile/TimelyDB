//
// Created by saltfish on 2022/1/9.
//

#include "../ser_drive.h"

/**
 * TODO:用来检测数组内容的长度
 * @param buf被检测的数组
 * @return 数组长度
 * */


int size_of_buf(u8 *buf){
    for(int i = 0;i < 1024;i++){
        if(buf[i] == NULL){
            return i+1;
        }
    }
    return sizeof(buf);
}


/**
 * TODO:正常的c语言服务端开启
 * @param port:端口号
 * @return 只是代表结束，没什么意义
 * */
int ser_start(int port){
    int listenfd,connfd;
    socklen_t client;
    struct  sockaddr_in cliaddr,seraddr;

    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(port);

    bind(listenfd,(struct sockaddr *) &seraddr,sizeof(seraddr));
    listen(listenfd,1024);

    for(;;){
        client = sizeof(cliaddr);
        connfd = accept(listenfd,(struct  sockaddr *) &cliaddr,&client);
        read_runtable(connfd);
    }
}


/**
 * TODO:类似于java的网络读io
 * @param socketfd:类似于java的socket
 * */
void read_runtable(int socketfd){
    ssize_t n;
    u8 buf[1024];

    char *ptr = (char *)buf;
    memset(ptr,0,1024);
    int time = 0;
    for (;;) {
        fprintf(stdout, "收到消息");
        if ((n = read(socketfd, buf, 1024)) == 0)
            return;

        time++;
        cout<<buf<<endl;
        cout<<"========================"<<endl;
        int len = size_of_buf(buf);




    packge *packge1 = (packge *)malloc(sizeof(packge));
    packge1->solve_package(buf);
    printf("%d\n",packge1->pack_head);
    cout<<packge1->result<<endl;

    // TODO:经过了数据库的一些操作得到答案,在这里需要联调

        packge *packge2 = (packge *)malloc(sizeof(packge));

        cout<<endl;

        string res = " i m a massage";

        //判断协议头的目的
        switch (packge1->pack_head) {
            case 128 :packge2->create_package("successfluy into database",CONN_SUCCESS);break;
            case 65 :packge2->create_package("id,name,age;1,xxsadaasdx,13;2,yydssdy,16",MESS_SUCCESS);break;
            case 0 :packge2->create_package("success is user add",MESS_SUCCESS);break;
            case 1 :packge2->create_package("err is del user",OPER_FAIL);break;
            case 2 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 3 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 4 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 5 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 6 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 7 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 8 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 9 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 10 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 11 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 12 :packge2->create_package("succses",MESS_SUCCESS);break;
            case 13 :packge2->create_package("succses",MESS_SUCCESS);break;



            default:packge2->create_package("error",CONN_FAIL);
        }

    send_runtable(socketfd,packge2->all,packge2->alllen);
        cout<<"解析*1"<<endl;

        memset(buf,0,1024);
        usleep(1000);
        free(packge1);
        free(packge2);
    }
}


/**
 * TODO:类似于java的网络写io
 * @param sockfdsocketfd:类似于java的socket cp要发送的消息,len消息长度
 *
 * */

void send_runtable(int sockfd,u8 *cp,int len){
    size_t remaining = len;
    while (remaining) {
        int n_written = send(sockfd, cp, remaining, 0);
        fprintf(stdout, "send into buffer %ld \n", n_written);
        if (n_written <= 0) {
            error(1, errno, "send failed");
            return;
        }
        remaining -= n_written;
    }

    return;
}


void process(packge *res){

}


void cen_process(packge *packge){
    //参数:就是传过来的原始包


    process(packge);

    if(packge->pack_head == 192){

    }

}



