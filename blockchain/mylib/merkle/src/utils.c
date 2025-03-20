#include "gavivimerkle.h"

void print_spaces(int count) {
    for (int i = 0; i < count; i++)
        printf("    ");
}

void print_merkle_tree(merkleNode *node, int level, char *prefix) {
    if (!node || level > MAX_LEVEL) return;

    char new_prefix[128];
    snprintf(new_prefix, sizeof(new_prefix), "%s│   ", prefix);

    print_merkle_tree(node->right, level + 1, new_prefix);

    print_spaces(level);
    printf("%s├── ", prefix);
    for (int i = 0; i < MAX_HASH_DISPLAY; i++)
        printf("%02x", node->hash[i]);
    printf("\n");

    print_merkle_tree(node->left, level + 1, new_prefix);
}

void print_hash(uint8_t *hash)
{
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");
}

int load_voter_data(const char *filename, uint8_t voter_hashes[][SHA256_DIGEST_LENGTH])
{
    FILE *file = fopen(filename, "r");
    size_t len;

    if (!file)
    {
        perror("Failed to open file");
        return 0;
    }
    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_VOTERS)
    {
        len = strcspn(line, "\n");
        if (line[len] == '\n')
            line[len] = '\0';
        compute_sha256((uint8_t *)line, strlen(line), voter_hashes[count]);
        count++;
    }

    fclose(file);
    return count;
}

void compute_sha256(const uint8_t *data, size_t len, uint8_t *hash_out)
{
    uint32_t hash_len;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx)
    {
        fprintf(stderr, "Failed to create EVP_MD_CTX\n");
        return;
    }
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1)
    {
        fprintf(stderr, "EVP_DigestInit_ex failed\n");
        return;
    }

    if (EVP_DigestUpdate(ctx, data, len) != 1)
    {
        fprintf(stderr, "EVP_DigestUpdate failed\n");
        EVP_MD_CTX_free(ctx);
        return;
    }
    if (EVP_DigestFinal_ex(ctx, hash_out, &hash_len) != 1)
    {
        fprintf(stderr, "EVP_DigestFinal_ex failed\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    EVP_MD_CTX_free(ctx);
}

