//
// Created by ferris on 17-4-15.
//

#include <pthread.h>
#include <malloc.h>
#include <zconf.h>
#include "SHTTP.h"

//参数初始化
static int MaxClient = 3;  //最大线程数,根据CPU核数2等因素设置为3
static int workersnum = 0; //工作线程的数量
static struct worker_ctl *wctls = NULL ; //线程选项
pthread_mutex_t thread_init = PTHREAD_MUTEX_INITIALIZER; //init 线程锁
static int WORKER_ISSTATUS(int status);
static void Worker_Init();
static int Worker_Add(int i);
static void Worker_Delete(int i);
static void Worker_Destory();


static void do_work(struct worker_ctl *wctl)
{
    printf("==>do_work\n");
    struct timeval tv;		/*超时时间*/
    fd_set rfds;			/*读文件集*/
    int fd = wctl->conn.cs;/*客户端的套接字描述符*/

//    struct vec *req = &wctl->conn.req;/*请求缓冲区向量*/

    int retval = 1;

    for(;retval > 0;)
    {
        /*清读文件集,将客户端连接
            描述符放入读文件集*/
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        /*设置超时*/
        tv.tv_sec = 300;//conf_para.TimeOut;
        tv.tv_usec = 0;

        /*超时读数据*/
        retval = select(fd + 1, &rfds, NULL, NULL, &tv);
        switch(retval)
        {
            case -1:/*错误*/
                close(fd);
                break;
            case 0:/*超时*/
                close(fd);
                break;
//            default:
//                printf("select retval:%d\n",retval);
//                if(FD_ISSET(fd, &rfds))/*检测文件*/
//                {
//                    memset(wctl->conn.dreq, 0, sizeof(wctl->conn.dreq));
//                    /*读取客户端数据*/
//                    req->len =
//                            read(wctl->conn.cs, wctl->conn.dreq, sizeof(wctl->conn.dreq));
//                    req->ptr = wctl->conn.dreq;
//                    printf("Read %d bytes,'%s'\n",req->len,req->ptr);
//                    if(req->len > 0)
//                    {
//                        /*分析客户端的数据*/
//                        wctl->conn.con_req.err =	Request_Parse(wctl);
//                        /*处理并响应客户端请求*/
//                        Request_Handle(wctl);
//                    }
//                    else
//                    {
//                        close(fd);
//                        retval = -1;
//                    }
//                }
        }
    }
    printf("<==do_work\n");
}


static void *worker(void *arg)
{
    printf("==>worker\n");
//    struct worker_ctl *ctl = (struct worker_ctl *)arg;
//    struct worker_opts *self_opts = &ctl->opts;
//
//    pthread_mutex_unlock(&thread_init);
//    /*初始化线程为空闲，等待任务*/
//    self_opts->flags = WORKER_IDEL;
//
//    /*如果主控线程没有让此线程退出，则循环处理任务*/
//    for(;self_opts->flags != WORKER_DETACHING;)
//    {
//        /*查看是否有任务分配*/
//        int err = pthread_mutex_trylock(&self_opts->mutex);
//        if(err)
//        {
//            sleep(1);
//            continue;
//        }
//        else
//        {
//            /*有任务，do it*/
//            printf("Do task\n");
//            self_opts->flags = WORKER_RUNNING;
//            do_work(ctl);
//            close(ctl->conn.cs);
//            ctl->conn.cs = -1;
//            if(self_opts->flags == WORKER_DETACHING)
//                break;
//            else
//                self_opts->flags = WORKER_IDEL;
//        }
//    }
//
//    /*主控发送退出命令*/
//    /*设置状态为已卸载*/
//    self_opts->flags = WORKER_DETACHED;
//    workersnum--;/*工作线程-1*/

    printf("<==worker\n");
    return NULL;
}

// 线程状态查询
int WORKER_ISSTATUS(int status)
{
    int i = 0;
    for(i = 0; i<MaxClient;i++)
    {
        if(wctls[i].opts.flags == status)
            return i;
    }

    return -1;
}

// 线程初始化
static void Worker_Init()
{
    printf("==> Worker_Init is working \n");
    int i =0 ;
    //初始化总控参数
    wctls = (struct worker_ctl*)malloc(sizeof(struct worker_ctl)*MaxClient);
    memset(wctls,0,sizeof(*wctls)*MaxClient);  //清零
    for (i = 0; i < MaxClient; i++)
    {
        // opts&conn 结构与worker_ctl 结构形成回指针
        wctls[i].opts.work = &wctls[i] ;
        wctls[i].conn.work = &wctls[i] ;

        // opts 结构的初始化
        wctls[i].opts.flags = WORKER_DETACHED ;
        pthread_mutex_init(&wctls[i].opts.mutex,NULL);
        pthread_mutex_lock(&wctls[i].opts.mutex);

    }
    printf("<== Worker_Init has worked  \n");
}

