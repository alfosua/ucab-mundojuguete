#ifndef H_MUNDOJUGUETE_STRUCTS_STACK_H
#define H_MUNDOJUGUETE_STRUCTS_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "toy.h"

typedef struct record {
	int id;
	char* datetime;
	char entry_type;
	int quantity;
	struct record *sig;
} record;

void save_stack(toy_t *stack);
void stack_record(toy_t **top, record data);
void load_stack(toy_t *stack);
void print_stack(toy_t *stack);

#endif
