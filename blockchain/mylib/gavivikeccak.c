#include "gavivikeccak.h"

uint32_t b_s[S_LEN], c[O_LEN], b;

const uint32_t r[O_LEN] = {1152, 1088, 82, 576};

void init(uint8_t _b){
    for(int l = 0; l < S_LEN; l++)
       b_s[l] = 25 * (1UL << l);
    b = b_s[_b];
    for(int i = 0; i < O_LEN; i++){
        c[i] = b - r[i];
    }
}

/**
 * c_blocks- creates blocks
 * @blocks: blocks of n size container
 * @size: size of ouput, 224, 256, etc ...
 * @buf: message buffer
 * @m_len: message length
 * Return: Nothing
 */
void c_blocks(uint8_t **blocks, uint8_t *buf, o_size size, size_t m_len){
    int i = 0, b_size = r[size] / 8, n_blocks = m_len / b_size;
    for (int j = 0; j < b_size; j++){
        for (; i < b_size * (j + 1); i++)
            blocks[j][i] = buf[i];
    }
}

int main(void){
    init(BS_INDEX);

    return (0);
}