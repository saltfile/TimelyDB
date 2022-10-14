//
// Created by saltfish on 2022/1/9.
//

#include "../ser_drive.h"
#include "../../grammar/Myall.h"
/**
 * TODO:用来检测数组内容的长度
 * @param buf被检测的数组
 * @return 数组长度
 * */


int size_of_buf(u8 *buf){
    for(int i = 0;i < 1002555l;i++){
        if(buf[i] == NULL){
            return i+1;
        }
    }
    return sizeof(buf);
}

//将原来的server变为epoll

int epollser_start(int port) {
    int  iSocketFD;
    iSocketFD = sckt_bind_fun(port);
    listen(iSocketFD,5);
    run_epoll(iSocketFD);
    return 0;
}
void run_epoll(int listenfd){
    int epollfd;
    struct epoll_event events[20];
    int ret;
    char buf[4096];
    memset(buf,0,4096);
    /*创建一个描述符*/
    epollfd = epoll_create(1024);

    /*添加监听描述符事件*/
    add_event(epollfd,listenfd,EPOLLIN);
    while(1){
        /*获取已经准备好的描述符事件*/
        ret = epoll_wait(epollfd,events,20,-1);
        handler_eventsserver(epollfd,events,ret,listenfd,buf);//重点注意这个ret，它返回的是已经有事儿的fd的个数
        //这样一会儿轮循的就不是所有的fd了
    }
    close(epollfd);
}
void handler_eventsserver(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf){
    int i;
    int fd;
    /*进行选好遍历*/
    for (i = 0;i < num;i++){
        fd = events[i].data.fd;
        /*根据描述符的类型和事件类型进行处理*/
        if ((fd == listenfd) &&(events[i].events & EPOLLIN)) {handler_accpet(epollfd,listenfd);}
        else if (events[i].events & EPOLLIN)
            rec_runtable(epollfd,fd,buf);
        else if (events[i].events & EPOLLOUT)
            send_runtable(epollfd,buf);
    }
}
//epoll链接
void handler_accpet(int epollfd,int listenfd){
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t  cliaddrlen;
    clifd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen);
    if (clifd == -1)
        perror("accpet error:");
    else{
        printf("accept a new client: %s:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
        /*添加一个客户描述符和事件*/
        add_event(epollfd,clifd,EPOLLIN);
    }
}


//epoll接收
void rec_runtable(int epollfd,int fd,char *buf)
{
    int nread;
    memset(buf,0,sizeof(buf));
    nread = read(fd,buf,4096);
    if (nread == -1)
    {
        perror("read error:");
        close(fd);
        delete_event(epollfd,fd,EPOLLIN);
    }
    else if (nread == 0)
    {
        fprintf(stderr,"client close.\n");
//        close(fd);
        delete_event(epollfd,fd,EPOLLIN);
    }
    else
        {
        char *ptr = (char *)buf;
        int time = 0;
            fprintf(stdout, "收到消息");

            time++;
            cout<<buf<<endl;
            cout<<"========================"<<endl;
            int len = size_of_buf((u8 *)buf);

            packge *packge1 = (packge *)malloc(sizeof(packge));
            packge1->solve_package((u8 *)buf);
            printf("%d\n",packge1->pack_head);
            cout<<packge1->result<<endl;

            // TODO:经过了数据库的一些操作得到答案,在这里需要联调

            packge *packge2 = (packge *)malloc(sizeof(packge));
            memset(packge2,0,sizeof(packge2));
            cout<<endl;

            string res = " i m a massage";

            //判断协议头的目的
            switch (packge1->pack_head)
            {
                case 128 :packge2->create_package("successfluy into database",CONN_SUCCESS);break;
                case 65 :packge2->create_package("id,name,age;1,xxsadaasdx,13;2,yydssdy,16",MESS_SUCCESS);break;
                case 0 :packge2->create_package(packge1->result,MESS_SUCCESS);break;
                case 1 :packge2->create_package("err is del user",MESS_SUCCESS);break;
                case 2 :packge2->create_package("succses",MESS_SUCCESS);break;
                case 3 :packge2->create_package(create_handle(packge1->result),MESS_SUCCESS);break;
                case 4 :packge2->create_package("succses",MESS_SUCCESS);break;
                case 5 :packge2->create_package("succses",MESS_SUCCESS);break;
                case 6 :packge2->create_package("succses",MESS_SUCCESS);break;
                case 7 :packge2->create_package("succses",MESS_SUCCESS);break;
                case 14:packge2->create_package(show_Table_handle(packge1->result),MESS_SUCCESS);break;
                case 8 :packge2->create_package(show_DB_handle(packge1->result),MESS_SUCCESS);break;
                case 9 :packge2->create_package(use_handle(packge1->result),MESS_SUCCESS);break;
                case 10 :packge2->create_package("succses",MESS_SUCCESS);break;
                case 11 :packge2->create_package("succses",MESS_SUCCESS);break;
                case 12 :packge2->create_package("succses",MESS_SUCCESS);break;
                case 13 :packge2->create_package("succses",MESS_SUCCESS);break;
                default:packge2->create_package("error",CONN_FAIL);
            }
            cout<<"解析*1"<<endl;
            send_runtable(fd,(char *)packge2->all);
            memset(buf,0,4096);
            usleep(1000);
            free(packge1);
            free(packge2);
        }
//        printf("read message is : %s",buf);
//        char *message = str_copy(message,buf);
        modify_event(epollfd,fd,EPOLLIN);
    }
