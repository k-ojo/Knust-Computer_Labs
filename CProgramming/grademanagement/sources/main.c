#include "main.h"
#include "parse.h"
#include "prints.h"

void sign_in(){
    char *buf = NULL;
    size_t len = 0;
    bool valid = true;
    uint8_t *hashed_pwd;
    user *u;

    do{
        print_header("LOGIN");
        printf("\t\033[1;31musername:\033[0m");

        if (getline(&buf, &len, stdin) == -1){
            perror("Getline Error");
            exit(EXIT_FAILURE);
        }

        len = strlen(buf);
        if (len && buf[len - 1] == '\n'){
            buf[len - 1] = '\0';
            len--;
        }

        u = parse_user(lookup(buf, "instructor.db"), '|');
        free(buf);
        if (u){
            clearConsole();
            print_header("LOGIN");
            hashed_pwd = enter_pwd();

            if (memcmp(hashed_pwd, u->hashed_pwd, strlen((char *)hashed_pwd)) == 0){
                //get_dashboarb(u);
                printf("Sign in success\n");
            }
            else{
                printf("Invalid passwaord!\n");
            }
        }
        
    }while(valid == false);

}
void start_up(){
    char *option = NULL;
    size_t len = 0;
    int count = 0;
    bool valid = false;
    
    do{
        print_header("WELCOME TO GRADEMENT");
        print_options("\n1. Sign-in\n2. Create Account\n3. Check Result\n");
        printf("Enter q(quit) to exit");
        if (count) printf(" ---- Wrong option! Enter 1, 2, or 3\n");
        else printf("\n");

        if (getline(&option, &len, stdin) == -1){
            perror("Getline Error");
            exit(EXIT_FAILURE);
        }

        printf("%s\n", option);
        if (strncmp(option, "1\n", 2) == 0){
            clearConsole();
            sign_in();
            valid = true;
        }
        else if (strncmp(option, "2\n", 2) == 0){
            clearConsole();
            printf("break\n");
            valid = true;
        }
        else if (strncmp(option, "3\n", 2) == 0){
            clearConsole();
            printf("break\n");
            valid = true;
        }

        else if (strncmp(option, "Q\n", 2) == 0|| strncmp(option, "quit\n", 5) == 0|| strncmp(option, "q\n", 2) == 0){
            clearConsole();
            perror("Terminated Program");
            exit(EXIT_FAILURE);
        }

        else if (count > 10){
            clearConsole();
            printf("Too Many Attempts\n");
            exit(EXIT_FAILURE);
        }
        else{
            clearConsole();
            valid = false;
        }
        count++;
        free(option);
    }while(valid == false);
}

int main (void){
    user *u1, *u2;

    u1 = parse_user(lookup("user1", "instructor.db"), '|');
    u2 = parse_user(lookup("user1", "instructor.db"), '|');

    uint8_t *pswd = enter_pwd();
    printf("%i\n", memcmp(pswd, u2->hashed_pwd, strlen((char *)pswd)));
    free_user(u1);
    free_user(u2);
    return (0);
}