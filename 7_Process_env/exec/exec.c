#include<apue.h>
#include<apueerror.h>
#include<sys/wait.h>


char * env_init[] = {"USER=unknown","PATH=/tmp",NULL};

int main(void)
{
    pid_t pid;
    if((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if(pid == 0){   //指定路径，指定环境
        if(execle("/home/wkl/echoall","echoall","myagr1","MY ARG2",(char *)0,env_init) < 0)
            err_sys("execle error");
    }
    if(waitpid(pid,NULL,0) < 0 ){
        err_sys("wait error");
    }
    if((pid = fork()) < 0){
        err_sys("wait error");
    }
    else if(pid == 0){  //指定文件名，继承环境
        if(execlp("echoall","echoall","only 1 arg",(char *)0) < 0)
            err_sys("execlp error");
    }
    exit(0);
}