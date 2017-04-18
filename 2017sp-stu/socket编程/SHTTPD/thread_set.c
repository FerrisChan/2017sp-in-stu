//
// Created by ferris on 17-4-15.
//

#include <pthread.h>
#include <malloc.h>
#include "SHTTP.h"

//参数初始化
static int MaxClient = 500;  //最大线程数
static int workersum = 0; //工作线程的数量
static struct worker_ctl *wctls = NULL ; //线程选项
pthread_mutex_t thread_init = PTHREAD_MUTEX_INITIALIZER; //init 线程锁
static int WORKER_ISSTATUS(int status);
static void Worker_Init();
static int Worker_Add(int i);
static void Worker_Delete(int i);
static void Worker_Destory();

// 线程初始化
static void Worker_Init()
{
    printf("==> Worker_Init is working \n");
    int i =0 ;
    //初始化总控参数
    wctls = (struct worker_ctl*)malloc(sizeof(struct worker_ctl)*MaxClient);
    memset(wctls,0,sizeof(*wctls)*MaxClient);



}

int Worker_ScheduleRun(int ss)
{
    printf("==> Worker_ScheduleRun is working \n");
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    Worker_Init();
}