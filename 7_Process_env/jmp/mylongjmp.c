#include<apue.h>
#include<apueerror.h>
#include<setjmp.h>


/*读命令、确定命令类型，调用响应函数处理每一条命令
*
*
*/

static void func1(int,int,int,int);
static void func2(void);

#define TOK_ADD 5


static jmp_buf jmpbuffer;
static int globval;

void do_line(char *);
void cmd_add(void);
int get_token(void);

int main(void)
{
    int autoval;
    register int regival;
    volatile int volaval;
    static int statval;
    globval = 1;
    autoval = 2;
    regival = 3;
    volaval = 4;
    statval = 5;
    if(setjmp(jmpbuffer) != 0){
        printf("after longjmp: \n");
        printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",globval,autoval,regival,volaval,statval);     
        exit(0);
    }
//改变值
    globval = 95;
    autoval = 96;
    regival = 97;
    volaval = 98;
    statval = 99;
    func1(autoval,regival,volaval,statval);
    exit(0);
}
static void func1(int num1,int num2,int num3,int num4)
{
    printf("in func1(): \n");
    printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",globval,num1,num2,num3,num4);     
    func2();
}
static void func2(void)
{
    longjmp(jmpbuffer,1);
}

