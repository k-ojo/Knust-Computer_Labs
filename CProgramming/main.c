#include "main.h"

int main(void){

    flavours *flavors = init_flavours(5);
    add_flavour("Vanilla", flavors);
    return (0);
}