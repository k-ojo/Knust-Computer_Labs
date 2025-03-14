#include "../gavivikeccak.h"

int main(void){

    //keccak_init(BS_INDEX, o_224);
    char *buf = "abc";
    size_t len = strlen(buf);
    uint32_t *padded = malloc(sizeof(uint32_t) * ((len / 2) + 4 + 1));

    pad(buf, padded, &len);

    return (0);

}