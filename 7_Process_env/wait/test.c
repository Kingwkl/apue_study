#include<apue.h>
#include<apueerror.h>

static void charatatime(char*);

int main(void)
{
    pid_t pid;

    TELL_WAIT();

    if((pid = fork()) < 0 ){
        err_sys("fork error");
    }
    else if(pid = 0){
        charatatime("output from child\n");
        TELL_PARENT(getppid());
    }
    else{
        WAIT_CHILD();
        charatatime("output from parent\n");
    }
    exit(0);
}
static void charatatime(char * str)
{
    char * ptr;
    int c;
    setbuf(stdout,NULL);   //将标准输出设置为不带缓冲的
    
    for(ptr = str;(c = *ptr++) != 0;){
       putc(c,stdout);
    }
}