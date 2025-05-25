#include "pila.h"

void save_stack(toy_t *stack){
    FILE *f = fopen("stack.sav", "wb");
    record_t* temp = stack->top;
	while(temp!=NULL){
		fwrite(&temp->id,sizeof(int),1,f);
		fwrite(temp->datetime,1,11,f);
		fwrite(&temp->entry_type, 1,1,f);
		fwrite(&temp->quantity,sizeof(int),1,f);
		temp = temp->sig;
	}

	char i=0;
	fwrite(&i,1,1,f);
	fclose(f);
	free(temp);
}

void stack_record(toy_t **top, record_t data) {
	record_t * nuevo = (record_t*)malloc(sizeof(record_t));
	if(nuevo == NULL) {
		printf("la pc de daniela se bugea siempre, comprenme ram vale 52.4$");
		exit(1);}

	nuevo->id = data.id;
	nuevo->datetime = data.datetime;
	nuevo->entry_type = data.entry_type;
	nuevo->quantity = data.quantity;
	nuevo->sig = (*top)->top;

	(*top)->top = nuevo;
	(*top)->quantity = (*top)->quantity + nuevo->quantity;
	
	save_stack(*top);
}

void load_stack(toy_t *stack){
	FILE *f = fopen("stack.sav","rb");

	toy_t* temp = malloc(sizeof(toy_t));
	record_t* entry = (record_t*)malloc(sizeof(record_t));

	for (;;){
		entry->datetime = (char*)malloc(11);
		fread(&entry->id,sizeof(int),1,f);
		if (entry->id == 0){break;}
		fread(entry->datetime,1,11,f);
		fread(&entry->entry_type,1,1,f);
		fread(&entry->quantity,sizeof(int),1,f);
		stack_record(&temp,*entry);
	}
	fclose(f);
	while(temp->top!=NULL){
		stack_record(&stack,*(temp->top));
		temp->top = temp->top->sig;
	}
	
	free(temp);
}

void print_stack(toy_t *stack) {
    record_t* temp = stack->top;
    int i=0;
    while(stack->name[i]!='\0') {
			printf("%c",stack->name[i]);
			i++;
		}i=0;
    printf(" | Stock: %i\n\n", stack->quantity);

	while(temp!=NULL) {
	    printf("[%i] ", temp->id);
		while(temp->datetime[i]!='\0') {
			printf("%c",temp->datetime[i]);
			i++;
		}i=0;
		printf(" - New entry: ");
		if(temp->entry_type==0) {
			printf("In  ");
		} else {
			printf("Out ");
		}

		printf(" | Quantity: %i\n", temp->quantity);

		temp = temp->sig;
	}
	free(temp);
}
