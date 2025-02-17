#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>

#define MAX_BUF_LENGTH 200

#define smallVanilla 5.00
#define largeVanilla 8.00
#define smallStrawberry 5.00
#define largeStrawberry 8.00
#define smallChocolate 6.00
#define largeChocolate 9.00
#define smallMango 7.00
#define largeMango 10.00

extern const char *type[];

typedef struct{
    /* data */
    int time;
    int cost;
    int order;
    int topping;
    int size;
    int flavour;
    int enquire;
}Order;

typedef struct{
    int key;
    //char *type[2];
    float prices[2];
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
int add_flavour(char *str, flavours *f, float, float);
flavours *init_flavours(size_t s);
void delete_flavours(flavours *f);
void delete_flavour(flavours *f, char *name);
char *get_flavours(char *buf, flavours *f);

void clearConsole();

#endif