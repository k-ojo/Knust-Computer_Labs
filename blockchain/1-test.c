#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint8_t *pad(uint8_t *msg, size_t *l){
    size_t len = strlen((char *)msg);
    uint8_t *padded_msg;
    size_t p = (56 - ((len + 1) % 64)) % 64, tl = len + 1 + p + 8;
    uint64_t bit_len;
     
    padded_msg = (uint8_t *)malloc(sizeof(uint8_t) * tl);
    memcpy(padded_msg, msg, len);
    padded_msg[len] = 0x80;
    memset(padded_msg + len + 1, 0x0, p);
    bit_len = (uint64_t)len * 8;

    for (int i = 0; i < 8; i++){
        padded_msg[tl - 8 + i] = (uint8_t)((bit_len >> (56 - (i * 8))) & 0xFF);
    }
    *l = tl;
    return (padded_msg);
}

uint8_t **create_blocks(uint8_t *padded_msg, size_t len){
    size_t n = len / 64;
    uint8_t **blocks = (uint8_t **)malloc((sizeof(uint8_t *) * n));

    for (int i = 0; i < n; i++){
        blocks[i] = malloc(sizeof(uint8_t) * 64);
        memcpy(blocks[i], padded_msg + (i * 64), 64);
    }
    return (blocks);
}

int main(){
    
    size_t len;
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
    
    return (0);
}