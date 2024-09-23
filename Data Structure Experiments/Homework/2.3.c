#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef int STDataType;

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

const int MAX_SIZE = 1010;

int isStack(int *a, int *b, int n)
{
    struct Stack st;
    STInit(&st);
    int i = 0, j = 0;
    for (i = 0; i < n;)
    {
        if (STEmpty(&st) || STTop(&st) != b[j])
        {
            STPush(&st, a[i]);
            i++;
        }
        else
        {
            while (!STEmpty(&st))
            {
                if (b[j] != STTop(&st))
                    return 0;
                STPop(&st);
                j++;
            }
        }
    }
    if (STTop(&st) == b[j])
    {
        while (!STEmpty(&st))
        {
            if (b[j] != STTop(&st))
                return 0;
            STPop(&st);
            j++;
        }
    }
    if (STEmpty(&st))
        return n;
    else
        return 0;
}
int main()
{
    int n;
    int a[MAX_SIZE], b[MAX_SIZE];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &b[i]);
    }
    printf("%d\n", isStack(a, b, n));
    return 0;
}