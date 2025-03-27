#ifndef _MAIN
#define _MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <openssl/evp.h>
#include <string.h>



#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

uint8_t *get_pwd(uint32_t *size);
void secure_zero(void *, ssize_t);
void hash(const char *input, uint8_t *output, uint32_t *output_length);

#endif