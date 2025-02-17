#include "main.h"

int main(void){

    int index;
    pages *p1, *p3;
    char buf[100];
    flavours *flavors = init_flavours(5);
    add_flavour("Vanilla", flavors);
    p1 = page_init("WELCOME TO FIIFI’S ICE CREAM SHOP\n\t1. Order\n\t2. Enqueries", 1);


    index = flavors->size;
    printf("%d\n", index);

    while(index > 0){
        sprintf(buf, "%d - %s\n", index, flavors->container[index- 1]->name);
        index--;
    }

    printf("buf: %s\n", buf);
    p3 = page_init(buf, 3);

    show_page(p1);
    show_page(p3);
    return (0);
}