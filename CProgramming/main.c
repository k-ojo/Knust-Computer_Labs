#include "main.h"

int main(void){

    pages *p1, *p2, *p3, *p4;
    char buf[MAX_BUF_LENGTH];
    flavours *flavors = init_flavours(5);

    flavors->size = 0;

    Order order = { 0, 0, 0, 0, 0, 0, 0};

    add_flavour("Mango", flavors, smallVanilla, largeVanilla);
    add_flavour("Vanilla", flavors, smallVanilla, largeVanilla);
    add_flavour("Strawberry", flavors, smallVanilla, largeVanilla);
    add_flavour("Chocolate", flavors, smallVanilla, largeVanilla);
    delete_flavour(flavors, "Chocolate");
    add_flavour("Chocolate", flavors, smallVanilla, largeVanilla);


    p1 = page_init("WELCOME TO FIIFI’S ICE CREAM SHOP\n\t1. Order\n\t2. Enqueries", 1);
    p2 = page_init(get_flavours(buf, flavors), 2);
    p3 = page_init("Contact Support", 3);
    p4 = page_init("Choose a size (1 or 2)\n\n1- Small\n2- Large\n", 4);

    do{
        clearConsole();
        show_page(p1);
        scanf("%d", &order.enquire);
        if (order.enquire == 2){
            show_page(p3);
            exit(99);
        }
        else{
            clearConsole();
            printf("Order Something\t\t\n");
            show_page(p2);
            scanf("%d", &order.flavour);
            clearConsole();
            show_page(p4);
            scanf("%d", &order.size);
            clearConsole();
            if ((order.size == 0 || order.size == 1) && (order.flavour > 0 && order.flavour < 7))
                printf("Name of Flavour: %s\nType: %s\n", flavors->container[order.flavour]->name, type[order.size - 1]);

            else{
                printf("Ooops!\nYou did not enter a valid Flavour or size.\nTry again!\n");
                exit(99);
            }
        }
    }while(order.order > 0);

    printf("%s\n", flavors->container[3]->name);
    delete_flavours(flavors);
    return (0);
}