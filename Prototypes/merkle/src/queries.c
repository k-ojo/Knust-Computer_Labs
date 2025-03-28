#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdbool.h>
#include "queries.h"

void insert_node(sqlite3 *db, const char *node_hash, const char *left_child, const char *right_child) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO merkle_tree (node_hash, left_child, right_child) VALUES (?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "❌ SQL Error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, node_hash, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, left_child, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, right_child, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "❌ ERROR inserting node %s\n", node_hash);
    } else {
        printf("✅ Inserted Node: %s | Left: %s | Right: %s\n", node_hash, left_child, right_child);
    }

    sqlite3_finalize(stmt);

    // Update parent for child nodes if they exist
    if (strlen(left_child) > 0) update_parent_hash(db, left_child, node_hash);
    if (strlen(right_child) > 0) update_parent_hash(db, right_child, node_hash);
}

void update_parent_hash(sqlite3 *db, const char *child_hash, const char *parent_hash) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE merkle_tree SET parent_hash = ? WHERE node_hash = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "❌ SQL Error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, parent_hash, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, child_hash, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "❌ ERROR updating parent for node %s\n", child_hash);
    } else {
        printf("✅ Updated Parent: %s -> %s\n", child_hash, parent_hash);
    }

    sqlite3_finalize(stmt);
}

void create_merkle_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS merkle_tree ("
                      "node_hash TEXT PRIMARY KEY, "
                      "left_child TEXT, "
                      "right_child TEXT, "
                      "parent_hash TEXT, "
                      "is_root INTEGER DEFAULT 0);";  // Add root flag

    char *err_msg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "❌ ERROR Creating Table: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("✅ Merkle Tree Table Ready\n");
    }
}

bool fetch_parent_and_sibling(sqlite3 *db, const char *node_hash, char *parent_hash, char *sibling_hash) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT parent_hash, left_child, right_child FROM merkle_tree WHERE left_child = ? OR right_child = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "❌ SQL Error: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_bind_text(stmt, 1, node_hash, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, node_hash, -1, SQLITE_STATIC);

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *parent = (const char *)sqlite3_column_text(stmt, 0);
        const char *left = (const char *)sqlite3_column_text(stmt, 1);
        const char *right = (const char *)sqlite3_column_text(stmt, 2);

        if (parent) {
            strncpy(parent_hash, parent, 64);
            parent_hash[64] = '\0'; // Ensure null-termination
        } else {
            parent_hash[0] = '\0'; // No parent case
        }

        sibling_hash[0] = '\0';  // Ensure sibling is always initialized

        if (left && strcmp(left, node_hash) == 0) {
            if (right) {
                strncpy(sibling_hash, right, 64);
                sibling_hash[64] = '\0';
            }
        } else if (right && strcmp(right, node_hash) == 0) {
            if (left) {
                strncpy(sibling_hash, left, 64);
                sibling_hash[64] = '\0';
            }
        }

        if (sibling_hash[0] == '\0') {
            fprintf(stderr, "❌ Warning: Sibling is empty at level with parent %s\n", parent_hash);
        }

        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}