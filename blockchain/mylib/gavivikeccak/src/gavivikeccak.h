#ifndef _GAVIVIKECCAK_
#define _GAVIVIKECCAK_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S_LEN 7
#define O_LEN 4
#define BS_INDEX 6
#define BUFF_TYPE_SIZE 32



typedef enum{
    o_224 = 0,
    o_256 = 1,
    o_384 = 2,
    o_512 = 3
}o_size;

typedef struct{
    int l;
    uint32_t b;
    o_size type;
}b_state;

typedef struct{
    uint32_t *r;
    uint32_t *c;
    size_t c_len;
    size_t r_len;
}buf_t;

extern uint32_t b_s[S_LEN];
extern uint32_t c_size[O_LEN];
extern const uint32_t r_size[O_LEN], n_o_blocks;
extern b_state b;

void c_blocks(uint32_t **blocks, uint32_t *padded_msg, size_t m_len);
void keccak_init(uint8_t _b, o_size size);
uint8_t pad(uint8_t *msg, uint32_t *padded_msg, size_t *l);

#endif