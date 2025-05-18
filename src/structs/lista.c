#include "lista.h"

node_t* create_node(toy_t* data){
    node_t *node=malloc(sizeof(node_t));
    node->data=data;
    node->next=NULL;
    node->before=NULL;
    return node;
}

void insert_at_beggining(list_t *list, toy_t *data){
    node_t *n= create_node(data);
    if (list->head==NULL){
        list->tail=n;
    }else{
        list->head->before=n;
        n->next=list->head;
    }
    list->head=n;
}

void insert_at_final(list_t *list, toy_t *data){
    node_t *n= create_node(data);
    if (list->head==NULL){
        list->head=n;
    }else{
        list->tail->next=n;
        n->before=list->tail;
    }
    list->tail=n;
}

void print_list_start_end(list_t *list){
    node_t *current= list->head;
    while (current!=NULL){
        printf("Start to end\n");
        printf("ID: %d\n",current->data->id);
        printf("Name: %s\n",current->data->name);
        printf("Description: %s\n",current->data->description);
        printf("Quantity: %d\n",current->data->quantity);
        printf("Price: %f\n",current->data->price);
        printf("Category id: %d\n",current->data->category_id);
        printf("-----------\n");
        current=current->next;
    }
}

void print_list_end_start(list_t *list){
    node_t *current= list->tail;
    while (current!=NULL){
        printf("End to start\n");
        printf("Category id: %d\n",current->data->category_id);
        printf("Price: %f\n",current->data->price);
        printf("Quantity: %d\n",current->data->quantity);
        printf("Description: %s\n",current->data->description);
        printf("Name: %s\n",current->data->name);
        printf("ID: %d\n",current->data->id);
        printf("-----------\n");
        current=current->before;
    }
}


list_t* create_list(){
    list_t* list=malloc(sizeof(list_t));
    list->head=NULL;
    list->tail=NULL;
    return list;
}

toy_t* create_toy(){
    toy_t* toy=malloc(sizeof(toy_t));
    toy->name=malloc(sizeof(char)*1000);
    toy->description=malloc(sizeof(char)*1000);
    toy->name[0]='\0';
    toy->description[0]='\0';
    toy->id=0;
    toy->quantity=0;
	toy->price=0;
	toy->category_id=0;
    toy->top=NULL;
    toy->inicio=NULL;
    return toy;
}

int test_list(){
    list_t *tilin=create_list();
    int bandera=1;
    while (bandera==1){
        printf("id,name,description;int quantity;float price;int category_id\n");
        toy_t *alfonso=create_toy();
        scanf("%d", &alfonso->id);
        scanf("%s", alfonso->name);
        scanf("%s", alfonso->description);
        scanf("%d", &alfonso->quantity);
        scanf("%f", &alfonso->price);
        scanf("%d", &alfonso->category_id);
        printf("donde?\n");
        scanf("%d", &bandera);
        if (bandera==0){
            insert_at_beggining(tilin,alfonso);
        }else{
            insert_at_final(tilin,alfonso);
            }
        printf("alfonsini?\n");
        scanf("%d", &bandera);
    }
    print_list_start_end(tilin);
    print_list_end_start(tilin);
    return 0;
}
