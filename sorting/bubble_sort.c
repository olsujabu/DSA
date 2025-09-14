// author : Buyandelger.J
// date : 14/09/2025 22:30
// title :  Bubble sort using malloc

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int n, int *arr)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print_arr(int n, int *arr)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    clock_t t;
    t = clock();
    int *arr, n;
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Nothing is here");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    bubble_sort(n, arr);
    print_arr(n, arr);
    double taken_time = ((double)t) / CLOCKS_PER_SEC;
    printf("took %f seconds to execute\n", taken_time);
    return 0;
}