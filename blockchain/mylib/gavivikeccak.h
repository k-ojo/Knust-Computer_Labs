#ifndef _GAVIVIKECCAK_
#define _GAVIVIKECCAK_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define S_LEN 7
#define O_LEN 4
#define BS_INDEX 6

extern uint32_t b_s[S_LEN];
extern uint32_t r[O_LEN], b;
extern const uint32_t c[O_LEN], n_o_blocks;

typedef enum{
    o_224 = 0,
    o_256 = 1,
    o_384 = 2,
    o_512 = 3
}o_size;

#endif