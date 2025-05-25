#include <stdlib.h>
#include <string.h>
#include "db.h"

// global data
list_t *toy_list;
queue_t *order_queue;

// id counters
int toy_next_id = 1;
int record_next_id = 1;
int order_next_id = 1;

void init_db() {
    toy_list = create_list();
    order_queue = create_queue();

    toy_t *toy_1 = create_toy();
    toy_1->id = 1;
    strcpy(toy_1->name, "Doom Slayer (DOOM: The Dark Ages) 7\" Figure McFarlane Elite Edition #1");
    strcpy(toy_1->description, "SKU: Doom-The-Dark-Ages-Doom-Slayer-MEE1-3 | UPC: 787926111590| MPN: 11159");
    toy_1->price = 59.99f;
    toy_1->category_id = 1;
    insert_at_final(toy_list, toy_1);

    toy_t *toy_2 = create_toy();
    toy_2->id = 2;
    strcpy(toy_2->name, "Bloodaxe w/Horse (Spawn: The Dark Ages) 7\" Figure 2-Pack w/McFarlane Toys Digital Collectible");
    strcpy(toy_2->description, "SKU: Spawn-Bloodaxe-w-Horse-2-Pk-w-MCF-Digital-Collectible-52 | UPC: 787926902211 | MPN: 90221");
    toy_2->price = 69.99f;
    toy_2->category_id = 2;
    insert_at_final(toy_list, toy_2);

    toy_t *toy_3 = create_toy();
    toy_3->id = 3;
    strcpy(toy_3->name, "Batman (The Batman) 7\" Figure");
    strcpy(toy_3->description, "SKU: DC-The-Batman-W1-Batman-68 | UPC: 787926150766 | MPN: 15076");
    toy_3->price = 19.99f;
    toy_3->category_id = 3;
    insert_at_final(toy_list, toy_3);

    toy_t *toy_4 = create_toy();
    toy_4->id = 4;
    strcpy(toy_4->name, "Venom (Venom #5) 1:6th Scale Collectible Figure w/Scene & Comic");
    strcpy(toy_4->description, "SKU: Marvel-Venom-5-Venom-25 | UPC: 787926147971 | MPN: 14797");
    toy_4->price = 49.99f;
    toy_4->category_id = 1;
    insert_at_final(toy_list, toy_4);

    toy_t *toy_5 = create_toy();
    toy_5->id = 5;
    strcpy(toy_5->name, "Spider-Man (Miles Morales: Spider-Man #1) 1:10th Scale Collectible Figure w/Scene");
    strcpy(toy_5->description, "SKU: Marvel-MMSP1-Spider-Man-11 | UPC: 787926147780 | MPN: 14778");
    toy_5->price = 11.99f;
    toy_5->category_id = 1;
    insert_at_final(toy_list, toy_5);
}

void cleanup_db() {
    // cleanup_toy_list();
    // cleanup_order_queue();
}

void cleanup_toy_list() {
    node_t *current_toy = toy_list->head;
    while (current_toy != NULL) {
        node_t *temp_toy = current_toy;
        current_toy = current_toy->next;
        record_t *current_record = current_toy->data->top;
        while (current_record != NULL) {
            record_t *temp_record = current_record;
            current_record = current_record->sig;
            free(temp_record->datetime);
            free(temp_record);
        }
        free(temp_toy->data->name);
        free(temp_toy->data->description);
        free(temp_toy->data);
        free(temp_toy);
    }
    free(toy_list);
}

void cleanup_order_queue() {
    order_t *current_order = order_queue->first;
    while (current_order != NULL) {
        order_t *temp_order = current_order;
        current_order = current_order->sig;
        free(temp_order->datetime);
    }
    free(order_queue);
}

list_t *get_toy_list() {
    return toy_list;
}

toy_t *get_toy_by_id(int id) {
    node_t *current_toy = toy_list->head;
    while (current_toy != NULL) {
        if (current_toy->data->id == id) {
            return current_toy->data;
        }
        current_toy = current_toy->next;
    }
    return NULL;
}

queue_t *get_order_queue() {
    return order_queue;
}

int get_toy_next_id() { return toy_next_id; }
void inc_toy_next_id() { toy_next_id++; }
int get_order_next_id() { return order_next_id; }
void inc_order_next_id() { order_next_id++; }
int get_inventory_record_next_id() { return record_next_id; }
void inc_inventory_record_next_id() { record_next_id++; }
