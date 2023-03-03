
#include "my_bases.h"


#define MAXLINE 4096

int main(int argc,char** argv) {




    client_run(8080,"192.168.10.105");
//person person(2);
//    cout<<person.a;
//cout<<person.persons(3)<<endl;
//    cout<<person.a;

//    person person;
//    person.name = "aaaa";
//    person.age = 11;
//    cout<<person.name<<endl;
//    cout<<person.age<<endl;

//    client_run(atoi(argv[0]),argv[1]);
//
//    int sfd,ret;
//    char buf[1024] ={0};
//    char readbuf[1024] = {0};
//    ssize_t send_bytes,recv_bytes;
//    struct sockaddr_in dest;
//    socklen_t len = sizeof(dest);
//    sfd = socket(AF_INET,SOCK_STREAM,0);
//    if(sfd == -1)
//    {
//        perror("socket fail");
//        return -1;
//    }
//    dest.sin_family = AF_INET;
//    dest.sin_port = htons(9876);
//    dest.sin_addr.s_addr = inet_addr("127.0.0.1");
//    ret = connect(sfd,(const struct sockaddr *)&dest,len);
//    if(ret == -1)
//    {
//        perror("connect");
//        return -1;
//    }
//    while(1)
//    {
//        printf("input ");
//        memset(buf,0,sizeof(buf));
//        fgets(buf,sizeof(buf),stdin);
//        if(strncmp(buf,"quit",4) == 0)
//        {
//            printf("client shutdown\n");
//            break;
//        }
//        send_bytes = send(sfd,buf,strlen(buf),0);
//        if(send_bytes == -1)
//        {
//            perror("send fail");
//            return -1;
//        }
//
//        memset(readbuf,0,sizeof(readbuf));
//
//        recv_bytes = recv(sfd,readbuf,sizeof(readbuf),0);
//        if(recv_bytes == -1)
//        {
//            perror("recv");
//            return -1;
//        }
//        else if(recv_bytes == 0)
//        {
//            printf("client shutdaown\n");
//            break;
//        }
//        printf("buf :%s\n",readbuf);
//
//
//
//
//
//    }
//    close(sfd);

    return 0;
}
