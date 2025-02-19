#include "main.h"

void clearConsole(){
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");
    #endif
}
pages *page_init(char *str, int num)
{
    pages *p = (pages *)malloc(sizeof(pages));
    p->str = (char *)malloc(strlen(str) * sizeof(char));
    memcpy(p->str, str, strlen(str));
    p->num = num;
    return (p);
}

void delete_page(pages *p){
    free(p->str);
    free(p);
}

int show_page(pages *p)
{
    printf("%s\n", p->str);
    return (0);
}