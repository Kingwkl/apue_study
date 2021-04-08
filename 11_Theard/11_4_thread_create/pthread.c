/*
 * @Descripttion:  创建一个新线程，并打印进行id和线程id
 *  特别之处： 1、需要处理主线程和新线程之间的竞争，主线程需要休眠，
 *              如果主线程不休眠，它就可能退出，这样新线程还没机会运行，整个进程就已经终止
 *            2、新线程通过pthread_self函数获取自己的线程ID，
 *              而不是从共享内存中读出的，或从线程启动例程中以参数的形式接收到的。
 * 
 * @version: 
 * @Author: wkl
 * @Date: 2021-04-08 15:30:15
 * @LastEditors: wkl
 * @LastEditTime: 2021-04-08 15:55:31
 */
#include<apue.h>
#include<apueerror.h>
#include<pthread.h>

pthread_t ntid;


void printids(const char *s)       //打印进程id和线程id
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,(unsigned long)tid,(unsigned long)tid);
}

void * thr_fn(void * arg)     //线程函数
{
    printids("new thread : ");
    return ((void *)0);
}

int main(void)
{
    int err;
    err = pthread_create(&ntid,NULL,thr_fn,NULL);
    if(err != 0)
        err_exit(err,"can't create thread");
    printids("main thread: ");
    sleep(1);        //如果不睡眠，进程直接结束，新线程没有机会运行
    exit(0);
}