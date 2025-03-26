#include "password.h"

void clearConsole(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void secure_zero(void *buf, ssize_t len){
    volatile unsigned char *p = buf;
    while(len--) *p++ = 0;
}

void hash(const char *input, uint8_t *output, uint32_t *output_length){
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx){
        perror("EVP_MD_CTX_new failed");
        return;
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1){
        perror("EVP_DigestInit_ex failed");
        EVP_MD_CTX_free(ctx);
        return;
    }

    if (EVP_DigestUpdate(ctx, input, strlen(input)) != 1){
        perror("EVP_DigestUdate failed");
        EVP_MD_CTX_free(ctx);
        return;
    }
    if (EVP_DigestFinal_ex(ctx, output, output_length) != 1){
        perror("EVP_DigestFinal_ex failed");
        EVP_MD_CTX_free(ctx);
        return;
    }
    EVP_MD_CTX_free(ctx);
}

uint8_t *get_pwd(uint32_t *len){
    ssize_t i = 0;

    char *buf = NULL;
    size_t size = 15;

    uint8_t *hashed_pwd = (uint8_t *)malloc(sizeof(uint8_t) * EVP_MAX_MD_SIZE);

    buf = (char *)malloc(sizeof(char) * size);

    if (!buf){
        perror("Realloc");
        free(buf);
        exit(EXIT_FAILURE);
    }

#ifdef _WIN32
    while (1)
    {
        char c = _getch();
        if (i + 1 >= size)
            tmp = realloc(buf, size * 2);
        if (!tmp){
            perror("Realloc");
            free(buf);
            exit(EXIT_FAILURE);
        }

        buf = tmp;

        if (c == '\r' || c == '\n'){
            buf[i] = '\0';
            break;
        }
        buf[i++] = c;
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    if ((i = getline(&buf, &size, stdin)) == -1){
        perror("getline");
        free(buf);
        return NULL;
    }
    if (i > 0 && buf[i - 1] == '\n'){

        buf[i - 1] = '\0';
        i--;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    hash(buf, hashed_pwd, len);
    secure_zero((void *)buf, strlen(buf));
    free(buf);
    return (hashed_pwd);
}

uint8_t *enter_pwd(){
    uint32_t len = 0;
    printf("\t\033[1;31mpasssword:\033[0m");
    return (get_pwd(&len));
}
