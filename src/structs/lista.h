#ifndef H_MUNDOJUGUETE_STRUCTS_LIST_H
#define H_MUNDOJUGUETE_STRUCTS_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "toy.h"

typedef struct category_t{
    const char *name;
    int toy_count;
    int *toys;
    struct category_t *before;
    struct category_t *next;
} category_t;

typedef struct list_t{
    category_t *head;
    category_t *tail;
} list_t;

list_t* create_list();
category_t* create_category(const char* name);
category_t *get_category_by_index(list_t* list, int index);
void add_toy_to_category(list_t* list, int category_index, int toy_id);
void insert_at_end(list_t *list, const char *name);

#endif
