// author : Buyandelger.J
// title : Quick Sort
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int arr[], int low, int high)
{
  int pivot = arr[low];
  int i = low + 1;
  int j = high;
  while (1)
  {
    while (i <= high && arr[i] <= pivot)
      i++;
    while (arr[j] > pivot)
      j--;
    if (i >= j)
      break;
    swap(&arr[i], &arr[j]);
  }
  swap(&arr[low], &arr[j]);
  return j;
}

void quickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int p = partition(arr, low, high);
    quickSort(arr, low, p - 1);
    quickSort(arr, p + 1, high);
  }
}

int main()
{
  int n;
  scanf("%d", &n);
  int *arr = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  quickSort(arr, 0, n - 1);
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  free(arr);
  return 0;
}