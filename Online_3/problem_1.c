#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int getsun[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &getsun[i]);
    }
    int keep = getsun[0];
    for (int j = 0; j < n; j++)
    {
        if (getsun[j] > keep)
        {
            keep += (getsun[j] - keep);
            keep = getsun[j];
        }
    }
    printf("%d", keep);

    return 0;
}