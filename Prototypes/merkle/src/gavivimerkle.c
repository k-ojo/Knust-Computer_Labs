#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/gavivimerkle.h"
#include "../includes/queries.h"
#include "../includes/utils.h"

void build_merkle_tree(sqlite3 *db, char voter_ids[][65], int num_voters) {
    char parent_hash[65];

    for (int i = 0; i < num_voters; i += 2) {
        if (i + 1 >= num_voters) {
            strcpy(parent_hash, voter_ids[i]);
        } else {
            hash_pair(voter_ids[i], voter_ids[i + 1], parent_hash);
        }

        insert_node(db, voter_ids[i], "", "");
        insert_node(db, voter_ids[i + 1], "", ""); 
        insert_node(db, parent_hash, voter_ids[i], voter_ids[i + 1]); 
    }
}

void generate_merkle_proof(sqlite3 *db, const char *leaf_hash) {
    char node_hash[65], parent_hash[65], sibling_hash[65];
    strcpy(node_hash, leaf_hash);

    printf("Merkle Proof for %s:\n", node_hash);
    while (fetch_parent_and_sibling(db, node_hash, parent_hash, sibling_hash)) {
        printf("Sibling: %s\n", sibling_hash);
        strcpy(node_hash, parent_hash);
    }
}
