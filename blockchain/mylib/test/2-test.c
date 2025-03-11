# include "../gavivisha256.h"

void print_W(uint32_t *W){
    for (int w = 0; w < 16; w++){
        printf("%i\t", w);
        print_bin(W[w]);
    }
}

int main(){

    size_t len;
    char msg[] = "abc";
    uint8_t *padded = pad(msg, &len);
    uint8_t **blocks = create_blocks(padded, len);
    uint32_t *W = init_w(blocks[0]);

    print_W(W);

}