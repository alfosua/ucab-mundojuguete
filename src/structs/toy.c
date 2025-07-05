#include "stdlib.h"
#include "toy.h"

toy_t* create_toy(){
    toy_t* toy=malloc(sizeof(toy_t));
    toy->name=malloc(sizeof(char)*1000);
    toy->description=malloc(sizeof(char)*1000);
    toy->name[0]='\0';
    toy->description[0]='\0';
    toy->id=0;
    toy->quantity=0;
    toy->price=0;
    toy->category_id=-1;
    toy->top=NULL;
    return toy;
}