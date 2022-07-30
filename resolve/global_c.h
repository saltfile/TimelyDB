//
// Created by maomao on 2021/8/20.
//
#ifndef INDEXTSDB_V1_0_GLOBAL_C_H
#define INDEXTSDB_V1_0_GLOBAL_C_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h>
#include <assert.h>
//#include <uv.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
//#include <pthread.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include "fstream"
#include "iostream"
#include <pwd.h>
//#include "snappy/snappy.h"
#include "database_engine.h"

using namespace std;
//#include "engine/vfsTree.h"
//
//
////server
//#include "server/acceptor.h"
//#include "server/buffer.h"
//#include "server/channel.h"
//#include "server/channel_map.h"
//#include "server/event_dispatcher.h"
//#include "server/event_loop.h"
//#include "server/event_loop_thread.h"
//#include "server/lntp_request.h"
//#include "server/lntp_response.h"
//#include "server/lntp_server.h"
//#include "server/tcp_connection.h"
//#include "server/tcp_server.h"
//#include "server/thread_pool.h"
//
////lib
//#include "lib/log.h"
//#include "lib/utils.h"

enum DataTypes{
    BYTE=0,
    INT=1,
    FLOAT,
    DOUBLE,
    DECIMAL,
    VARCHAR=5,
    TEXT,
    TIME,
    TIMESTAMP=8
};

#define SERV_PORT   9999
#define MAXLINE     4096
#define LISENQ      1024
#define BUFFER_SIZE 4096


#endif //INDEXTSDB_V1_0_GLOBAL_C_H
