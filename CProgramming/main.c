#include "main.h"

int main(void){

    pages *p1, *p3;
    char buf[100];
    flavours *flavors = init_flavours(5);

    add_flavour("Vanilla", flavors);
    add_flavour("Vanilla", flavors);
    add_flavour("Vanilla", flavors);
    add_flavour("Vanilla", flavors);

    p1 = page_init("WELCOME TO FIIFI’S ICE CREAM SHOP\n\t1. Order\n\t2. Enqueries", 1);

    p3 = page_init(get_flavours(buf, flavors), 3);

    show_page(p1);
    show_page(p3);

    return (0);
}