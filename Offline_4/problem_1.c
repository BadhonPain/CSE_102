#include <stdio.h>
#include <stdlib.h>
void removeNegatives(int *input, int n, int **output, int *newSize)
{
    int count = n;
    for (int i = 0; i < n; i++)
    {
        if (*(input + i) < 0)
            count--;
    }
    *output = (int *)malloc(count * sizeof(int));
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (*(input + i) >= 0)
        {
            *(*output + k) = *(input + i);
            k++;
        }
    }
    *newSize = count;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *input = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", (input + i));
    }
    int *output;
    int newSize = 0;
    removeNegatives(input, n, &output, &newSize);
    printf("%d\n", newSize);
    for (int i = 0; i < newSize; i++)
    {
        printf("%d ", *(output + i));
    }
    free(input);
    free(output);

    return 0;
}