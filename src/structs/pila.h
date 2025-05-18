#include <stdio.h>
#include <stdlib.h>

typedef struct toy {
	int id;
	char* name;
	char* description;
	int quantity;
	float price;
	int category_id;
	struct record* top;
	struct record* inicio;
} toy;

typedef struct record {
	int id;
	char* datetime;
	char entry_type;
	int quantity;
	struct record *sig;
	struct record *ant;
} record;

void save_stack(toy *stack){
    FILE *f = fopen("stack.sav", "wb");
    
    record* temp = stack->top;
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

void stack_record(toy **top, record data) {
	record * nuevo = (record*)malloc(sizeof(record));
	if(nuevo == NULL) {
		printf("la pc de daniela se bugea siempre, comprenme ram vale 52.4$");
		exit(1);
	}if ((*top)->top!=NULL){
		(*top)->inicio = nuevo;
		(*top)->top->ant = nuevo;}

	nuevo->id = data.id;
	nuevo->datetime = data.datetime;
	nuevo->entry_type = data.entry_type;
	nuevo->quantity = data.quantity;
	nuevo->sig = (*top)->top;
	nuevo->ant = NULL;

	(*top)->top = nuevo;
	(*top)->quantity = (*top)->quantity + nuevo->quantity;
	
	save_stack(*top);
}

// no sirve odio todo
void load_stack(toy *stack){
	FILE *f = fopen("stack.sav","rb");

	record* entry = (record*)malloc(sizeof(record));

	for (;;){ //dejaem probar esto
		entry->datetime = (char*)malloc(11);
		fread(&entry->id,sizeof(int),1,f);
		if (entry->id == 0){break;}
		fread(entry->datetime,1,11,f);
		fread(&entry->entry_type,1,1,f);
		fread(&entry->quantity,sizeof(int),1,f);
		stack_record(&stack,*entry);
	}
	fclose(f);
}

void print_stack(toy *stack) {
    record* temp = stack->top;
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