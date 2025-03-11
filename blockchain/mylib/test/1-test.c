#include "../gavivisha256.h"

void print_buf(uint8_t *buf, size_t size){
    for (int j = 0; j < size; j++){
        printf("%02x ", buf[j]);
            if ((j + 1) % 16 == 0) printf("\n");
    }
}

int main()
{

    
    /*size_t len;
    uint8_t *buf = pad("abc", &len);
    int i = 0;

    /*for (int j = 0; j < len; j++){
        printf("%02x ", buf[j]);
            if ((j + 1) % 16 == 0) printf("\n");
    }

    //print_buf(buf, len);
    print_bin(buf[0]);


    uint8_t **blocks = create_blocks(buf, len);

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



    uint32_t *W = init_w(blocks[0]);
    for (int i = 0; i < W_SIZE; i ++){
        printf("W%i\t", i);
        print_bin(W[i]);
    }

    /**
     * 
    //double num = sqrt(2.0);
    uint32_t ex, *K = init_k();

    double e = 1.0f / 3.0f;

   /*for (int i = 0; i < K_SIZE; i++){
        printf("%i\t", i);
        print_bin(K[i]);
    }

    printf("e: %f %x\n", e, ex = getWord(cbrt(primes[34])));
    print_bin(ex);
  */

    /*uint32_t A = 0b11, B = 0b101, C = 0b1001;

    print_bin(M_(A, B, C));*/
    uint32_t digest[256 / 8];
    gavivisha256("abc", digest);
    for (int i = 0; i < 8; i++){
        print_bin(digest[i]);
    }
    return (0);
    
}