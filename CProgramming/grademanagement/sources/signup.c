#include "main.h"
#include "parse.h"

static char *get_detail(const char *str, color c){
    char *buf = NULL;
    size_t len = 0;

    printf("\t\033[1;%im%s:\033[0m", c, str);

    if (getline(&buf, &len, stdin) == -1)
    {
        perror("Getline Error");
        return NULL;
    }

    len = strlen(buf);
    if (len && buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
        len--;
    }
    if (strlen(buf) > NAME_SIZE)
        return NULL;
    return buf;
}

static void set_attr(user *u){
    char *buf[3];

    buf[0] = get_detail("Enter your firstname", WHITE);
    buf[1] = get_detail("Enter your lastname", WHITE);
    buf[2] = get_detail("Enter your email", WHITE);


    strcpy(u->firstname, buf[0]);
    strcpy(u->lastname, buf[1]);
    strcpy(u->email, buf[2]);

    for (int i = 0; i < 3; i++){
        if (buf[i])
            free(buf[i]);
    }
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

user *sign_up(){
    char *opt, *buf = NULL;
    bool valid = true;
    uint8_t *hashed_pwd[2];
    user *u, *u1;
    int count = 0;

    clearConsole();
    print_header("CREATE ACCOUNT\n");

    u = init();
            set_attr(u);
    do
    {
        clearConsole();
        print_header("CREATE ACCOUNT");
        buf = get_detail("New Username", GREEN);
        u1 = parse_user(lookup(buf, "instructor.db"), '|');

        if (!u1)
        {
            strcpy(u->username, buf);

            here:
            clearConsole();
            print_header("CREATE ACCOUNT");
            if (count > 0)
                printf("Password doesn't match! %d attempt(s) more available\n", PWD_TRY_TIMES - count);

            hashed_pwd[0] = enter_pwd();
            memcpy(u->hashed_pwd,  hashed_pwd[0], strlen((char *)hashed_pwd[0]));
            free(hashed_pwd[0]);

            clearConsole();
            print_header("CREATE ACCOUNT");
            printf("\t\t\033[1;32mConfirm Password\033[0m\n");
            hashed_pwd[1] = enter_pwd();

            if (memcmp(hashed_pwd[1], u->hashed_pwd, strlen((char *)hashed_pwd[1])) == 0)
            {
                clearConsole();
                save_user_to_db(u, "instructor.db", '|');
                printf("Account Creation Success\n");
                free(buf);
                free(hashed_pwd[1]);
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
                    free(hashed_pwd[1]);
                    free_user(u);
                    exit(EXIT_FAILURE);
                }

                count++;
                free(hashed_pwd[1]);
                if (u->hashed_pwd)
                    free(u->hashed_pwd);
                goto here;
            }
        }
        else
        {
            clearConsole();
            opt = get_detail("Username is taken! 🥲\tEnter q(quit) to exit or any other key to try another", WHITE);

            if (strcmp(opt, "q") == 0 && strcmp(opt, "quit") == 0){
                free(buf);
                free_user(u1);
                free_user(u);
                exit(EXIT_FAILURE);
            }

            if (buf)
                free(buf);
            free_user(u1);
            valid = false;
        }
    } while (valid == false);

    free(buf);
    free_user(u1);
    free_user(u);
    return NULL;
}