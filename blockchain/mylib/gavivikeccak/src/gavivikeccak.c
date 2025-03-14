#include "gavivikeccak.h"

uint32_t b_s[S_LEN], c_size[O_LEN], n_r;
const uint32_t r_size[O_LEN] = {1152, 1088, 82, 576};
b_state b;

/**
 * init- sets states of b, c(capacity) and r(rates)
 * @_b: 
 */
void keccak_init(uint8_t _b, o_size size){
    for(int l = 0; l < S_LEN; l++)
       b_s[l] = 25 * (1UL << l);

    b.l = _b;
    b.b = b_s[_b];
    b.type = size;
    n_r = 12 + b.l + b.l;

    for(int i = 0; i < O_LEN; i++)
        c_size[i] = b.b - r_size[i];
}

/**
 * buf_init- initialize  
 */
buf_t *buf_init(){

    buf_t *buf = (buf_t *)malloc(sizeof(buf_t));
    buf->r_len = r_size[b.type] / BUFF_TYPE_SIZE;
    buf->c_len = c_size[b.type] / BUFF_TYPE_SIZE;

    buf->r = (uint32_t *)malloc(sizeof(uint32_t) * buf->r_len);
    buf->c = (uint32_t *)malloc(sizeof(uint32_t) * buf->c_len);

    memset(buf->c, 0x0, buf->c_len * 2);
    memset(buf->r, 0x0, buf->r_len * 2);

}

/**
 * c_blocks- creates blocks
 * @blocks: blocks of n size container
 * @size: size of ouput, 224, 256, etc ...
 * @buf: message buffer
 * @m_len: message length
 * Return: Nothing
 */
void c_blocks(uint32_t **blocks, uint32_t *padded_msg, size_t m_len){
    int i = 0, b_size = r_size[b.type] / BUFF_TYPE_SIZE;
    int n_blocks = m_len / b_size;

    for (int j = 0; j < n_blocks; j++){
        for (; i < b_size * (j + 1); i++)
            blocks[j][i] = padded_msg[i];
    }

}

/**
 * pad- pad message
 * @msg: message
 * @padded_msg: padded message
 * @l: length
 * 
 */
uint8_t pad(uint8_t *msg, uint32_t *padded_msg, size_t *l)
{
    size_t m_len = strlen((char *)msg), tl;
    int b_size = r_size[b.type] / BUFF_TYPE_SIZE;
    size_t padd_len = (b_size - 2 - ((((m_len) / 4)) % b_size)) % b_size; //pad_len

    uint64_t len = (uint64_t)m_len * 8;

    tl = m_len/4 + padd_len + 2;

    for (int i = 0; i < m_len ; i += 4){
        for (int j = 0; j < 4; j++) 
            padded_msg[i] |= ((uint32_t)msg[j + i]) << j * 8;
    }
    memset(padded_msg + len/4 + 1, 0x0, padd_len * 4);

    for (int i = 0; i < 2; i++)
        padded_msg[tl - 2 + i] = (uint32_t)((len >> (b_size - (i * 32))) & 0xFFFF);

    return (*padded_msg);

}