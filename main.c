#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random(double lower_range_limit, double upper_range_limit)
{
    double result = lower_range_limit + (rand() * 1. / RAND_MAX) * (upper_range_limit - lower_range_limit);
    return result;
}

int main()
{
    srand(time(0));
    int n;
    printf("Enter count of numbers in binary file (n)\n");
    scanf("%d", &n);
    double high_r, low_r;
    printf("Enter range of random(low high)\n");
    scanf("%lf %lf", &low_r, &high_r);

    int rows, cols;

    if ((rows * cols) > n)
    {
        printf("ERROR: file is too small");
        return 1;
    }

    printf("Enter sizes of array (rows cols)\n");
    scanf("%d %d", &rows, &cols);
    double** array = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++)
    {
        array[i] = (double*)malloc(cols * sizeof(double));
    }

    FILE *output = fopen("RealNumber.bin", "wb");;
    for (int i = 0; i < n; i++)
    {
        double num;
        num = random(low_r, high_r);
        //printf("\n%lf", num);
        fwrite(&num, sizeof(double), 1, output);
    }
    fclose(output);

    FILE *input = fopen("RealNumber.bin", "rb");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double tmp;
            fread(&tmp, sizeof(double), 1, output);
            array[i][j] = tmp;
        }
    }

    printf("\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%lf ", array[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++)
    {
        free(array[i]);
    }
    free(array);

    fclose(input);
    return 0;
}
