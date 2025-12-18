// with double pointer
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n, q;
    scanf("%d %d %d", &m, &n, &q);

    int **A = (int **)malloc(m * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(m * sizeof(int *));

    for (int i = 0; i < m; i++)
    {
        *(A + i) = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        *(B + i) = (int *)malloc(q * sizeof(int));
    }

    for (int i = 0; i < m; i++)
    {
        *(C + i) = (int *)malloc(q * sizeof(int));
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", (*(A + i) + j));
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < q; j++)
        {
            scanf("%d", (*(B + i) + j));
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            *(*(C + i) + j) = 0;
            for (int k = 0; k < n; k++)
            {
                *(*(C + i) + j) +=
                    (*(*(A + i) + k)) * (*(*(B + k) + j));
            }
        }
    }

    printf("%d %d\n", m, q);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            printf("%d ", *(*(C + i) + j));
        }
        printf("\n");
    }

    for (int i = 0; i < m; i++)
    {
        free(*(A + i));
        free(*(C + i));
    }

    for (int i = 0; i < n; i++)
    {
        free(*(B + i));
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
