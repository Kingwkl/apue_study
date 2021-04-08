#include<apue.h>

int main(int argc,char * argv[])
{
    int var_i;
    char **ptr;
    extern char **environ;
    for(var_i = 0;var_i < argc;var_i++){
        printf("agrv[%d]: %s\n",var_i,argv[var_i]);
    }
    for(ptr = environ;*ptr != 0;ptr++){
        printf("%s\n",*ptr);
    }
    exit(0);
}