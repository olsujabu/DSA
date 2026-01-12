// author : Buyandelger.J
// title :  Merge Sort
#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right)
{
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int L[n1], R[n2];
  for (int i = 0; i < n1; i++)
  {
    L[i] = arr[left + i];
  }
  for (int j = 0; j < n2; j++)
  {
    R[j] = arr[mid + 1 + j];
  }
  i = 0, j = 0, k = left;
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1)
  {
    arr[k++] = L[i++];
  }
  while ((j < n2))
  {
    arr[k++] = R[j++];
  }
}

void merge_sort(int arr[], int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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
  merge_sort(arr, 0, n - 1);
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  free(arr);
  return 0;
}