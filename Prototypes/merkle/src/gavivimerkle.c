#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/gavivimerkle.h"
#include "../includes/queries.h"
#include "../includes/utils.h"

void print_hash_hex(const unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int has_parent(sqlite3 *db, const char *node_hash) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM merkle_tree WHERE left = ? OR right = ?";
    int result = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, node_hash, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, node_hash, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0) > 0;
        }

        sqlite3_finalize(stmt);
    }

    return result;
}

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
    memset(node_hash, 0, sizeof(node_hash));
    memset(parent_hash, 0, sizeof(parent_hash));
    memset(sibling_hash, 0, sizeof(sibling_hash));

    strncpy(node_hash, leaf_hash, 64);
    node_hash[64] = '\0'; // Ensure proper null-termination

    printf("Merkle Proof for %s:\n", node_hash);
    while (fetch_parent_and_sibling(db, node_hash, parent_hash, sibling_hash)) {
        if (sibling_hash[0] == '\0') {
            fprintf(stderr, "❌ Warning: Empty sibling at level, parent hash: %s\n", parent_hash);
        } else {
            printf("Sibling: %s\n", sibling_hash);
        }
        
        strncpy(node_hash, parent_hash, 64);
        node_hash[64] = '\0'; // Ensure parent hash is null-terminated
    }

    printf("🟢 Reached Merkle Root: %s\n", node_hash);
}