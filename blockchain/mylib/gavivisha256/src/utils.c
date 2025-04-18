#include "gavivisha256.h"


uint32_t primes[PRIMES_SIZE] = {
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


uint32_t *init_s()
{
    uint32_t *S = (uint32_t *)malloc(sizeof(uint32_t) * S_SIZE);
    if (!S)
        exit(99);
    for (int i = 0; i < S_SIZE; i++){
        S[i] = getWord(sqrt(primes[i]));
    }
    return (S);
}

uint32_t *init_w(uint8_t *block){
    uint32_t *W = malloc(sizeof(uint32_t) * W_SIZE);
    memset(W, 0x0, sizeof(uint32_t) * W_SIZE);
    uint8_t bbs_len = BLOCK_SIZE / I_SIZE;
    int i, w;

    for (w = 0, i = 0; i < BLOCK_SIZE / I_SIZE; i++, w += 4){
        for (int j = 3; j >= 0; j--){
            W[i] = W[i] | ((uint32_t)block[w + (3 -j)] << (8 * j)); //take 32 bits and store at W[i]
        }
    }

    for (int t = bbs_len; t < W_SIZE; t++)
        W[t] = O_1(W[t-2]) + W[t - 7] + O_0(W[t - 15]) + W[t - 16];
    return (W);
}

uint32_t *init_k(){
    uint32_t *K = malloc(sizeof(uint32_t) * K_SIZE);
    for (int i = 0; i < K_SIZE; i++){
        K[i] = getWord(cbrt(primes[i]));
    }
    return (K);
}
