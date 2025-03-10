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

//gavivisha256.c
uint32_t sigma0(uint32_t w);
uint32_t sigma1(uint32_t w);
uint8_t *pad(uint8_t *msg, size_t *l);
uint8_t **create_blocks(uint8_t *padded_msg, size_t len);

void print_bin(uint32_t hexa);
uint32_t getWord(double i_number);
uint32_t rotr(uint32_t value, uint8_t shift);
uint32_t *init_state_variables();
uint32_t *init_k();

extern uint32_t primes[PRIMES_SIZE];

#endif