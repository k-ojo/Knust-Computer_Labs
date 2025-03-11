#include "../gavivisha256.h"

int main(){
    uint32_t input[] = {0x00FF00FF, 0x0000FFFF, 0xFFFF0000};
    printf("%08X\n", C_(input[0], input[1], input[2]));
    printf("%08X\n", Z_0(input[1]));
    printf("%08X\n", M_(input[0], input[1], input[2]));
}