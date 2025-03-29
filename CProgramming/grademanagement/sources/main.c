#include "main.h"
#include "parse.h"
#include "prints.h"
#include "dbutils.h"

const char *I_PATH = "instructor.db";

void start_up()
{
    char *option = NULL;
    size_t len = 0;
    int count = 0;
    bool valid = false;

    do
    {
        print_header("WELCOME TO GRADEMENT");
        print_options("\n1. Sign-in\n2. Create Account\n3. Check Result\n");
        printf("Enter q(quit) to exit");
        if (count)
            printf(" ---- Wrong option! Enter 1, 2, or 3\n");
        else
            printf("\n");

        if (getline(&option, &len, stdin) == -1)
        {
            perror("Getline Error");
            exit(EXIT_FAILURE);
        }

        printf("%s\n", option);
        if (strncmp(option, "1\n", 2) == 0)
        {
            clearConsole();
            free_user(sign_in());
            valid = true;
        }
        else if (strncmp(option, "2\n", 2) == 0)
        {
            clearConsole();
            printf("break\n");
            valid = true;
        }
        else if (strncmp(option, "3\n", 2) == 0)
        {
            clearConsole();
            printf("break\n");
            valid = true;
        }

        else if (strncmp(option, "Q\n", 2) == 0 || strncmp(option, "quit\n", 5) == 0 || strncmp(option, "q\n", 2) == 0)
        {
            clearConsole();
            perror("Terminated Program");
            exit(EXIT_FAILURE);
        }

        else if (count > 10)
        {
            clearConsole();
            printf("Too Many Attempts\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            clearConsole();
            valid = false;
        }
        count++;
        free(option);
    } while (valid == false);
}

int main(void)
{
    start_up();
    return (0);
}