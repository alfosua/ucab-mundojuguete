#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arbol.h"

tree_t *create_tree() {
    tree_t *tree = malloc(sizeof(tree_t));
    tree->root = NULL;
    return tree;
}

tree_node_t *create_tree_node(toy_t* data) {
    tree_node_t *node = malloc(sizeof(tree_node_t));
    node->key = data->id;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void add_node(tree_t *tree, toy_t* data) {
    if (tree->root == NULL) {
        tree->root = create_tree_node(data);
    } else {
        int ret = add_child(tree->root, data);
        if (ret == 1) {
            tree->root = rebalance_node(tree->root);
        }
    }
}

int add_child(tree_node_t *parent, toy_t* data) {
    if (data->id < parent->data->id) {
        return insert_child(&parent->left, data);
    } else if (data->id > parent->data->id) {
        return insert_child(&parent->right, data);
    }
    return 0;
}

int insert_child(tree_node_t **current, toy_t* data) {
    if (*current == NULL) {
        *current = create_tree_node(data);
        return 1;
    } else {
        int ret = add_child(*current, data);
        if (ret == 1) {
            *current = rebalance_node(*current);
        }
        return ret;
    }
}

tree_node_t *rebalance_node(tree_node_t *current) {
    int fb = balance(current);

    if (fb >= 2) {
        int inner_fb = current->left != NULL
            ? balance(current->left)
            : 0;
        if (inner_fb >= 0) {
            return rotate_right(current);
        } else {
            return rotate_left_right(current);
        }
    }

    if (fb <= -2) {
        int inner_fb = current->right != NULL
            ? balance(current->right)
            : 0;
        if (inner_fb <= 0) {
            return rotate_left(current);
        } else {
            return rotate_right_left(current);
        }
    }

    return current;
}

tree_node_t *rotate_right(tree_node_t *current) {
    tree_node_t *new_root = current->left;
    current->left = new_root->right;
    new_root->right = current;
    return new_root;
}

tree_node_t *rotate_left(tree_node_t *current) {
    tree_node_t *new_root = current->right;
    current->right = new_root->left;
    new_root->left = current;
    return new_root;
}

tree_node_t *rotate_left_right(tree_node_t *current) {
    current->left = rotate_left(current->left);
    return rotate_right(current);
}

tree_node_t *rotate_right_left(tree_node_t *current) {
    current->right = rotate_right(current->right);
    return rotate_left(current);
}

int height(tree_node_t *node) {
    if (node == NULL) {
        return -1;
    }
    
    int left_height = height(node->left) + 1;
    int right_height = height(node->right) + 1;

    if (left_height > right_height) {
        return left_height;
    } else {
        return right_height;
    }
}

int balance(tree_node_t *node) {
    return height(node->left) - height(node->right);
}

toy_t* search_data(tree_node_t *root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key == key) {
        return root->data;
    } else if (key > root->key) {
        return search_data(root->right, key);
    } else {
        return search_data(root->left, key);
    }
}

void print_inorder(tree_node_t *parent, int tailing) {
    if (parent == NULL) {
        return;
    }
    print_inorder(parent->left, tailing);
    printf("{ id: %d, name: \"%s\" }\n", parent->data->id, parent->data->name);
    print_inorder(parent->right, 1);
}

void print_preorder(tree_node_t *parent, int tailing) {
    if (parent == NULL) {
        return;
    }
    printf("{ id: %d, name: \"%s\" }\n", parent->data->id, parent->data->name);
    print_inorder(parent->left, tailing);
    print_inorder(parent->right, 1);
}

int test_tree() {
    tree_t *toy_tree = create_tree();

    toy_t *toy_1 = create_toy();
    toy_1->id = 1;
    strcpy(toy_1->name, "Doom Slayer (DOOM: The Dark Ages) 7\" Figure McFarlane Elite Edition #1");
    strcpy(toy_1->description, "SKU: Doom-The-Dark-Ages-Doom-Slayer-MEE1-3 | UPC: 787926111590| MPN: 11159");
    toy_1->price = 59.99f;
    toy_1->category_id = 1;
    add_node(toy_tree, toy_1);

    toy_t *toy_2 = create_toy();
    toy_2->id = 2;
    strcpy(toy_2->name, "Bloodaxe w/Horse (Spawn: The Dark Ages) 7\" Figure 2-Pack w/McFarlane Toys Digital Collectible");
    strcpy(toy_2->description, "SKU: Spawn-Bloodaxe-w-Horse-2-Pk-w-MCF-Digital-Collectible-52 | UPC: 787926902211 | MPN: 90221");
    toy_2->price = 69.99f;
    toy_2->category_id = 2;
    add_node(toy_tree, toy_2);

    toy_t *toy_3 = create_toy();
    toy_3->id = 3;
    strcpy(toy_3->name, "Batman (The Batman) 7\" Figure");
    strcpy(toy_3->description, "SKU: DC-The-Batman-W1-Batman-68 | UPC: 787926150766 | MPN: 15076");
    toy_3->price = 19.99f;
    toy_3->category_id = 3;
    add_node(toy_tree, toy_3);

    toy_t *toy_4 = create_toy();
    toy_4->id = 4;
    strcpy(toy_4->name, "Venom (Venom #5) 1:6th Scale Collectible Figure w/Scene & Comic");
    strcpy(toy_4->description, "SKU: Marvel-Venom-5-Venom-25 | UPC: 787926147971 | MPN: 14797");
    toy_4->price = 49.99f;
    toy_4->category_id = 1;
    add_node(toy_tree, toy_4);

    toy_t *toy_5 = create_toy();
    toy_5->id = 5;
    strcpy(toy_5->name, "Spider-Man (Miles Morales: Spider-Man #1) 1:10th Scale Collectible Figure w/Scene");
    strcpy(toy_5->description, "SKU: Marvel-MMSP1-Spider-Man-11 | UPC: 787926147780 | MPN: 14778");
    toy_5->price = 11.99f;
    toy_5->category_id = 1;
    add_node(toy_tree, toy_5);

    print_inorder(toy_tree->root, 0);
    printf("\n");
    return 0;
}
