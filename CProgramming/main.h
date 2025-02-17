#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>

typedef enum{
    
    smallVanilla = 5,
    largeVanilla = 8,
    smallStrawberry = 5,
    largeStrawberry = 8,
    smallChocolate = 6,
    largeChocolate = 9,
    smallMango = 7,
    largeMango = 10,
}size;

typedef struct{
    /* data */
    int time;
    int cost;
    int order;
    int topping;
    int size;
    int flavour;
}order;

typedef struct{
    int key;
    char *name;
}flavour;

typedef struct{
    /* data */
    int size;
    int capacity;
    flavour **container;

}flavours;



typedef struct{
    int num;
    char *str;
}pages;

pages *page_init(char *str, int num);
int show_page(pages *p);
int add_flavour(char *str, flavours *f);
flavours *init_flavours(size_t s);
void delete_flavours(flavours *f);
void delete_flavour(flavours *f, char *name);

#endif