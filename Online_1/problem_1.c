#include <stdio.h>

int main()
{
    int n, sum = 0;
    scanf("%d", &n);
    int temp = n;
    while (n > 0)
    {
        int a = n % 10;
        sum += (a * a * a);
        n /= 10;
    }
    if (sum == temp)
    {
        printf("Armstrong number\n");
    }
    else
    {
        printf("Not an Armstrong number\n");
    }

    return 0;
}