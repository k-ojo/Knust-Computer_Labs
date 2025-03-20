#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "utils.h"

void hash_pair(const char *left, const char *right, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char input[130];
    snprintf(input, sizeof(input), "%s%s", left, right);
    SHA256((unsigned char *)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
}