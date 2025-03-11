#include "gavivisha256.h"


uint32_t O_0(uint32_t w){
    uint32_t R_7, R_18, S_3;
    R_7 = rotr(w, 7), R_18 = rotr(w, 18);
    S_3 = w >> 3;
    return (R_7 ^ R_18 ^ S_3);
}

uint32_t O_1(uint32_t w){
    uint32_t R_17, R_19, S_10;
    R_17 = rotr(w, 17), R_19 = rotr(w, 19);
    S_10 = w >> 10;
    return (R_17 ^ R_19 ^ S_10);
}

uint32_t rotr(uint32_t value, uint8_t shift)
{
    shift %= (sizeof(value) * CHAR_BIT);
    return (value >> shift) | (value << (sizeof(value) * CHAR_BIT) - shift);
}

uint32_t Z_0(uint32_t x){
    return (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22));
}
uint32_t Z_1(uint32_t x){
    return (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25));
}

uint32_t C_(uint32_t A, uint32_t B, uint32_t C){
    return (((~A) & C) | (B & C) | (A & B));
}

uint32_t M_(uint32_t A, uint32_t B, uint32_t C){
    return ((A & C) | (B & C) | (A & B));
}