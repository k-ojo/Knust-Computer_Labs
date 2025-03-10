#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define K_SIZE 64
uint32_t primes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
    353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
    467, 479, 487, 491, 499, 503, 509, 521, 523, 541
};

void print_bin(uint32_t hexa)
{
    size_t len = sizeof(hexa) * CHAR_BIT;
    //printf("0b ");
    for (int i = len - 1; i >= 0; i--)
    {
        printf("%u", (hexa >> i) & 0x1);
        if (i % 4 == 0)
            printf(" ");
    }
    printf("\n");
}

uint32_t getWord(double i_number)
{
    double intpart = (int)i_number;
    double frac = i_number - intpart;
    return (uint32_t)(frac * (1ULL << 32));
}

uint32_t rotr(uint32_t value, uint8_t shift)
{
    shift %= (sizeof(value) * CHAR_BIT);
    return (value >> shift) | (value << (sizeof(value) * CHAR_BIT) - shift);
}

uint8_t *pad(uint8_t *msg, size_t *l)
{
    size_t len = strlen((char *)msg);
    uint8_t *padded_msg;
    size_t p = (56 - ((len + 1) % 64)) % 64, tl = len + 1 + p + 8;
    uint64_t bit_len;

    padded_msg = (uint8_t *)malloc(sizeof(uint8_t) * tl);
    memcpy(padded_msg, msg, len);
    padded_msg[len] = 0x80;
    memset(padded_msg + len + 1, 0x0, p);
    bit_len = (uint64_t)len * 8;

    for (int i = 0; i < 8; i++)
    {
        padded_msg[tl - 8 + i] = (uint8_t)((bit_len >> (56 - (i * 8))) & 0xFF);
    }
    *l = tl;
    return (padded_msg);
}

uint32_t *init_state_variables()
{
    uint32_t *S = malloc(sizeof(uint32_t) * 8);
    for (int i = 0; i < 8; i++){
        S[i] = getWord(sqrt(primes[i]));
    }
}

uint32_t *init_k(){
    uint32_t *K = malloc(sizeof(uint32_t) * K_SIZE);
    for (int i = 0; i < K_SIZE; i++){
        K[i] = getWord(cbrt(primes[i]));
    }
}

uint32_t sigma0(uint32_t w){
    uint32_t R_7, R_18, S_3;
    R_7 = rotr(w, 7), R_18 = rotr(w, 18);
    S_3 = w >> 3;
    return ((R_7 ^ R_18) ^ S_3);
};

uint32_t sigma1(uint32_t w){
    uint32_t R_17, R_19, S_10;
    R_17 = rotr(w, 7), R_19 = rotr(w, 18);
    S_10 = w >> 10;
    return ((R_17 ^ R_19) ^ S_10);
};

uint32_t (*sigma[2]) (uint32_t) = {sigma0, sigma1};



uint8_t **create_blocks(uint8_t *padded_msg, size_t len)
{
    size_t n = len / 64;
    uint8_t **blocks = (uint8_t **)malloc((sizeof(uint8_t *) * n));

    for (int i = 0; i < n; i++)
    {
        blocks[i] = malloc(sizeof(uint8_t) * 64);
        memcpy(blocks[i], padded_msg + (i * 64), 64);
    }
    return (blocks);
}

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