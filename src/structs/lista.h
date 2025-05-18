#include "toy.h"
typedef struct node_t{
    toy *data;
    struct node_t *before;
    struct node_t *next;
}node_t;

typedef struct list_t{
    node_t *head;
    node_t *tail;
}list_t;

void insert_at_beggining(list_t *list, toy *data){
    node_t *n= malloc(sizeof(node_t));
    n->data=data;
    n->before=NULL;
    if (list->head==NULL){
        list->tail=n;
    }else{
        list->head->next=n;
    }
    list->head=n;
}

void insert_at_final(list_t *list, toy *data){
    node_t *n= malloc(sizeof(node_t));
    n->data=data;
    n->next=NULL;
    if (list->head==NULL){
        list->head=n;
    }else{
        list->tail->next=n;
    }
    list->tail=n;
}