#include<apue.h>
#include<apueerror.h>
#include<sys/wait.h>

int main(void)
{
    pid_t pid;
    printf("main function pid = %ld\n",(long)getpid());
    if((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if(pid == 0){
        printf("first child,parent pid = %ld,first child's pid = %ld\n",(long)getppid(),(long)getpid());
        if((pid = fork()) < 0){
            err_sys("fork error");
        }
        else if(pid > 0){
            exit(0);
        }
        printf("second child,parent pid = %ld\n",(long)getppid());
        sleep(2);
        printf("sleeped second child,parent pid = %ld\n",(long)getppid());
        exit(0);
    }
    if(waitpid(pid,NULL,0) != pid){
        err_sys("waitpid error");
    }
    else{
        printf("sdfsd");
    }
    exit(0);
}