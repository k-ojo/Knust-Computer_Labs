#ifndef _MAIN
#define _MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdbool.h>

#include "binutils.h"
#include "prints.h"
#include "dbutils.h"
#include "password.h"



#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

uint8_t *get_pwd(uint32_t *size);
typedef enum{
    UNAME = 0,
    FNAME = 1,
    LNAME = 2,
    EMAIL = 3,
    H_PWD = 4
}attr;

#endif