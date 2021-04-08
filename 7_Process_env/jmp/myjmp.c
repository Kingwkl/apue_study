#include<apue.h>
#include<apueerror.h>
#include<setjmp.h>


/*读命令、确定命令类型，调用响应函数处理每一条命令
*
*
*/


#define TOK_ADD 5


jmp_buf jmpbuffer;
int globval;

void do_line(char *);
void cmd_add(void);
int get_token(void);

int main(void)
{
    char line[MAXLINE];
    if(setjmp(jmpbuffer) != 0)
        printf("error!");
    while (fgets(line,MAXLINE,stdin) != NULL)
    {
        do_line(line);
    }
    exit(0);
}
char *tok_ptr;
void do_line(char *ptr)
{
    int cmd;
    tok_ptr = ptr;
    while((cmd = get_token()) > 0){
        switch (cmd)
        {
        case TOK_ADD:
            cmd_add();
            break;
        }
    }

}
void cmd_add(void)
{
    int token;
    token = get_token();
    if(token < 0){
        longjmp(jmpbuffer,1);
    }

}
int get_token(void)
{
    /* 从tok_ptr指向的行中获取下一个token */

}