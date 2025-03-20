CREATE TABLE IF NOT EXISTS merkle_tree (
    node_hash TEXT PRIMARY KEY,
    left_child TEXT,
    right_child TEXT,
    parent_hash TEXT
);