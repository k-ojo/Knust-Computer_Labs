#include "gavivimerkle.h"
int main()
{
    char *filename = "voters.text";
    uint8_t voter_hashes[MAX_VOTERS][SHA256_DIGEST_LENGTH];
    int num_voters = load_voter_data(filename, voter_hashes);

    if (num_voters == 0)
    {
        fprintf(stderr, "No voter data found!\n");
        return 1;
    }

    printf("Voter Hashes:\n");
    for (int i = 0; i < num_voters; i++)
    {
        print_hash(voter_hashes[i]);
    }

    merkleNode *root = build_merkle_tree(voter_hashes, num_voters);
    printf("\nMerkle Root: ");
    print_hash(root->hash);

    free_merkle_tree(root);
    return (0);

}