#include<apue.h>
#include<apueerror.h>
int main(void)
{
    printf("uid = %d,euid = %d\n",getuid(),geteuid());
    printf("gid = %d,geuid = %d\n",getgid(),getegid());
    pid_t pid;
    if((pid = fork()) < 0){
        err_sys("fork failed");
    }
    else if(pid == 0){
        printf("child process!\n");
        printf("groupid = %d,getpgid = %d,pid = %d\n",getpgrp(),getpgid(getpid()),getpid());
    }
    else{
        printf("parent process!\n");
        printf("groupid = %d,getpgid = %d,pid = %d\n",getpgrp(),getpgid(getpid()),getpid());
    }


    
    return 0;
}