#include <stdio.h>
#include <stdlib.h>

typedef struct order {
    int id;
    char* toy_name;
    int quantity;
    char* datetime;
    struct order* sig;
}order;

typedef struct elemento {
    order* first;
    order* last;
}elemento;

void crear_order(id, toy_name, quantity, datetime) {
    order* new_order = (order*)malloc(sizeof(order));
    if (new_order == NULL) {
        printf("Error");
        exit(1);
    }
    new_order->id = id;
    new_order->toy_name = toy_name;
    new_order->quantity = quantity;
    new_order->datetime = datetime;
    new_order->sig = NULL;
    return new_order;
}

void agregar_order(elemento* cola, order* new_order) {
    if (cola->first == NULL) {
        cola->first = new_order;
    } else {
        cola->last->sig = new_order;
    }
    cola->last = new_order;
}

//:v