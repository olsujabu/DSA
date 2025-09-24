/*
author : Buyandelger.J
date : 24/09/2025 20:27
title : Selection Sort
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void selection_sort(int n, int *arr)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[min] > arr[j])
            {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void print_array(int n, int *arr)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

int main()
{
    clock_t t;
    t = clock();
    int n, *arr;
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
    selection_sort(n, arr);
    print_array(n, arr);
    printf("\n");
    double taken_time = ((double)t) / CLOCKS_PER_SEC;
    printf("took %f seconds to execute\n", taken_time);
    return 0;
}