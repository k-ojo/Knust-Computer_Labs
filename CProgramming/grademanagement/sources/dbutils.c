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
    u->hashed_pwd = (uint8_t *)malloc(sizeof(uint8_t) * EVP_MAX_MD_SIZE);
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

    char *hex = malloc(2 * EVP_MAX_BLOCK_LENGTH + 1);
    if (!hex){
        perror("Memory Alloc failed");
        return;
    }

    bytes_to_hex(u->hashed_pwd, EVP_MAX_BLOCK_LENGTH, hex);
    printf("Break\n");
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

user *sign_in()
{
    char *buf = NULL;
    size_t len = 0;
    bool valid = true;
    uint8_t *hashed_pwd;
    user *u;
    int count = 0;

    do
    {
        clearConsole();
        print_header("LOGIN");
        printf("\t\033[1;31musername:\033[0m");

        if (getline(&buf, &len, stdin) == -1)
        {
            perror("Getline Error");
            exit(EXIT_FAILURE);
        }

        len = strlen(buf);
        if (len && buf[len - 1] == '\n')
        {
            buf[len - 1] = '\0';
            len--;
        }

        u = parse_user(lookup(buf, "instructor.db"), '|');
        if (u)
        {

            here:
            clearConsole();
            print_header("LOGIN");
            if (count > 0)
                printf("Invalid passwaord! %d attempt(s) more available\n", PWD_TRY_TIMES - count);

            hashed_pwd = enter_pwd();

            if (memcmp(hashed_pwd, u->hashed_pwd, strlen((char *)hashed_pwd)) == 0)
            {
                // get_dashboarb(u);
                clearConsole();
                printf("Sign in success\n");
                free(buf);
                free(hashed_pwd);
                return(u);
            }
            else
            {
                clearConsole();
                if (count >= PWD_TRY_TIMES - 1)
                {
                    printf("Too Many Attempts. Try again Later\n");
                    free_user(u);
                    free(buf);
                    free(hashed_pwd);
                    exit(EXIT_FAILURE);
                }
                count++;
                free(hashed_pwd);
                goto here;
            }
        }
        else
        {
        label:
            clearConsole();
            printf("User is not signed up!\n");
            printf("1. Try Again\n2. Create Account\n");
            if (getline(&buf, &len, stdin) == 1)
            {
                perror("Getline");
                return (NULL);
            }
            if (strcmp(buf, "1\n") == 0)
            {
                valid = false;
            }
            else if (strcmp(buf, "2\n") == 0)
            {
                clearConsole();
                start_up();
                valid = false;
            }
            else
            {
                clearConsole();
                printf("Invalid option");
                goto label;
            }
        }
    } while (valid == false);
    free(buf);
    return NULL;
}