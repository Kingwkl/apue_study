/*
 * @Descripttion: 从信号处理程序my_alarm调用非可重入函数getpwnam，
 *                  而my_alarm每秒钟被调用一次
 * 总结： 在信号处理程序中调用一个非可重入函数，则其结果是不可预知的。
 * @version: 
 * @Author: wkl
 * @Date: 2021-04-08 10:40:18
 * @LastEditors: wkl
 * @LastEditTime: 2021-04-08 11:42:02
 */
#include<apue.h>
#include<apueerror.h>
#include<pwd.h>

static void my_alarm(int signo)
{
    struct passwd * rootptr;
    printf("in signal handler\n");
    if((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root) error");
    printf("rootptr -> pw_name = %s\n",rootptr->pw_name);
    alarm(1);
}

int main(void)
{
    struct passwd *ptr;
    signal(SIGALRM,my_alarm);
    alarm(1);
    for(;;){
        if((ptr = getpwnam("wkl")) == NULL)
            err_sys("getpwnam error");
        if(strcmp(ptr->pw_name,"wkl") != 0)
            printf("return value corrupted!,pw_name = %s\n",ptr->pw_name);
    }
}
