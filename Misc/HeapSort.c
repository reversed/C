#include <stdio.h>

int left(int i)
{
    return i*2 + 1;
}

int right(int i)
{
    return i*2 + 2;
}

void swap(int a[], int i, int largest)
{
    int temp = a[i];
    a[i] = a[largest];
    a[largest] = temp;
}

void maxHeapify(int a[], int i, int length)
{
    if (i < 0 || length <= 0) return;

    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < length && a[l] > a[i])
    {
        largest = l;
    }
    if (r < length && a[r] > a[largest])
    {
        largest = r;
    }
    if (i != largest)
    {
        swap(a, i, largest);
        maxHeapify(a, largest, length);
    }
}

void buildMaxHeap(int a[], int size)
{
    int i;
    for (i = size / 2; i >= 0; --i)
    {
        maxHeapify(a, i, size);
    }
}

void sort(int a[], int size)
{
    int i;
    if (size <= 1) return;

    buildMaxHeap(a, size);

    for (i = size - 1; i > 0; --i)
    {
        swap(a, i, 0);
        maxHeapify(a, 0, i);
    }
}

int main()
{
    int i;
    int a[10] = { 10, 2, 30, 4, 5, 13, 11, 91, 23, 87 };
    //int a[1] = {0};
    int len = sizeof(a) / sizeof(a[0]);
    
    sort(a, len);
    for (i = 0; i < len; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;  
}
