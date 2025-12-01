// author : Buyandelger.J
// date : 02/12/2025 00:26
// title :  Radix sort
// Radix эрэмбэлэх нь integer эсвэл string зэрэг тогтмол хэмжээтэй массивтай үед сайн ажилладаг.

/*
Time Complexity :
    Integers (k digits) → O(k * n)
    Fixed string (L length) → O(L * n)
    k ба L хоёулаа тогтмол бол
    шууд O(n) болж хувирдаг.

Радикс эрэмбэлэлт нь:
    1-ийн орон
    10-ийн орон
    100-гийн орон … гэх мэтээр үе шаттай эрэмбэлдэг.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

// Массив дахь хамгийн их утгыг олно
// Энэ нь хэдэн оронтойг тодорхойлоход хэрэгтэй
int get_Max(int *arr, int n)
{
    int max = arr[0];
    for (int i = 1; n > i; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

void counting_Sort(int *arr, int exp, int n)
{
    // Түр хадгалах массив
    // Тухайн үеийн эрэмбэлэлтийг шууд arr дээр хийх юм бол
    // өмнөх утгуудыг дээрээс нь дарж бичээд утга нь алдагдана.
    // Тийм учраас үүсгэсэн массивдаа хуулж өгнө.
    int *output = (int *)malloc(n * sizeof(int));

    // 0–9 хүртэл цифрийн давтамжийг хадгална
    // 9 хүртэлх бүх цифрийн: хэд гарав, ямар дарааллаар байрлуулах вэ гэдгийг тодорхойлно.
    int count[10] = {0};

    // Одоогийн цифрийн утгаар давтамж тоолох
    for (int i = 0; n > i; i++)
    {
        int index = (arr[i] / exp) % 10;
        count[index]++;
    }

    // Давтамжийг хуримтлагдсан хэлбэрт оруулах
    // Энэ нь байрлалыг зөв тодорхойлох
    for (int i = 1; 10 > i; i++)
    {
        count[i] += count[i - 1];
    }

    // Анхны массиваас баруун талаас эхлэн утгуудыг зөв байрлалд байрлуулах
    for (int i = n - 1; i >= 0; i--)
    {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // Буцааж хуулна
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
    free(output);
}

void radix_sort(int n, int *arr)
{
    int max_value = get_Max(arr, n);
    int exp = 1;
    while (max_value / exp > 0)
    {
        counting_Sort(arr, exp, n);
        exp *= 10;
    }
}

void print_arr(int n, int *arr)
{
    for (int i = 0; n > i; i++)
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
    for (int i = 0; n > i; i++)
    {
        scanf("%d", &arr[i]);
    }
    radix_sort(n, arr);
    print_arr(n, arr);
    double taken_time = ((double)t) / CLOCKS_PER_SEC;
    printf("took %f seconds to execute\n", taken_time);
    return 0;
}