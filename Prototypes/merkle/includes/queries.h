#ifndef QUERIES_H
#define QUERIES_H

#include <sqlite3.h>
#include <stdbool.h>


void insert_node(sqlite3 *db, const char *node_hash, const char *left, const char *right);
bool fetch_parent_and_sibling(sqlite3 *db, const char *node_hash, char *parent_hash, char *sibling_hash);
void create_merkle_table(sqlite3 *db);
void update_parent_hash(sqlite3 *db, const char *child_hash, const char *parent_hash);

#endif
