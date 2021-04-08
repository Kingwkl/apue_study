#include<apue.h>
#include<sys/resource.h>
int main(void)
{
    pid_t pid;
    if((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if(pid == 0){
        printf("real uid = %d,effective uid = %d,loginid = %s\n",getuid(),geteuid(),getlogin());
        printf("*********************\n");
        printf("nice = %d\n",getpriority(PRIO_PROCESS,0));
    }
    exit(0);
}