#include "../headers/parse.h"

char *parse_attribute(char *buf, user *u, attr att, char delim){
    size_t n = strlen(buf);
    char hpwd[EVP_MAX_BLOCK_LENGTH * 2];

    for(size_t i = 0; i < n; i++){
        if (buf[i] == delim || buf[i] == '\n'){
            switch (att)
            {
            case UNAME:
                strncpy(u->username, buf, i);
                break;
            case EMAIL:
                strncpy(u->email, buf, i);
                break;
            case FNAME:
                strncpy(u->firstname, buf, i);
                break;
            case LNAME:
                strncpy(u->lastname, buf, i);
                break;
            case H_PWD:
                strncpy(hpwd, buf, i);
                hex_to_bytes(hpwd, u->hashed_pwd, strlen(hpwd)/2);
                break;
            default:
                printf("Invalid attribute\n");
                break;
            }
            return (buf + i + 1);
        }
    }
    return NULL;

}

user *parse_user(char *buf, char delim){
    if (!buf) return NULL;
    user *u = init();
    char *tmp = buf;
    int i = 0;
    

    while (*tmp && *tmp != '\n'){
        tmp = parse_attribute(tmp, u, UNAME + i, delim);
        i++;
    }
    free(buf);

    return u;
}