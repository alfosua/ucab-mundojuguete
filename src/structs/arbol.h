#include "toy.h"

typedef struct tree_node_t {
    int key;
    toy_t* data;
    struct tree_node_t *left;
    struct tree_node_t *right;
} tree_node_t;

typedef struct tree_t {
    tree_node_t *root;
} tree_t;

tree_t *create_tree();
tree_node_t *create_tree_node(toy_t* data);
int height(tree_node_t *node);
int balance(tree_node_t *node);
void add_node(tree_t *tree, toy_t* data);
int add_child(tree_node_t *parent, toy_t* data);
int insert_child(tree_node_t **target, toy_t* data);
toy_t* search_data(tree_node_t *root, int key);
tree_node_t *rebalance_node(tree_node_t *current);
tree_node_t *rotate_left(tree_node_t *current);
tree_node_t *rotate_right(tree_node_t *current);
tree_node_t *rotate_left_right(tree_node_t *current);
tree_node_t *rotate_right_left(tree_node_t *current);
