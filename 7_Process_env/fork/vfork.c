#include<apue.h>
#include<apueerror.h>

int glob = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
	int var;
	pid_t pid;
	var = 88;
	if(write(STDOUT_FILENO,buf,sizeof(buf)-1) != sizeof(buf)-1){
		err_sys("write error");
	}
	printf("before vfork\n");

	if((pid = vfork()) < 0 ){
		err_sys("fork error");
	}
	else if(pid == 0){   //子进程
		glob++;
		var++;
        _exit(0);    //子进程退出
	}
	printf("pid = %d, glob = %d, var = %d\n",getpid(),glob,var);
	exit(0);
	
}
