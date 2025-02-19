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
    //delete_flavour(flavors, "Chocolate");
    //add_flavour("Chocolate", flavors, smallVanilla, largeVanilla);


    p1 = page_init("WELCOME TO FIIFI’S ICE CREAM SHOP\n\t1. Order\n\t2. Enqueries", 1);
    p2 = page_init(get_flavours(buf, flavors), 2);
    p3 = page_init("Contact Support", 3);
    p4 = page_init("Choose a size (1 or 2)\n\n1- Small\n2- Large\n", 4);

    do{
        clearConsole();
        show_page(p1);
        if (scanf("%d", &order.enquire) == EOF){
            exit(errno);
        }
        if (order.enquire == 2){
            show_page(p3);
            exit(errno);
        }
        else{
            clearConsole();
            printf("Order Something\t\t\n");
            show_page(p2);
            if (scanf("%d", &order.flavour) == EOF){
                exit(errno);
            }
            clearConsole();
            show_page(p4);
            if (scanf("%d", &order.size) == EOF)
                exit (errno);
            clearConsole();
            if ((order.size == 1 || order.size == 2) && (order.flavour > 0 && order.flavour < flavors->size))
                printf("\t\tFlavour: %s\n\t\tType: %s\n", flavors->container[order.flavour]->name, type[order.size - 1]);

            else{
                printf("Ooops!\nYou did not enter a valid Flavour or size.\nTry again!\n");
                exit(errno);
            }
        }
    }while(order.order > 0);

    delete_page(p1);
    delete_page(p2);
    delete_page(p3);
    delete_page(p4);
    
    delete_flavours(flavors);

    return (0);
}