//epoll发送
void send_runtable(int new_fd,char *buf)
{
    send(new_fd, buf, strlen(buf), 0);
}

int sckt_bind_fun(int port)
{
    int iSocketFD = 0;  //socket句柄
    int new_fd = 0;    //建立连接后的句柄
    struct sockaddr_in stLocalAddr = {0}; //本地地址信息结构图，下面有具体的属性赋值
    struct sockaddr_in stRemoteAddr = {0}; //对方地址信息
    socklen_t socklen = 0;

    iSocketFD = socket(AF_INET, SOCK_STREAM, 0); //建立socket
    if (0 > iSocketFD)
    {
        printf("创建socket失败！\n");
        return 0;
    }

    stLocalAddr.sin_family = AF_INET;  /*该属性表示接收本机或其他机器传输*/
    stLocalAddr.sin_port = htons(port); /*端口号*/
    stLocalAddr.sin_addr.s_addr = htonl(INADDR_ANY); /*IP，括号内容表示本机IP*/

    //绑定地址结构体和socket
    if (0 > bind(iSocketFD, (struct sockaddr *) &stLocalAddr, sizeof(stLocalAddr)))
    {
        printf("绑定失败！\n");
        exit(-1);
    }

    //开启监听 ，第二个参数是最大监听数
    if (0 > listen(iSocketFD, 128))
    {
        printf("监听失败！\n");
        exit(-2);
    }
    printf("iSocketFD: %d\n", iSocketFD);
    return iSocketFD;
}

void add_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
}
void delete_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}

void modify_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}

/**
 * TODO:正常的c语言服务端开启
 * @param port:端口号
 * @return 只是代表结束，没什么意义
 * */
//int ser_start(int port)
//{
//    int listenfd,connfd;
//    socklen_t client;
//    struct  sockaddr_in cliaddr,seraddr;
//
//    listenfd = socket(AF_INET,SOCK_STREAM,0);
//    bzero(&seraddr,sizeof(seraddr));
//    seraddr.sin_family = AF_INET;
//    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
//    seraddr.sin_port = htons(port);
//
//    bind(listenfd,(struct sockaddr *) &seraddr,sizeof(seraddr));
//    listen(listenfd,1024);
//
//    for(;;){
//        client = sizeof(cliaddr);
//        connfd = accept(listenfd,(struct  sockaddr *) &cliaddr,&client);
//        read_runtable(connfd);
//    }
//}


/**
 * TODO:类似于java的网络读io
 * @param socketfd:类似于java的socket
 * */
//void read_runtable(int socketfd)
//{
//    ssize_t n;
//    u8 buf[1024];
//
//    char *ptr = (char *)buf;
//    memset(ptr,0,1024);
//    int time = 0;
//    for (;;) {
//        fprintf(stdout, "收到消息");
//        if ((n = read(socketfd, buf, 1024)) == 0)
//            return;
//
//        time++;
//        cout<<buf<<endl;
//        cout<<"========================"<<endl;
//        int len = size_of_buf(buf);
//
//
//
//
//    packge *packge1 = (packge *)malloc(sizeof(packge));
//    packge1->solve_package(buf);
//    printf("%d\n",packge1->pack_head);
//    cout<<packge1->result<<endl;
//
//    // TODO:经过了数据库的一些操作得到答案,在这里需要联调
//
//        packge *packge2 = (packge *)malloc(sizeof(packge));
//
//        string res = " i m a massage";
//
//        //判断协议头的目的
//        switch (packge1->pack_head) {
//            case 128 :packge2->create_package("successfluy into database",CONN_SUCCESS);break;
//            case 65 :packge2->create_package("id,name,age;1,xxsadaasdx,13;2,yydssdy,16;",MESS_SUCCESS);break;
//            case 0 :packge2->create_package("success is user add",MESS_SUCCESS);break;
//            case 1 :packge2->create_package("err is del user",OPER_FAIL);break;
//            case 2 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 3 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 4 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 5 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 6 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 7 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 8 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 9 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 10 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 11 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 12 :packge2->create_package("succses",MESS_SUCCESS);break;
//            case 13 :packge2->create_package("succses",MESS_SUCCESS);break;
//            default:packge2->create_package("error",CONN_FAIL);
//        }
//
//         send_runtable(socketfd,packge2->all,packge2->alllen);
//        cout<<"解析*1"<<endl;
//        memset(buf,0,1024);
//        usleep(1000);
//        free(packge1);
//        free(packge2);
//    }
//}

//void send_runables(int epollfd,int fd,char *buf)
//{
//    send(epollfd, buf, strlen(buf), 0);
//}
/**
 * TODO:类似于java的网络写io
 * @param sockfdsocketfd:类似于java的socket cp要发送的消息,len消息长度
 *
 * */

//void send_runtable(int sockfd,u8 *cp,int len)
//{
//    size_t remaining = len;
//    while (remaining) {
//        int n_written = send(sockfd, cp, remaining, 0);
//        fprintf(stdout, "send into buffer %ld \n", n_written);
//        if (n_written <= 0) {
//            error(1, errno, "send failed");
//            return;
//        }
//        remaining -= n_written;
//    }
//
//    return;
//}


void process(packge *res)
{

}


void cen_process(packge *packge)
{
    //参数:就是传过来的原始包
    process(packge);

    if(packge->pack_head == 192){

    }

}



