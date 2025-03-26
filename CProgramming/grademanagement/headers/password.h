#ifndef _PASSWORD
#define _PASSWORD

#include "main.h"

void clearConsole();
void secure_zero(void *buf, ssize_t len);
void hash(const char *input, uint8_t *output, uint32_t *output_length);
uint8_t *get_pwd(uint32_t *len);
uint8_t *enter_pwd();

#endif