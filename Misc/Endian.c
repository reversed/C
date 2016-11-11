#include <stdio.h>

#define BIG_ENDIAN 0
#define LITTLE_ENDIAN 1

int main()
{
    short int word = 0x0001;
    char *byte = (char*)&word;
    if (byte[0] == 0x01)
    {
        printf("Little Endian\n");
    }
    else
    {
        printf("Big Endian\n");
    }

    return 0;
} 
