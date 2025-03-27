#ifndef _DBUTILS
#define _DBUTILS

#include "main.h"

typedef struct{
    char *firstname;
    char *username;
    char *email;
    char *lastname;
    uint8_t *hashed_pwd;
}user;

char *lookup(char *str, const char *path);
user *init();
void free_user(user *u);
void save_user_to_db(user *u, const char *path, char delim);

//sign_up.c
user *sign_in();
user *sign_up();


#endif