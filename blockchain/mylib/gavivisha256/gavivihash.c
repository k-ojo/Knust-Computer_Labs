#include "gavivisha256.h"

int main(int ac, char *av[])
{
    if (ac != 2)
        exit(99);
    uint32_t digest[256 / 8];

    gavivisha256(av[1], digest);
    printf("Hash Value:\t");
    for (int i = 0; i < 8; i++)
        printf("%x", digest[i]);

    printf("\n");

    return (0);
}