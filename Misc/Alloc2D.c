#include <malloc.h>

int** My2DAlloc(int rows, int cols)
{
    int header = rows * sizeof(int*);
    int data = rows * cols * sizeof(int);
    int** rowptr = (int**)malloc(header + data);
    int* buf = (int*)(rowptr + rows);
    
    int k;
    for (k = 0; k < rows; ++k)
    {
        rowptr[k] = buf + k*cols;
    }
    return rowptr;
}

void My2DFree(int **ptr)
{
    free(ptr);
}

int main()
{
    int** arr = My2DAlloc(5, 5);
    arr[3][3] = 1;
    printf("%d\n", arr[3][3]);
    My2DFree(arr);
    
    return 0;
}    
