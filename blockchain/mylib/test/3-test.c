# include "../gavivisha256.h"

void print_s(uint32_t *S){
    for (int w = 0; w < 8; w++){
        printf("%i\t", w);
        print_bin(S[w]);
    }
}

void print_k(uint32_t *K){
    for (int w = 0; w < 64; w++){
        printf("%i\t", w);
        print_bin(K[w]);
    }
}

int main(){

    size_t len;
    char msg[] = "abc";
    uint8_t *padded = pad(msg, &len);
    uint8_t **blocks = create_blocks(padded, len);
    uint32_t *W = init_w(blocks[0]);
    uint32_t *S = init_s(), *K = init_k();


    //print_W(W);
    print_s(S);
    //print_k(K);

}