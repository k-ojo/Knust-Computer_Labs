#include "gavivisha256.h"



int main()
{

    /**
     * size_t len;
    uint8_t *buf = pad("abcertyutoyzdxfghfytriut iufuyveculriuxceabcertyutoyzdxfe ", &len);
    int i = 0;

    uint8_t **blocks = create_blocks(buf, len);
    for (int j = 0; j < len; j++){
        printf("%02x ", buf[j]);
            if ((j + 1) % 16 == 0) printf("\n");
    }
    free(buf);

    while (i < len / 64)
    {
        for (int j = 0; j < 64; j++)
            {
                printf("%02x ", blocks[i][j]);
                if ((j + 1) % 16 == 0) printf("\n");
            }

        i++;
    }
    printf("\n");
    */
    //double num = sqrt(2.0);
    uint32_t ex, *K = init_k();

    double e = 1.0f / 3.0f;

   /*for (int i = 0; i < K_SIZE; i++){
        printf("%i\t", i);
        print_bin(K[i]);
    }*/

    printf("e: %f %x\n", e, ex = getWord(cbrt(primes[34])));
    print_bin(ex);

    return (0);

}