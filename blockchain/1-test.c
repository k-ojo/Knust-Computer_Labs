#include <stdint.h>
#include <stdio.h>


uint8_t *pad(uint8_t *msg){
    size_t len = sizeof(msg);
    uint8_t *padded_msg;
    int p = len + 1, i;

    while((len + 8) % 64){
        p++;
    }
    padded_msg = (uint8_t *)malloc(sizeof(uint8_t) * p);
    padded_msg[len] = 0x8;

    memset(padded_msg + len + 1, 0x0, p - len - 1 - 8);
    
    
}
int main(){
    return (0);
}