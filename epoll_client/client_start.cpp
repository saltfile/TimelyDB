//
// Created by saltfish on 2022/10/5.
//

#include "my_bases.h"

#define BUF_LENS 4096


#define LIGHT_CYAN   "\033[1;36m"
#define NONE         "\033[m";
#define LIGHT_BLUE   "\033[1;34m"
#define LIGHT_PURPLE "\033[1;35m"
#define LIGHT_PURPLE "\033[1;35m"
int client_run(int port,char* address){
    printf(LIGHT_BLUE"\n"
           " ______                        ___             ____    ____      \n"
           "/\\__  _\\__                    /\\_ \\           /\\  _`\\ /\\  _`\\    \n"
           "\\/_/\\ \\/\\_\\    ___ ___      __\\//\\ \\    __  __\\ \\ \\/\\ \\ \\ \\L\\ \\  \n"
           "   \\ \\ \\/\\ \\ /' __` __`\\  /'__`\\\\ \\ \\  /\\ \\/\\ \\\\ \\ \\ \\ \\ \\  _ <' \n"
           "    \\ \\ \\ \\ \\/\\ \\/\\ \\/\\ \\/\\  __/ \\_\\ \\_\\ \\ \\_\\ \\\\ \\ \\_\\ \\ \\ \\L\\ \\       port: %d\n "
           "     \\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\____\\/\\____\\\\/`____ \\\\ \\____/\\ \\____/      host: localhost\n"
           "      \\/_/\\/_/\\/_/\\/_/\\/_/\\/____/\\/____/ `/___/> \\\\/___/  \\/___/ \n"
           "                                            /\\___/               \n"
           "                                            \\/__/                \n\033[m"
           ,port);
    printf(
          "    Preliminary client test of 2022-10 test version\n"
    "It is not guaranteed to be very stable, but it can be used               \n"
          "                                                 \n");


    int sfd,ret;
    char writebuf[BUF_LENS] ={0};
    char readbuf[BUF_LENS] = {0};
    ssize_t send_bytes,recv_bytes;
    struct sockaddr_in dest;
    socklen_t len = sizeof(dest);
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1)
    {
        perror("socket fail");
        return -1;
    }
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    dest.sin_addr.s_addr = inet_addr(address);
    ret = connect(sfd,(const struct sockaddr *)&dest,len);


    if(ret == -1)
    {
        perror("connect fail");
        return -1;
    }


    while(1)
    {
        //write
        if (!buf_send(sfd,writebuf)){
            continue;
        }
        if (buf_read(sfd,readbuf)){
//            printf("%s\n",readbuf);
        } else{
            printf("读取信息失败\n");
            continue;
        }

    }
    close(sfd);


}


//封包协议测试点
int buf_send(int sfd,char *buf){

    printf("TimelyDB >");
    memset(buf,0,BUF_LENS);
    fgets(buf,BUF_LENS,stdin);
    if(strncmp(buf,"quit",4) == 0)
    {
        printf(LIGHT_BLUE"BYE BYE!!\n\033[m");
        exit(0);
    }
    packge send_packge;

    //拼接报文体
    u8 head = grammer_check(buf);
    if (head == 0)
    {
        cout<<LIGHT_PURPLE<<"Unknown statement, please re-enter\033[m"<<endl;
        return 0;
    }


    if (head!=0){
        send_packge.create_package(buf,head);
    }


    int send_bytes = send(sfd,send_packge.all,strlen((char *)send_packge.all),0);



    if(send_bytes == -1)
    {
        perror("send fail");
        return 0;
    }
    return 1;
}



int buf_read(int sfd,char* buf){
    memset(buf,0,BUF_LENS);
    int recv_bytes = recv(sfd,buf,BUF_LENS,0);

    packge *packge1 = (packge *)malloc(sizeof(packge));
    packge1->solve_package((u8 *)buf);
    //展示结果
    cout<<LIGHT_BLUE<<packge1->result<<NONE;

    if(recv_bytes == -1)
    {
        return 0;
    }
    else if(recv_bytes == 0)
    {
        return 0;
    }
    return 1;

}






