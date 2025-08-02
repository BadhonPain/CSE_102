#include <stdio.h>

int main()
{
    float mAB, mCD;
    int x1, y1, x2, y2, x3, y3, x4, y4;

    scanf("%d %d %d %d %d %d %d %d",&x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
    int isABVertical = (x2 - x1 == 0);
    int isCDVertical = (x4 - x3 == 0);

    if (isABVertical && isCDVertical)
    {

        if (x1 == x3)
            printf("Coincident\n");
        else
            printf("Parallel\n");
    }
    else if (isABVertical || isCDVertical)
    {

        printf("Intersecting\n");
    }
    else
    {

        mAB = (float)(y2 - y1) / (x2 - x1);
        mCD = (float)(y4 - y3) / (x4 - x3);

        if (mAB == mCD)
        {

            float mAtoC = (float)(y3 - y1) / (x3 - x1);
            if (mAtoC == mAB)
                printf("Coincident\n");
            else
                printf("Parallel\n");
        }
        else
        {
            printf("Intersecting\n");
        }
    }

    return 0;
}
