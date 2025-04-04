#include "dbutils.h"
#include "main.h"
#include "parse.h"

char *lookup(char *str, const char *path){
    char *buf = NULL;
    size_t len = 0;
    FILE *f = fopen(path, "r");
    if (!f){
        perror("File opening");
        exit(EXIT_FAILURE);
    }
    while (getline(&buf, &len, f) != EOF)
    {
        if (strncmp(str, buf, strlen(str)) == 0 && buf[strlen(str)] == '|')
        {
            fclose(f);
            return buf;
        }
    }
    fclose(f);
    free(buf);
    return NULL;
}

user *init(){
    user *u = (user *)malloc(sizeof(user));
    u->email = (char *)malloc(sizeof(char) * 50);
    strcpy(u->email, "NULL");
    u->firstname = (char *)malloc(sizeof(char) * 50);
    strcpy(u->firstname, "NULL");
    u->lastname = (char *)malloc(sizeof(char) * 50);
    strcpy(u->lastname, "NULL");
    u->username = (char *)malloc(sizeof(char) * 50);
    strcpy(u->username, "NULL");
    u->hashed_pwd = (uint8_t *)malloc(sizeof(uint8_t) * SHA256_DIGEST_LENGTH);
    memcpy(u->hashed_pwd, "NULL", 4);
    return u;
}

void free_user(user *u){
    if (!u) return;
    free(u->email);
    free(u->username);
    free(u->firstname);
    free(u->lastname);
    free(u->hashed_pwd);
    free(u);
}

void save_user_to_db(user *u, const char *path, char delim){

    char *hex = malloc(2 * SHA256_DIGEST_LENGTH + 1);
    if (!hex){
        perror("Memory Alloc failed");
        return;
    }

    bytes_to_hex(u->hashed_pwd, SHA256_DIGEST_LENGTH, hex);
    printf("%s\n", path);

    FILE *f = fopen(path, "a");
    if (!f){
        perror("File opening");
        return;
    }

    fprintf(f, "%s%c%s%c%s%c", u->username, delim, u->firstname, delim, u->lastname, delim);
    printf("%s\n", path);

    fprintf(f, "%s%c%s\n", u->email, delim, hex);
    fclose(f);
    free(hex);
}