#ifndef _GAVIVIMERKLE_
#define _GAVIVIMERKLE_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#define MAX_VOTERS 1024

#define MAX_HASH_DISPLAY 8  
#define MAX_LEVEL 5

typedef struct merkleNode
{
    uint8_t hash[SHA256_DIGEST_LENGTH];
    struct merkleNode *left, *right;
} merkleNode;

typedef struct {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    int is_left;
} MerkleProofStep;

//utils.c
int load_voter_data(const char *filename, uint8_t voter_hashes[][SHA256_DIGEST_LENGTH]);
void print_hash(uint8_t *hash);
void print_merkle_tree(merkleNode *node, int level, char *prefix);
void print_spaces(int count);
void compute_sha256(const uint8_t *data, size_t len, uint8_t *hash_out);

//merkle.c
void free_merkle_tree(merkleNode *node);
int load_voter_data(const char *filename, uint8_t voter_hashes[][SHA256_DIGEST_LENGTH]);
merkleNode *build_merkle_tree(uint8_t voter_hashes[][SHA256_DIGEST_LENGTH], int num_voters);
merkleNode *create_node(uint8_t *hash, merkleNode *left, merkleNode *right);

//queries.c
int generate_merkle_proof(merkleNode *root, const unsigned char *target_hash, MerkleProofStep *proof);
int hash_equals(const unsigned char *hash1, const unsigned char *hash2);
int generate_merkle_proof(merkleNode *root, const unsigned char *target_hash, MerkleProofStep *proof);
void print_merkle_proof(MerkleProofStep *proof, int depth);

#endif