#ifndef _BINUTILS
#define _BINUTILS

#include "main.h"

void hex_to_bytes(const char *hex, uint8_t *bytes, size_t bytes_len);
void bytes_to_hex(const uint8_t *bytes, size_t bytes_len, char *hex);

#endif