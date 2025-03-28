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

#define PWD_TRY_TIMES 4

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#define NAME_SIZE 50
void start_up();

typedef enum{
    UNAME = 0,
    FNAME = 1,
    LNAME = 2,
    EMAIL = 3,
    H_PWD = 4
}attr;

typedef enum{
    GREEN = 32,
    WHITE = 30,
    RED = 31
}color;

#endif