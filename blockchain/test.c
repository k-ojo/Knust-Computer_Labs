#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define ERRNO INT_MAX

uint8_t arr[4][4] = {0x0};

int gcd_find(int x, int y){
    int R[2], q = x > y ? x : y;
    R[1] = x <= y ? x : y;

    do{
        R[0] = R[1];
        R[1] = q % R[0];
        q = R[0];
    }while(R[1] != 0);

    return R[0];
}


int inverse_mod(int x, int y){
    int Q, R, a = y, b = x % y, T[3];
    R = b;
    T[1] = 0, T[2] = 1;

    do{
        R = b;
        Q = a / R;
        b = a % R;
        a = R;
        T[0] = T[1] - (T[2] * Q);
        T[1] = T[2];
        T[2] = T[0];
    }while (b != 0);

    if (R != 1)
        return ERRNO;
    return (T[1] % y);    
}

int main(){

    printf("%d\n", inverse_mod(4, 13));
    return (0);
}