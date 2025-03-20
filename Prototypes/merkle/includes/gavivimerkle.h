#ifndef GAVIVIMERKLE_H
#define GAVIVIMERKLE_H

#include <sqlite3.h>

void build_merkle_tree(sqlite3 *db, char voter_ids[][65], int num_voters);
void generate_merkle_proof(sqlite3 *db, const char *leaf_hash);

#endif