/* 增加线程数 */
int Worker_Add (int i)
{
    printf("== > worker is Adding anthor one ");
    pthread_t th ;
    int err = -1;
    if (wctls[i].opts.flags == WORKER_RUNNING)
        return 1 ;
    pthread_mutex_lock(&thread_init);
    wctls[i].opts.flags = WORKER_INITED ; //线程为已初始化
//    err = pthread_create(&th,NULL,worker,(void*)&wctls[i]); //建立线程
    pthread_mutex_lock(&thread_init);
    pthread_mutex_unlock(&thread_init);

    /*  更新线程选项 */
    wctls[i].opts.th = th;  // 线程ID
    workersnum ++ ;
    printf("< == worker Added anthor one ");
    return 0;

}
/*减少线程,将线程状态设为待删除*/
static void Worker_Delete(int i)
{
    printf("==>Worker_Delete\n");
    wctls[i].opts.flags = WORKER_DETACHING;/*线程状态改为正在卸载*/
    printf("<==Worker_Delete\n");
}

/* 销毁线程 */
static void Worker_Destory()
{
    printf("==> Worker Destory \n");
    int i = 0;
    int clean = 0 ;  //所有线程销毁符号
    for (i = 0; i< MaxClient;i++)
    {
        printf("thread %d,status %d \n",i,wctls[i].opts.flags);
        if(wctls[i].opts.flags != WORKER_DETACHED)
            Worker_Delete(i);
    }
    while(!clean){
        clean = 1;
        for (i = 0; i < MaxClient; i++){
            printf("thread %d,status %d \n",i,wctls[i].opts.flags);
            if (wctls[i].opts.flags == WORKER_RUNNING
                    || wctls[i].opts.flags == WORKER_DETACHING)
                clean = 0;
        }
        if (! clean) // 即clean不为1，等待
            sleep(1);  //等待1s,sleep令线程程暂停
    }
    printf("==> Worker Destory \n");
}

#define STATUS_RUNNING 1
#define STATSU_STOP 0
static int SCHEDULESTATUS = STATUS_RUNNING;

/* 初始化线程，侦听select要求， 查询线程和分配线程 */
int Worker_ScheduleRun(int ss)
{
    printf("==> Worker_ScheduleRun is working \n");
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    Worker_Init();
    int i = 0;
    for (;SCHEDULESTATUS ==STATUS_RUNNING;)
    {
        struct timeval tv ; //超时时间timeover
        fd_set rfds;       // 读文件集
        int retval = -1;

        /*读文件集，将客户端链接描述符放入读文件集*/
        FD_ZERO(&rfds);
        FD_SET(ss,&rfds);

        /*设置超时 0.5s */
        tv.tv_sec = 0;
        tv.tv_usec = 500000;

        /* 超时读数据，使用select */
        retval = select (ss +1, &rfds ,NULL, NULL, &tv);
        switch(retval)
        {
            case -1 :
                printf("select erro\n"); //错误
            case 0 :                         // 超时
                continue;
                break;
            default:
                /* 有可读套接字文件描述符 */
                if (FD_ISSET(ss, &rfds))
                {
                    int sc = accept(ss, (struct sockaddr*)&client,&len);
                    printf("client is comming\n");
                    i = WORKER_ISSTATUS(WORKER_IDEL); // 查询空闲线程
                    /* 对结果分析 */
                    if (i == -1)  // 没有找到空闲线程
                    {
                        i = WORKER_ISSTATUS(WORKER_DETACHED);
                        if (i != -1)
                            Worker_Add(i);
                    }
                    if (i != -1) // 发现空闲线程，添加任务
                    {
                        wctls[i].conn.cs = sc;  //套接字描述符
                        pthread_mutex_unlock(&wctls[i].opts.mutex); //告知有任务
                    }
                }
        }
    }
    printf("<== Worker_ScheduleRun has worked. \n");
    return 0;
}

/* 终止线程和分配线程任务 */
int Worker_ScheduleStop()
{
    printf(" ==> Worker_SchedulerStop \n");
    SCHEDULESTATUS = STATSU_STOP;  // 设置终止条件
    int i = 0 ;
    Worker_Destory();  // 销毁线程
    int allfired = 0 ; // 所有线程函数销毁标识符
     while (!allfired){
        for (i;i < MaxClient; i++) {
            allfired = 1 ;
            int flags = wctls[i].opts.flags;
            if (flags == WORKER_DETACHING || flags == WORKER_IDEL)
                /* 线程正在活动 */
                allfired = 0;
        }
    }
    pthread_mutex_destroy(&thread_init); // 摧毁互斥变量
    for (i=0; i < MaxClient;i++)
        pthread_mutex_destroy(&wctls[i].opts.mutex);
    free (wctls);
    printf(" <== Worker_SchedulerStop \n");
    return  0;
}