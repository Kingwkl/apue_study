#include<apue.h>
#include<sys/wait.h>
#include<apueerror.h>
#include<errno.h>
#include<unistd.h>

int system(const char * cmdstring)
{
    pid_t pid;
    int status;
    if(cmdstring == NULL){
        return 1;
    }
    if((pid = fork()) < 0){
        status = -1;
    }
    else if(pid == 0){
        execl("/bin/bash","sh","-c",cmdstring,(char *)0);
        _exit(127);
    }
    else{
        while(waitpid(pid,&status,0) < 0){
            if(errno != EINTR){
                status = -1;
                break;
            }
        }
    }
    return status;
}

int main(void)
{
    int status;
    if((status = system("date")) < 0){
        err_sys("system() error");
    }
    pr_exit(status);
    
    if((status = system("nosuchcommand")) < 0){
        err_sys("system() error");
    }
    pr_exit(status);

    if((status = system("who;exit 44")) < 0){
        err_sys("system() error");
    }
    pr_exit(status);
    exit(0);
}