#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <openssl/evp.h>

#define MAX_C 100

extern const char delim;

typedef struct{
    char *name;
    char *email;
    char *reference;
    char *index;
    char *sex;
}student_o;


typedef enum{
    m = 0,
    f = 1
}sex_t;

int save_student(const char *path, const char delim, student_o *);

#endif