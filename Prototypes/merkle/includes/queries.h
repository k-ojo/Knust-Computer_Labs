#ifndef QUERIES_H
#define QUERIES_H

#include <sqlite3.h>
#include <stdbool.h>

// Function prototypes
void insert_node(sqlite3 *db, const char *node_hash, const char *left_child, const char *right_child);
void update_parent_hash(sqlite3 *db, const char *child_hash, const char *parent_hash);
void create_merkle_table(sqlite3 *db);
bool fetch_parent_and_sibling(sqlite3 *db, const char *node_hash, char *parent_hash, char *sibling_hash);

#endif
