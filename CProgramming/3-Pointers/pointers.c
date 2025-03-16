#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_WIDTH 38

int x = 0; //1
int *ptrx = &x; //2
int **ptrptrx = &ptrx; //3

void add(float *ptrf, float x);
void sub(float *ptrf, float x);
void mul(float *ptrf, float x);
void dvd(float *ptrf, float x);
//void print_cal(float x, float y, char op, char *prev);



int main(){
    /*printf("x: %i\n ptr: %p\n ptrptr: %p\n", x, ptrx, ptrptrx); //4
    printf("x: %d\n x from ptrx: %d\n x from ptrptrx: %d\n", x, *ptrx, **ptrptrx); //5
    */
start:
    float x = 0 , y, *result = &x; //2b.
    char op;  //2c.
    bool status = true;
    static uint32_t count = 0;

    
    printf("\n\n[ 0 ][ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ][ 7 ][ 8 ][ 9 ]\n[ + ][ - ][ * ][ / ][      @0      ][      #0    ]\n\n");
    printf("Start calculations :)\n");
    
    do{
        scanf("%c %f", &op, &y);
        getchar(); //get newline left after scanf

        switch (op)
        {
            case '\n':
            break;
            case '+':
            add(result, y);
            break;
            case '-':
            sub(result, y);
            break;
            case '*':
            if (count == 0 & *result == 0)
                *result = 1.0f;
            mul(result, y);
            break;
            case '/':
            if (!count && !result)
                *result = 1.0f;
            dvd(result, y);
            break;
            case '#': 
            printf("Goodbye :(\n"); 
            status = false;
            break;
            case '@': 
            goto start; 
            break;
            default: 
            printf("Error :(\n"); 
            goto start;
        }
        count++;
    }while(status);
    return (0);
}

void add(float *ptrf, float x){ //1a
    printf("%*g + %g\n", MAX_WIDTH, *ptrf, x); // 1b
    *ptrf += x;  //1c
    printf("%*g\n", MAX_WIDTH, *ptrf); //1d
}

void sub(float *ptrf, float x){
    printf("%*g - %g\n", MAX_WIDTH, *ptrf, x);
    *ptrf -= x;
    printf("%*g\n", MAX_WIDTH, *ptrf);
}

void mul(float *ptrf, float x){
    printf("%*g × %g\n", MAX_WIDTH, *ptrf, x);
    *ptrf *= x;
    printf("%g\n", MAX_WIDTH, *ptrf);
}

void dvd(float *ptrf, float x){ 
    printf("%*g ÷ %g\n", MAX_WIDTH, *ptrf, x);
    *ptrf /= x;
    printf("%*g\n", MAX_WIDTH, *ptrf);
}