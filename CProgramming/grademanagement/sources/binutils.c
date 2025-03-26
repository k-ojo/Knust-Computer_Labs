#include "binutils.h"

void hex_to_bytes(const char *hex, uint8_t *bytes, size_t bytes_len){
    for (size_t i = 0; i < bytes_len; i++){
        sscanf(hex + 2 * i, "%2hhx", &bytes[i]);
    }
}

void bytes_to_hex(const uint8_t *bytes, size_t bytes_len, char *hex){
    for (size_t i = 0; i < bytes_len; i++){
        sprintf(hex + 2 * i, "%02x", bytes[i]);
    }
    hex[2 * bytes_len] = '\0';
}