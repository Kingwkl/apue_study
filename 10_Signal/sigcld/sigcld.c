/*
 * @Descripttion: 不能正常工作的System V SIGCLD处理程序
 * @version: 
 * @Author: wkl
 * @Date: 2021-04-08 13:59:25
 * @LastEditors: wkl
 * @LastEditTime: 2021-04-08 14:27:13
 */
#include<apue.h>
#include<apueerror.h>
#include<sys/wait.h>

static void sig_cld(int);

int main()
{
    pid_t pid;
    if(signal(SIGCLD,sig_cld) == SIG_ERR)
        perror("signal error");
    if((pid = fork()) < 0){
        perror("fork error");
    }
    else if(pid == 0){   //子进程
        sleep(2);
        _exit(0);
    }
    pause();      //父进程挂起
    exit(0);
}

static void sig_cld(int signo)
{
    pid_t pid;
    int status;
    printf("SIGCLD received\n");
    if(signal(SIGCLD,sig_cld) == SIG_ERR)
        perror("signal error");
    if((pid = wait(&status)) < 0)
        perror("wait error");
    printf("pid = %d\n",pid);
}