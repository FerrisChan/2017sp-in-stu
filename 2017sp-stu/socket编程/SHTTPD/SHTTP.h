//
// Created by ferris on 17-4-15.
//

#ifndef SHTTPD_SHTTP_H
#define SHTTPD_SHTTP_H
  #include <stdio.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <string.h>
  #include <signal.h>
  #define  K 1024


/*
 * 需要数据结构类型的声明
 *
*/

  //线程的状态值
  enum{WORKER_INITED, WORKER_RUNNING,
      WORKER_DETACHING, WORKER_DETACHED,WORKER_IDEL};
  /*
   * 管理线程的状态
   */
  struct worker_opts{
      pthread_t th;  //线程的ID号
      int flags;     // 线程的状态
      pthread_mutex_t mutex; //线程任务互斥
      struct worker_ctl *work;  // 本线程的总控结构
  };

  /*
   * 管理客户端请求的状态和值
   */
  struct workr_conn{
      char dreq[16*K];  // 请求缓冲区大小
      char dres[16*K];  //响应缓冲区大小
      int  cs;          // client  的socket描述符
      int  to;          //client 链接超时
      struct worker_ctl *work ;//本线程的总控结构
      //调用相应函数结构
//      struct conn_response con_res;
//      struct conn_request con_req;
 };

  struct worker_ctl {
     struct worker_opts opts;
     struct worker_conn conn;
 };



#endif //SHTTPD_SHTTP_H

