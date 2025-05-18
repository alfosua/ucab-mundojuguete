#include <stdio.h>
#include <stdlib.h>

typedef struct toy{
	int id;
	char* name;
	char* description;
	int quantity;
	float price;
	int category_id;
}toy;

typedef struct node_t{
    toy *data;
    struct node_t *before;
    struct node_t *next;
}node_t;

typedef struct list_t{
    node_t *head;
    node_t *tail;
}list_t;

node_t* create_node(toy* data){
    node_t *node=malloc(sizeof(node_t));
    node->data=data;
    node->next=NULL;
    node->before=NULL;
    return node;
}

void insert_at_beggining(list_t *list, toy *data){
    node_t *n= create_node(data);
    if (list->head==NULL){
        list->tail=n;
    }else{
        list->head->before=n;
        n->next=list->head;
    }
    list->head=n;
}

void insert_at_final(list_t *list, toy *data){
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

toy* create_toy(){
    toy* toyp=malloc(sizeof(toy));
    toyp->name=malloc(sizeof(char)*1000);
    toyp->description=malloc(sizeof(char)*1000);
    toyp->name[0]='\0';
    toyp->description[0]='\0';
    toyp->id=0;
    toyp->quantity=0;
	toyp->price=0;
	toyp->category_id=0;
    return toyp;
}

int test(){
    list_t *tilin=create_list();
    int bandera=1;
    while (bandera==1){
        printf("id,name,description;int quantity;float price;int category_id\n");
        toy *alfonso=create_toy();
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