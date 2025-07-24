#include <stdio.h>
#include <stdlib.h>
int compare(char *p, char *q)
{
    while (*p != '.' && *q != '.' && *p == *q)
    {
        p++;
        q++;
    }
    if (*p == '.' && *q == '.')
        return 0;
    if (*p == '.')
        return -1;
    if (*q == '.')
        return 1;
    return (*p < *q) ? -1 : 1;
}
int main()
{
    int t;
    scanf("%d", &t);
    char **words = (char **)malloc(t * sizeof(char *));
    for (int i = 0; i < t; i++)
    {
        *(words + i) = (char *)malloc(26 * sizeof(char));
        scanf("%s", *(words + i));
    }
    for (int i = 0; i < t - 1; i++)
    {
        for (int j = 0; j < t - 1 - i; j++)
        {
            char *word1 = *(words + j);
            char *word2 = *(words + j + 1);
            if (compare(word1, word2) > 0)
            {
                char *temp = *(words + j);
                *(words + j) = *(words + j + 1);
                *(words + j + 1) = temp;
            }
        }
    }
    for (int i = 0; i < t; i++)
    {
        printf("%s\n", *(words + i));
    }
    for (int i = 0; i < t; i++)
    {
        free(*(words + i));
    }
    free(words);

    return 0;
}