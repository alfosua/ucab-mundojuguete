#include "lista.h"
#include <string.h>

list_t* create_list() {
    list_t* list=malloc(sizeof(list_t));
    list->head=NULL;
    list->tail=NULL;
    return list;
}

category_t* create_category(const char* name) {
    category_t *node=malloc(sizeof(category_t));
    node->toy_count = 0;
    node->toys = NULL;
    node->name=malloc(100);
    strcpy(node->name, name);
    node->next=NULL;
    node->before=NULL;
    return node;
}

category_t *get_category_by_index(list_t* list, int index) {
    if (list == NULL || index < 0) {
        return NULL;
    }

    category_t *current = list->head;
    int current_index = 0;

    while (current != NULL && current_index < index) {
        current = current->next;
        current_index++;
    }

    if (current_index < index) {
        return NULL;
    }

    return current;
}

void add_toy_to_category(list_t* list, int category_index, int toy_id) {
    category_t *category = get_category_by_index(list, category_index);

    if (category == NULL) {
        return;
    }
    
    category->toy_count++;

    int *new_toys = realloc(category->toys, category->toy_count * sizeof(int));

    if (new_toys == NULL) {
        category->toy_count--;
        return;
    }

    category->toys = new_toys;
    category->toys[category->toy_count - 1] = toy_id;
}

void insert_at_end(list_t *list, const char *name){
    category_t *n= create_category(name);
    if (list->head==NULL){
        list->head=n;
    }else{
        list->tail->next=n;
        n->before=list->tail;
    }
    list->tail=n;
}
