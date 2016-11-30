#include <stdio.h>

void bubble_sort(int arr[], int len)
{
    int i, j;

/*    
    for (i = 0; i < len; ++i)
    {
        for (j = 0; j < len - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
*/

    for (i = len; i > 0; --i)
    {
        for (j = 1; j < i; ++j)
        {
            if (arr[j - 1] > arr[j])
            {
                int tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            }
        }
    }
}

int main()
{
    int i;
    int arr[] = { 9, 10, 2, 6, 4, 3, 8, 7, 7, 1, 2, 4 };
    int len = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, len);
    
    for (i = 0; i < len; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}




