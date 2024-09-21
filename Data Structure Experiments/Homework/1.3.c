#include <stdio.h>

int main()
{
    int temp, size1 = 0, size2 = 0;
    int odd[1010], even[1010];
    while (scanf("%d", &temp) != EOF)
    {
        if (temp != 0)
        {
            if (temp % 2 == 0)
            {
                even[size2++] = temp;
            }
            else
            {
                odd[size1++] = temp;
            }
        }
        if (getchar() != ',')
            break;
    }
    if (size1 > 0)
    {
        for (int i = 0; i < size1-1; i++)
        {
            printf("%d,", odd[i]);
        }
    }
    if (size2 > 0)
    {
        if(size1>0)
            printf("%d,", odd[size1-1]);
        for (int i = 0; i < size2 - 1; i++)
        {
            printf("%d,", even[i]);
        }
        printf("%d", even[size2 - 1]);
    }
    else
    {
        printf("%d", odd[size1-1]);
    }
    return 0;
}