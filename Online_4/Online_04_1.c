// with single pointer
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n, q;
    scanf("%d %d %d", &m, &n, &q);

    int *A = (int *)malloc(m * n * sizeof(int));
    int *B = (int *)malloc(n * q * sizeof(int));
    int *C = (int *)malloc(m * q * sizeof(int));
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", (A + i * n + j));
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < q; j++)
        {
            scanf("%d", (B + i * q + j));
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            *(C + i * q + j) = 0;
            for (int k = 0; k < n; k++)
            {
                *(C + i * q + j) +=
                    (*(A + i * n + k)) * (*(B + k * q + j));
            }
        }
    }

    printf("%d %d\n", m, q);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            printf("%d ", *(C + i * q + j));
        }
        printf("\n");
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
