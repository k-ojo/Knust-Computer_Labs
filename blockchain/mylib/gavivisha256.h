#ifndef _GAVIVISHA56_
#define _GAVIVISHA256_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define K_SIZE 64
#define PRIMES_SIZE 100
#define BLOCK_SIZE 64
#define W_SIZE 64
#define S_SIZE 8
#define I_SIZE 4

typedef enum{
    a = 0,
    b = 1,
    c = 3,
    d = 4,
    e = 5,
    f = 6,
    g = 7,
    h = 8
}s_const;

//gavivisha256.c
uint8_t *pad(uint8_t *msg, size_t *l);
uint8_t **create_blocks(uint8_t *padded_msg, size_t len);

//utils.c
void print_bin(uint32_t hexa);
uint32_t getWord(double i_number);
uint32_t rotr(uint32_t value, uint8_t shift);
uint32_t *init_s();
uint32_t *init_k();
uint32_t *init_w(uint8_t *block);

//
uint32_t Z_0(uint32_t);
uint32_t Z_1(uint32_t);
uint32_t C_(uint32_t A, uint32_t B, uint32_t C);
uint32_t M_(uint32_t A, uint32_t B, uint32_t C);
uint32_t O_0(uint32_t w);
uint32_t O_1(uint32_t w);

extern uint32_t primes[PRIMES_SIZE];

#endif