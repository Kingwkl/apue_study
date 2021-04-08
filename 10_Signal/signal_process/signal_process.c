/*
 * @Descripttion:  简单的信号处理程序，捕捉两个用户自定义的信息，并打印信号的编号
 * @version: 
 * @Author: wkl
 * @Date: 2021-04-08 09:40:07
 * @LastEditors: wkl
 * @LastEditTime: 2021-04-08 10:31:14
 */
#include<apue.h>
#include<apueerror.h>

static void sig_usr(int);

/*
* SIGUSR1 和 SIGUSR2 一样，都是用户定义的信号，可用于应用程序 
*/

int main(void)
{
    if(signal(SIGUSR1,sig_usr) == SIG_ERR){
        err_sys("can't catch SIGUSR1");
    }
    if(signal(SIGUSR2,sig_usr) == SIG_ERR){
        err_sys("can't catch SIGUSR2");
    }
    for(;;)
        pause();                         //使得进程在收到信号前挂起    
}

/**
 * @name: 
 * @msg:  信号处理函数
 * @param {int} signo 信号名
 * @return {*} void
 */
static void sig_usr(int signo)
{
    if(signo == SIGUSR1){
        printf("received SIGUSR1\n");
    }
    else if(signo == SIGUSR2){
        printf("received SIGUSR2\n");
    }
    else{
        err_dump("received signal %d\n",signo);
    }
}