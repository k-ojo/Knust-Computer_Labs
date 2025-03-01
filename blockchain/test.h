#ifndef _TEST_
#define _TEST_

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define HASH_SIZE 32

typedef struct{
    /* data */
    int data;
}transaction_t;

typedef struct{
    uint8_t prev_hash[HASH_SIZE];
    uint32_t nonce;
    time_t timestamp;
    uint8_t merkle_root[HASH_SIZE];
}header_t;

typedef struct{
    header_t header;
    transaction_t *transactions;
}block_t;



#endif