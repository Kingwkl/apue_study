/*
* 安全漏洞（现在已经正常）
* 给予tsys程序的超级用户权限在 system中执行了fork和exec之后仍被保持了下来
*/



#include<apue.h>
#include<apueerror.h>

int main(int argc,char*argv[])
{
    int status;
    if(argc < 2){
        err_quit("command-line argument required");
    }
    if((status = system(argv[1])) < 0){
        err_sys("system() error");
    }
    pr_exit(status);
    exit(0);
}