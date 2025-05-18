#ifndef H_MUNDOJUGUETE_STRUCTS_LIST_H
#define H_MUNDOJUGUETE_STRUCTS_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "toy.h"

typedef struct node_t{
    toy_t *data;
    struct node_t *before;
    struct node_t *next;
} node_t;

typedef struct list_t{
    node_t *head;
    node_t *tail;
} list_t;

toy_t* create_toy();
list_t* create_list();
node_t* create_node(toy_t* data);
void insert_at_beggining(list_t *list, toy_t *data);
void insert_at_final(list_t *list, toy_t *data);
void print_list_start_end(list_t *list);
void print_list_end_start(list_t *list);

#endif
