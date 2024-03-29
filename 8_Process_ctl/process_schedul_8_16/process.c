#include<apue.h>
#include<apueerror.h>
#include<errno.h>
#include<sys/time.h>

unsigned long long count;
struct timeval end;
void checktime(char *str)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    if((tv.tv_sec >= end.tv_sec) && (tv.tv_usec >=end.tv_usec)){
        printf("%s count = %lld\n",str,count);
        exit(0);
    }
}
int main(int argc,char *argv[])
{
    pid_t pid;
    char *s;
    int nzero,ret;
    int adj = 0;
    setbuf(stdout,NULL);
#if defined(NZERO)
    nzero = NZERO;
#elif defined(_SC_NZERO)
    nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
    printf("NZERO = %d\n",nzero);
    printf("argc = %d\n",argc);
    if(argc == 2){
        adj = strtol(argv[1],NULL,10);
    }
    gettimeofday(&end,NULL);
    end.tv_sec +=10;

    if((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if(pid == 0){
        s = "child";
        printf("current nice value in child is %d,adjust by %d\n",
        nice(0)+nzero,adj);
        errno = 0;
        //如果nice调用成功，并且返回值为-1，那么errno仍然为0
        //如果errno不为0，说明nice调用失败
        if((ret = nice(adj)) == -1 && errno != 0){   
            err_sys("child set scheduling priority");
        }
        printf("now child nice value is %d\n",ret+nzero);
    }
    else{
        s = "parent";
        printf("current nice value in parent is %d\n",nice(0)+nzero);
    }
    for(;;){
        if(++count == 0){
            err_quit("%s counter wrap",s);
        }
        checktime(s);
    }

}