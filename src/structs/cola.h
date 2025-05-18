#ifndef H_MUNDOJUGUETE_STRUCTS_QUEUE_H
#define H_MUNDOJUGUETE_STRUCTS_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct order_t {
    int id;
    int toy_id;
    int quantity;
    char* datetime;
    struct order_t* sig;
} order_t;

typedef struct queue_t {
    order_t* first;
    order_t* last;
} queue_t;

queue_t *create_queue();
void orden(queue_t *cola, order_t data);
void detele_orden(queue_t *cola);
void show_orden(queue_t* cola);

#endif
