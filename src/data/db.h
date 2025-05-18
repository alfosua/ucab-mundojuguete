#ifndef H_MUNDOJUGUETE_DATA_DB_H
#define H_MUNDOJUGUETE_DATA_DB_H

#include "../structs/toy.h"
#include "../structs/cola.h"
#include "../structs/lista.h"
#include "../structs/pila.h"

void init_db();
void cleanup_db();

void cleanup_toy_list();
void cleanup_order_queue();

list_t *get_toy_list();
toy_t *get_toy_by_id(int id);
queue_t *get_order_queue();

int get_toy_next_id();
void inc_toy_next_id();
int get_order_next_id();
void inc_order_next_id();
int get_inventory_record_next_id();
void inc_inventory_record_next_id();

#endif