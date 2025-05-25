#ifndef H_MUNDOJUGUETE_STRUCTS_STACK_H
#define H_MUNDOJUGUETE_STRUCTS_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "toy.h"

typedef struct record_t {
	int id;
	char* datetime;
	char entry_type;
	int quantity;
	struct record_t *sig;
} record_t;

void save_stack(toy_t *stack);
void stack_record(toy_t **top, record_t data);
void load_stack(toy_t *stack);
void print_stack(toy_t *stack);

#endif
