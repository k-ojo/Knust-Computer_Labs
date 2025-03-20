#include <stdio.h>
#include <sqlite3.h>
#include "../includes/gavivimerkle.h"
#include "../includes/queries.h"

int main() {
    sqlite3 *db;

    
    sqlite3_open("merkle_tree.db", &db);
    create_merkle_table(db); 

    char voter_ids[][65] = {
        "abcdef123456", "789def456789", "112233445566", "998877665544"
    };

    int num_voters = sizeof(voter_ids) / sizeof(voter_ids[0]);

    build_merkle_tree(db, voter_ids, num_voters);

    generate_merkle_proof(db, "abcdef123456");

    sqlite3_close(db);
    return 0;
}

