#include <stdio.h>
#include <string.h>

int isPalindrome(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - 1 - i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char s[1001];
    int n;

    scanf("%s", s);
    scanf("%d", &n);

    int len = strlen(s);
    int found = 0;

    for (int i = 0; i <= len - n; i++)
    {
        char sub[1001];
        int k = 0;

        for (int j = i; j < i + n; j++)
        {
            sub[k++] = s[j];
        }
        sub[k] = '\0';

        if (isPalindrome(sub))
        {
            printf("%s\n", sub);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No Palindrome Substring");
    }

    return 0;
}
