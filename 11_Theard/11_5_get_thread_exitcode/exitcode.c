/*
 * @Descripttion: 
 *      子线程调用了pthread_join()方法后面的代码，只有等到子线程结束了才能执行。
 *      当调用 pthread_join() 时，当前线程会处于阻塞状态，直到被调用的线程结束后，当前线程才会重新开始执行
 * @version: 
 * @Author: wkl
 * @Date: 2021-04-08 16:06:38
 * @LastEditors: wkl
 * @LastEditTime: 2021-04-08 17:06:03
 */
#include<apue.h>
#include<apueerror.h>
#include<pthread.h>

void printids(const char *s)       //打印进程id和线程id
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,(unsigned long)tid,(unsigned long)tid);
}


void * thr_fn1(void * arg)
{
    printf("thread 1 returning\n");
    printids("thread 1: ");
    return((void * )1);
}

void * thr_fn2(void * arg)
{
    printf("thread 2 exiting\n");
    printids("thread 2: ");
    pthread_exit((void * )2);
}

int main(void)
{
    int err;
    pthread_t tid1,tid2;
    void * tret;
    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err != 0)
        err_exit(err,"can't create thread 1");
    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err != 0){
        err_exit(err,"can't create thread 2");
    }
    printids("main thread: ");
    err = pthread_join(tid1,&tret);
    if(err != 0){
        err_exit(err,"can't join with thread 1");
    }
    printf("thread 1 exit code = %ld\n",(long)tret);
    err = pthread_join(tid2,&tret);
    if(err != 0){
        err_exit(err,"can't join with thread 2");
    }
    printf("thread 2 exit code = %ld\n",(long)tret);
    exit(0);

}