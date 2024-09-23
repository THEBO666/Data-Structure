#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef char STDataType;

typedef struct Stack
{
    STDataType *a;
    int top;
    int capacity;
} ST;

void STInit(ST *ps)
{
    assert(ps);

    ps->a = (STDataType *)malloc(sizeof(STDataType) * 4);
    if (ps->a == NULL)
    {
        perror("malloc fail");
        return;
    }

    ps->capacity = 4;
    ps->top = 0; // top是栈顶元素的下一个位置

    // ps->top = -1;   // top是栈顶元素位置
}

void STDestroy(ST *ps)
{
    assert(ps);

    free(ps->a);
    ps->a = NULL;
    ps->top = 0;
    ps->capacity = 0;
}

void STPush(ST *ps, STDataType x)
{
    assert(ps);

    if (ps->top == ps->capacity)
    {
        STDataType *tmp = (STDataType *)realloc(ps->a,
                                                sizeof(STDataType) * ps->capacity * 2);
        if (tmp == NULL)
        {
            perror("realloc fail");
            return;
        }

        ps->a = tmp;
        ps->capacity *= 2;
    }

    ps->a[ps->top] = x;
    ps->top++;
}

bool STEmpty(ST *ps)
{
    assert(ps);

    return ps->top == 0;
}
void STPop(ST *ps)
{
    assert(ps);
    assert(!STEmpty(ps));

    ps->top--;
}

int STSize(ST *ps)
{
    assert(ps);

    return ps->top;
}

STDataType STTop(ST *ps)
{
    assert(ps);
    assert(!STEmpty(ps));

    return ps->a[ps->top - 1];
}

void isMatch(char *str, int n)
{
    struct Stack st;
    STInit(&st);
    for (int i = 0; i <n;i++)
    {
        if(str[i]=='('||str[i]=='{'||str[i]=='[')
        {
            STPush(&st,str[i]);
        }
        else if(str[i]==')'||str[i]=='}'||str[i]==']')
        {
            if((str[i]==')'&&STTop(&st)!='(')
            ||(str[i]==']'&&STTop(&st)!='[')
            ||str[i]=='}'&&STTop(&st)!='{'
            ||STEmpty(&st))
            {
                printf("N%d\n",i);
                return ;
            }
            else
            {
                STPop(&st);
            }
        }
    }
    if(STEmpty(&st))
        printf("Y\n");
    else
        printf("N%d\n",n);
}
int main()
{

    char str[128];
    scanf("%s", str);
    isMatch(str, strlen(str));
    return 0;
}