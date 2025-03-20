#include "gavivimerkle.h"

typedef struct {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    int is_left;
} MerkleProofStep;

int hash_equals(const unsigned char *hash1, const unsigned char *hash2) {
    return memcmp(hash1, hash2, SHA256_DIGEST_LENGTH) == 0;
}

/**
 * get_merkle_proof-
 */
int get_merkle_proof(merkleNode *node, const unsigned char *target_hash, MerkleProofStep *proof, int *depth) {
    if (!node || !target_hash) return 0;

    if (!node->left && !node->right) {
        return hash_equals(node->hash, target_hash);
    }

    if (node->left && get_merkle_proof(node->left, target_hash, proof, depth)) {
        memcpy(proof[*depth].hash, node->right->hash, SHA256_DIGEST_LENGTH);
        proof[*depth].is_left = 1;
        (*depth)++;
        return 1;
    }

    if (node->right && get_merkle_proof(node->right, target_hash, proof, depth)) {
        memcpy(proof[*depth].hash, node->left->hash, SHA256_DIGEST_LENGTH);
        proof[*depth].is_left = 0;
        (*depth)++;
        return 1;
    }
    return 0;
}

int generate_merkle_proof(merkleNode *root, const unsigned char *target_hash, MerkleProofStep *proof) {
    int depth = 0;
    int found = get_merkle_proof(root, target_hash, proof, &depth);
    return found ? depth : 0;
}

void print_merkle_proof(MerkleProofStep *proof, int depth) {
    printf("Merkle Proof (Path to Root):\n");
    for (int i = 0; i < depth; i++) {
        printf("Step %d: Hash = ", i);
        for (int j = 0; j < SHA256_DIGEST_LENGTH; j++)
            printf("%02x", proof[i].hash[j]);
        printf(", Position = %s\n", proof[i].is_left ? "Right" : "Left");
    }
}
