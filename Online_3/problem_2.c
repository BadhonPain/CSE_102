#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int first = -1, second = -1, third = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > first)
        {
            first = arr[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < first && arr[i] > second)
        {
            second = arr[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < second && arr[i] > third)
        {
            third = arr[i];
        }
    }

    if (third == -1)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", third);
    }

    return 0;
}
