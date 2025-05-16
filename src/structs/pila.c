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
} toy;

typedef struct record {
    int id;
    char* datetime;
    char entry_type;
    int quantity;
    struct toy *sig;
} record;

void stack_record(toy **top, record data){
    record * nuevo = (record*)malloc(sizeof(record));
    if(nuevo == NULL){printf("la pc de daniela se bugea siempre, comprenme ram vale 52.4$"); exit(1);}
    
    nuevo->id = data.id;
    nuevo->datetime = data.datetime;
    nuevo->entry_type = data.entry_type;
    nuevo->quantity = data.quantity;
    nuevo->sig = *top;
    
    (*top)->top = nuevo;
    (*top)->quantity = (*top)->quantity + nuevo->quantity;
    
    
    /*if(nuevo->entry_type==0){
        printf("In ");
    }else{printf("Out ");}
    
    int i=0;
    while(nuevo->datetime[i]!='\0'){
        printf("%c",nuevo->datetime[i]);
        i++;
    }i=0;
    
    printf(" - [ID%i] New entry: ", nuevo->id);
    
    while((*top)->name[i]!='\0'){
        printf("%c",(*top)->name[i]);
        i++;
    }printf(" | Quantity: %i", nuevo->quantity);
    printf(" | Stock: %i\n", (*top)->quantity);*/
    
}