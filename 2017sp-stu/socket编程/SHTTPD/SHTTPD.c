//
// Created by ferris on 17-4-15.
//

/*
*   主函数
*/

#include "SHTTP.h"


static void sig_int(int num) {
    /* ctrl +c 停止进程 */
    Worker_ScheduleStop();
    return;
}

static void sig_pipe(int num) {
    /*终止程序*/
    return;
}
int do_listen(){
    /*socket init初始化*/

    struct sockaddr_in server;
    int ss = -1;
    int err = -1;
    int reuse =1;
    int ret = 1;

    /* 初始化服务器地址*/
    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    /*信号截取函数*/
    signal(SIGINT, sig_int);
    signal(SIGPIPE, sig_pipe);

    /*申请socket*/
    ss = socket(AF_INET,SOCK_STREAM,0); //流式socket
    if (ss < 0){
        printf("socket error \n");
        return -1;
    }

    /*绑定socket和服务器地址*/
    err = bind(ss,(struct sockaddr*) &server,sizeof(server));
    if (err < 0){
        printf("bind error \n");
        return -2;
    }

    /* server listen ,支持连接client为最大值两倍 */
    err = listen(ss,MaxClient*2 );
    if (err < 0){
        printf("listen error \n");
        return -3;
    }

}
int main(int argc, char *argv[])
{   signal(SIGINT, sig_int);
    int s = do_listen();
    Worker_ScheduleRun(s);
    return 0;


}
