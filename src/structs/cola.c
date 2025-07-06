#include "cola.h"

queue_t *create_queue() {
    queue_t *queue = malloc(sizeof(queue_t));
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

void orden(queue_t *cola, order_t data) {
    order_t* new_order = (order_t*)malloc(sizeof(order_t));
    if (new_order == NULL) {
        printf("Error");
        exit(1);
    }
    
    new_order->id = data.id;
    new_order->quantity = data.quantity;
    new_order->toy_id = data.toy_id;
    new_order->datetime = data.datetime;
    new_order->sig = NULL;
    
    if (cola->first == NULL) {
        cola->first = new_order;
    } else {
        cola->last->sig = new_order;
    }
    cola->last = new_order;
}

void detele_orden(queue_t *cola) {
    if (cola->first == NULL) {
        printf("No hay orden que eliminar");
        exit(1);
    }
    order_t* temp = cola->first;
    cola->first = cola->first->sig;
    if (cola->first == NULL) {
        cola->last = NULL;
    }
    free(temp);
}

void show_orden(queue_t* cola) {
    order_t* aux = cola->first;
    while(aux != NULL) {
        printf("ID: %d\tJuguete: %d\tCantidad: %d\tFecha/Hora: %s\n",
               aux->id, aux->toy_id, aux->quantity, aux->datetime);
        aux = aux->sig;
    }
}
