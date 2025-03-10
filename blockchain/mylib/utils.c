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

uint32_t rotr(uint32_t value, uint8_t shift)
{
    shift %= (sizeof(value) * CHAR_BIT);
    return (value >> shift) | (value << (sizeof(value) * CHAR_BIT) - shift);
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