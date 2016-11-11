#include <stdio.h>
#include <stdlib.h>

void* aligned_malloc(size_t required_bytes, size_t alignment)
{
    if (alignment <= 0)
    {
        printf("invalid alignment\n");
        return NULL;
    }

    void* p1; // original block
    void** p2; // aligned block
    int offset = alignment - 1 + sizeof(void*);
    
    if ((p1 = (void*)malloc(required_bytes + offset)) == NULL)
    {
        return NULL;
    }
    p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void aligned_free(void *p)
{
    free(((void**)p)[-1]);
}

int main()
{
    void* res = aligned_malloc(1000, 256);
    printf("Allocated Addr: %lx\n", (long)res);
    aligned_free(res);
    return 0;
}
