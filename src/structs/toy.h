#ifndef H_MUNDOJUGUETE_STRUCTS_TOY_H
#define H_MUNDOJUGUETE_STRUCTS_TOY_H

typedef struct toy_t {
	int id;
	char* name;
	char* description;
	int quantity;
	float price;
	int category_id;
	struct record_t* top;
} toy_t;

#endif
