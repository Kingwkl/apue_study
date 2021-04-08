/*
 * @Descripttion: 
 * @version: 
 * @Author: wkl
 * @Date: 2021-04-08 17:14:06
 * @LastEditors: wkl
 * @LastEditTime: 2021-04-08 18:00:56
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
struct foo {
    int a,b,c,d;
};

void printfoo(const char *s,const struct foo *fp)
{
    printf("%s\n",s);
    printf("structure at 0x%lx\n",(unsigned long)fp);
    printf("foo.a = %d\n",fp->a);
    printf("foo.b = %d\n",fp->b);
    printf("foo.c = %d\n",fp->c);
    printf("foo.d = %d\n",fp->d);
}
void * thr_fn1(void * arg)
{
    struct foo fo = {1,2,3,4};
    printfoo("thread 1\n",&fo);
    pthread_exit((void *)&fo);
}

void * thr_fn2(void * arg)
{
    printf("thread 2: ID is %lu\n",(unsigned long)pthread_self());
    pthread_exit((void * )2);
}

int main(void)
{
    int err;
    pthread_t tid1,tid2;
    struct foo * fp;
    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err != 0)
        err_exit(err,"can't create thread 1");
    err = pthread_join(tid1,(void*)&fp);
    if(err != 0){
        err_exit(err,"can't join with thread 1");
    }
    sleep(5);

    printf("\nparent starting second thread\n");
    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err != 0){
        err_exit(err,"can't create thread 2");
    }
    sleep(2);
    
    printfoo("parent:\n",fp);
    exit(0);

}