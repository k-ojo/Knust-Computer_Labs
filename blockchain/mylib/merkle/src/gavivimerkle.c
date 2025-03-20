#include "gavivimerkle.h"


merkleNode *create_node(uint8_t *hash, merkleNode *left, merkleNode *right)
{
    merkleNode *node = (merkleNode *)malloc(sizeof(merkleNode));

    if (!node)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    if (hash)
        memcpy(node->hash, hash, SHA256_DIGEST_LENGTH);
    node->left = left;
    node->right = right;
    return node;
}

merkleNode *build_merkle_tree(uint8_t voter_hashes[][SHA256_DIGEST_LENGTH], int num_voters)
{
    if (num_voters == 0)
        return NULL;

    merkleNode **nodes = malloc(num_voters * sizeof(merkleNode *));
    for (int i = 0; i < num_voters; i++)
    {
        nodes[i] = create_node(voter_hashes[i], NULL, NULL);
    }

    while (num_voters > 1)
    {
        int new_size = (num_voters + 1) / 2;
        merkleNode **new_nodes = malloc(new_size * sizeof(merkleNode *));

        for (int i = 0; i < new_size; i++)
        {
            merkleNode *left = nodes[i * 2];
            merkleNode *right; // = (i * 2 + 1 < num_voters) ? nodes[i * 2 + 1] : left;
            if (i * 2 + 1 < num_voters){
                right = nodes[i * 2 + 1];
            }
            else{
                right = create_node(left->hash, NULL, NULL);
            }

            uint8_t combined[2 * SHA256_DIGEST_LENGTH];
            memcpy(combined, left->hash, SHA256_DIGEST_LENGTH);
            memcpy(combined + SHA256_DIGEST_LENGTH, right->hash, SHA256_DIGEST_LENGTH);

            uint8_t new_hash[SHA256_DIGEST_LENGTH];
            compute_sha256(combined, sizeof(combined), new_hash);
            new_nodes[i] = create_node(new_hash, left, right);
        }

        free(nodes);
        nodes = new_nodes;
        num_voters = new_size;
    }

    merkleNode *root = nodes[0]; //(merkleNode *)malloc(sizeof(merkleNode));
    // root = nodes[0];
    free(nodes);
    return root;
}

void free_merkle_tree(merkleNode *node)
{
    if (!node)
        return;
    free_merkle_tree(node->left);
    free_merkle_tree(node->right);
    free(node);
}