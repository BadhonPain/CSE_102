#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.c"

#define MAX_SIZE 100000
#define MAX_BINS 1000
#define MAX_STARS 50

void COMMANDS()
{
    printf("Commands:\n");
    printf("\tset\t-Set array size, seed, and distribution (uniform or gaussian)\n");
    printf("\tmin\t-Print minimum value\n ");
    printf("\tmax\t-Print maximum value\n ");
    printf("\tmean\t-Print mean value\n ");
    printf("\tstddev\t-Print standard deviation\n ");
    printf("\thist\t-Plot histogram\n ");
    printf("\tsummary\t-Print min, max, mean, stddev\n ");
    printf("\thelp\t-Show this help message\n ");
    printf("\texit\t-Exit the program\n ");
    return;
}

double MIN(double array[], int size)
{
    double min = array[0];
    for (int i = 1; i < size; i++)
    {
        min = (array[i] < min) ? array[i] : min;
    }
    return min;
}

double MAX(double array[], int size)
{
    double max = array[0];
    for (int i = 1; i < size; i++)
    {
        max = (array[i] > max) ? array[i] : max;
    }
    return max;
}

double MEAN(double array[], int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }
    double mean = sum / size;
    return mean;
}

double STDDEV(double array[], int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }
    double mean = sum / size;
    double sqr_sum = 0;
    for (int i = 0; i < size; i++)
    {
        sqr_sum += (array[i] - mean) * (array[i] - mean);
    }
    double stddev = sqrt(sqr_sum / size);
    return stddev;
}

int COMPARE(const void *a, const void *b)
{
    double da = *(const double *)a;
    double db = *(const double *)b;

    return (da < db) ? -1 : ((da > db) ? 1 : 0);
}

int main()
{
    COMMANDS();

    double array[MAX_SIZE];
    int size = 0, bins = 0;
    int populated_array = 0;

    char command[10];
    unsigned int seed;
    char distribution[20];

    while (1)
    {
        printf("Enter command: ");
        scanf("%s", command);

        if (strcmp(command, "set") == 0)
        {
            printf("Enter the number of elements (<= %d): ", MAX_SIZE);
            scanf("%d", &size);

            if (size <= 0 || size > MAX_SIZE)
            {
                printf("Invalid number of elements. It must be between 1 and %d.\n", MAX_SIZE);
                continue;
            }

            printf("Enter seed: ");
            scanf("%u", &seed);

            printf("Distribution? (uniform/gaussian): ");
            scanf("%s", distribution);

            if (strcmp(distribution, "uniform") == 0)
            {
                double min, max;
                printf("Enter min and max: ");
                scanf("%lf %lf", &min, &max);
                populate_array_uniform(array, size, min, max, seed);
                printf("Array initialized with uniform distribution.\n");
                populated_array = 1;
            }
            else if (strcmp(distribution, "gaussian") == 0)
            {
                double mean, stddev;
                printf("Enter mean and stddev: ");
                scanf("%lf %lf", &mean, &stddev);
                populate_array_gaussian(array, size, mean, stddev, seed);
                printf("Array initialized with gaussian distribution.\n");
                populated_array = 1;
            }
            else
            {
                printf("Invalid distribution.\n");
            }
        }
        else if (strcmp(command, "min") == 0)
        {
            if (populated_array)
            {

                printf("Min\t:\t%.4lf\n", MIN(array, size));
            }
            else
                printf("Array not initialized. Use 'set' command first.\n");
        }
        else if (strcmp(command, "max") == 0)
        {
            if (populated_array)
            {

                printf("Max\t:\t%.4lf\n", MAX(array, size));
            }

            else
                printf("Array not initialized. Use 'set' command first.\n");
        }
        else if (strcmp(command, "mean") == 0)
        {
            if (populated_array)
            {
                printf("Mean\t:\t%.4lf\n", MEAN(array, size));
            }

            else
                printf("Array not initialized. Use 'set' command first.\n");
        }

        else if (strcmp(command, "stddev") == 0)
        {
            if (populated_array)
            {
                printf("Std dev\t:\t%.4lf\n", STDDEV(array, size));
            }

            else
                printf("Array not initialized. Use 'set' command first.\n");
        }
        else if (strcmp(command, "summary") == 0)
        {
            if (populated_array)
            {

                double sum = 0, sqr_sum = 0, mean, stddev;
                double min = array[0], max = array[0];

                for (int i = 0; i < size; i++)
                {
                    if (array[i] < min)
                        min = array[i];
                    if (array[i] > max)
                        max = array[i];
                    sum += array[i];
                }

                mean = sum / size;

                for (int i = 0; i < size; i++)
                    sqr_sum += (array[i] - mean) * (array[i] - mean);

                stddev = sqrt(sqr_sum / size);

                printf("Min     :\t%.4lf\n", min);
                printf("Max     :\t%.4lf\n", max);
                printf("Mean    :\t%.4lf\n", mean);
                printf("Std Dev :\t%.4lf\n", stddev);
            }

            else
                printf("Array not initialized. Use 'set' command first.\n");
        }
        else if (strcmp(command, "hist") == 0)
        {
            if (populated_array)
            {

                printf("Enter number of bins: ");
                scanf("%d", &bins);

                if (bins <= 0 || bins > MAX_BINS)
                {
                    printf("Invalid number of bins. It must be between 1 and %d.\n", MAX_BINS);
                    continue;
                }

                double min = array[0], max = array[0];
                for (int i = 1; i < size; i++)
                {
                    if (array[i] < min)
                        min = array[i];
                    if (array[i] > max)
                        max = array[i];
                }

                double bin_width = (max - min) / bins;
                int bin_count[MAX_BINS] = {0};

                for (int i = 0; i < size; i++)
                {
                    int bin_idx = (int)((array[i] - min) / bin_width);
                    if (bin_idx == bins)
                        bin_idx--;
                    bin_count[bin_idx]++;
                }

                int maxcount = 0;
                for (int i = 0; i < bins; i++)
                    if (bin_count[i] > maxcount)
                        maxcount = bin_count[i];

                for (int i = 0; i < bins; i++)
                {
                    double lower = min + i * bin_width;
                    double upper = lower + bin_width;
                    printf("[%7.2f - %7.2f]: ", lower, upper);

                    int stars = (maxcount > 0) ? (bin_count[i] * MAX_STARS) / maxcount : 0;
                    for (int j = 0; j < stars; j++)
                        printf("*");
                    printf("\n");
                }
            }

            else
                printf("Array not initialized. Use 'set' command first.\n");
        }
        else if (strcmp(command, "median") == 0)
        {
            if (populated_array)
            {

                qsort(array, size, sizeof(double), COMPARE);
                double median;
                if (size % 2 != 0)
                    median = array[size / 2];
                else
                    median = (array[size / 2] + array[(size / 2) - 1]) / 2;

                printf("Median\t:\t%.4lf\n", median);
            }

            else
                printf("Array not initialized. Use 'set' command first.\n ");
        }
        else if (strcmp(command, "help") == 0)
        {

            COMMANDS();
        }
        else if (strcmp(command, "exit") == 0)

        {
            break;
        }

        else
        {
            printf("Unknown command. Type 'help' for list of commands.\n ");
        }
    }

    return 0;
}