#include "gavivisha256.h"

static uint32_t (*sigma[2]) (uint32_t) = {sigma0, sigma1};

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