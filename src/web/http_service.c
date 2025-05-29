#include <string.h>
#include <fiobj.h>
#include "fio_cli.h"
#include "fiobj_mustache.h"
#include "main.h"
#include "../data/db.h"

// web
static void on_http_request(http_s* h);
static void on_finish(http_settings_s *settings);
void initialize_http_service(void);

// utils
int match_route(http_s *request, FIOBJ method, FIOBJ route);
void render_page(http_s* request, const char * page_title, FIOBJ (*layout)(const char * pt, FIOBJ bc), FIOBJ (*page)(http_s *request));
mustache_s* load_mustache_from_file(const char *file_path);

// resources
FIOBJ HTTP_MIMETYPE_TEXT_HTML;
FIOBJ HTTP_METHOD_POST;
FIOBJ HTTP_METHOD_GET;
FIOBJ ROUTE_ROOT;
FIOBJ ROUTE_TOYS;
FIOBJ ROUTE_ORDERS;
FIOBJ ROUTE_INVENTORY;
FIOBJ HASH_KEY_BODY_CONTENT;
FIOBJ HASH_KEY_ID;
FIOBJ HASH_KEY_NEXT_ID;
FIOBJ HASH_KEY_DATETIME;
FIOBJ HASH_KEY_ENTRY_TYPE;
FIOBJ HASH_KEY_ENTRY_TYPE_DESCRIPTION;
FIOBJ HASH_KEY_QUANTITY;
FIOBJ HASH_KEY_TOY_ID;
FIOBJ HASH_KEY_TOY_NAME;
FIOBJ HASH_KEY_PAGE_TITLE;
FIOBJ HASH_KEY_INVENTORY;
FIOBJ HASH_KEY_ORDERS;
FIOBJ HASH_KEY_TOYS;
FIOBJ HASH_KEY_NAME;
FIOBJ HASH_KEY_DESCRIPTION;
FIOBJ HASH_KEY_PRICE;
FIOBJ HASH_KEY_CATEGORY_ID;
FIOBJ HASH_KEY_CATEGORY_DESCRIPTION;
void initialize_http_values();
void cleanup_http_values();

// components
FIOBJ layout_main(const char *page_title, FIOBJ body_content);
FIOBJ page_home(http_s *request);
FIOBJ page_404(http_s *request);
FIOBJ page_toys(http_s *request);
FIOBJ page_inventory(http_s *request);
FIOBJ page_orders(http_s *request);
FIOBJ wc_toy_grid(list_t *target, int next_id);
FIOBJ wc_inventory_grid(toy_t *target, int next_id);
FIOBJ wc_orders_grid(queue_t *target, int next_id);

// actions
void on_post_inventory(http_s *request);
void on_post_order(http_s *request);

/* TODO: edit this function to handle HTTP data and answer Websocket requests.*/
static void on_http_request(http_s* h) {
    if (match_route(h, HTTP_METHOD_GET, ROUTE_ROOT)) {
        render_page(h, "Inicio", layout_main, page_home);
    } else if (match_route(h, HTTP_METHOD_GET, ROUTE_TOYS)) {
        render_page(h, "Juguetes", layout_main, page_toys);
    } else if (match_route(h, HTTP_METHOD_GET, ROUTE_INVENTORY)) {
        render_page(h, "Inventario", layout_main, page_inventory);
    } else if (match_route(h, HTTP_METHOD_POST, ROUTE_INVENTORY)) {
        on_post_inventory(h);
    } else if(match_route(h, HTTP_METHOD_GET, ROUTE_ORDERS)){
        render_page(h, "Pedidos", layout_main, page_orders);
    } else if(match_route(h, HTTP_METHOD_POST, ROUTE_ORDERS)){
        on_post_order(h);
    } else {
        h->status = 404;
        render_page(h, "404", layout_main, page_404);
    }
}

/* starts a listeninng socket for HTTP connections. */
void initialize_http_service(void) {
    /* listen for inncoming connections */
    if (http_listen(fio_cli_get("-p"), fio_cli_get("-b"),
                                       .on_request = on_http_request,
                                       .on_finish = on_finish,
                                       .max_body_size = fio_cli_get_i("-maxbd") * 1024 * 1024,
                                       .ws_max_msg_size = fio_cli_get_i("-max-msg") * 1024,
                                       .public_folder = fio_cli_get("-public"),
                                       .log = fio_cli_get_bool("-log"),
                                       .timeout = fio_cli_get_i("-keep-alive"),
                                       .ws_timeout = fio_cli_get_i("-ping")) == -1) {
        /* listen failed ?*/
        perror("ERROR: facil couldn't initialize HTTP service (already running?)");
        exit(1);
    }
    init_db();
    initialize_http_values();
}

static void on_finish(http_settings_s *settings) {
    cleanup_http_values();
    cleanup_db();
}

void initialize_http_values() {
    HTTP_MIMETYPE_TEXT_HTML = fiobj_str_new("text/html", 9);
    HTTP_METHOD_POST = fiobj_str_new("POST", 4);
    HTTP_METHOD_GET = fiobj_str_new("GET", 3);

    ROUTE_ROOT = fiobj_str_new("/", 1);
    ROUTE_TOYS = fiobj_str_new("/toys", 5);
    ROUTE_ORDERS = fiobj_str_new("/orders", 7);
    ROUTE_INVENTORY = fiobj_str_new("/inventory", 10);
    
    HASH_KEY_BODY_CONTENT = fiobj_str_new("body_content", 12);
    HASH_KEY_ID = fiobj_str_new("id", 2);
    HASH_KEY_NEXT_ID = fiobj_str_new("next_id", 7);
    HASH_KEY_DATETIME = fiobj_str_new("datetime", 8);
    HASH_KEY_ENTRY_TYPE = fiobj_str_new("entry_type", 10);
    HASH_KEY_ENTRY_TYPE_DESCRIPTION = fiobj_str_new("entry_type_description", 22);
    HASH_KEY_QUANTITY = fiobj_str_new("quantity", 8);
    HASH_KEY_TOY_ID = fiobj_str_new("toy_id", 6);
    HASH_KEY_TOY_NAME = fiobj_str_new("toy_name", 8);
    HASH_KEY_PAGE_TITLE = fiobj_str_new("page_title", 10);
    HASH_KEY_INVENTORY = fiobj_str_new("inventory", 9);
    HASH_KEY_ORDERS = fiobj_str_new("orders", 6);
    HASH_KEY_TOYS = fiobj_str_new("toys", 4);
    HASH_KEY_NAME = fiobj_str_new("name", 4);
    HASH_KEY_DESCRIPTION = fiobj_str_new("description", 11);
    HASH_KEY_PRICE = fiobj_str_new("price", 5);
    HASH_KEY_CATEGORY_ID = fiobj_str_new("category_id", 11);
    HASH_KEY_CATEGORY_DESCRIPTION = fiobj_str_new("category_description", 20);
}

void cleanup_http_values() {
    fiobj_free(HTTP_MIMETYPE_TEXT_HTML);
    fiobj_free(HTTP_METHOD_POST);
    fiobj_free(HTTP_METHOD_GET);

    fiobj_free(ROUTE_ROOT);
    fiobj_free(ROUTE_TOYS);
    fiobj_free(ROUTE_ORDERS);
    fiobj_free(ROUTE_INVENTORY);
    
    fiobj_free(HASH_KEY_BODY_CONTENT);
    fiobj_free(HASH_KEY_ID);
    fiobj_free(HASH_KEY_NEXT_ID);
    fiobj_free(HASH_KEY_DATETIME);
    fiobj_free(HASH_KEY_ENTRY_TYPE);
    fiobj_free(HASH_KEY_ENTRY_TYPE_DESCRIPTION);
    fiobj_free(HASH_KEY_QUANTITY);
    fiobj_free(HASH_KEY_TOY_ID);
    fiobj_free(HASH_KEY_TOY_NAME);
    fiobj_free(HASH_KEY_PAGE_TITLE);
    fiobj_free(HASH_KEY_INVENTORY);
    fiobj_free(HASH_KEY_ORDERS);
    fiobj_free(HASH_KEY_TOYS);
    fiobj_free(HASH_KEY_NAME);
    fiobj_free(HASH_KEY_DESCRIPTION);
    fiobj_free(HASH_KEY_PRICE);
    fiobj_free(HASH_KEY_CATEGORY_ID);
    fiobj_free(HASH_KEY_CATEGORY_DESCRIPTION);
}

int match_route(http_s *request, FIOBJ method, FIOBJ route) {
    return fiobj_iseq(request->method, method) && fiobj_iseq(request->path, route);
}

mustache_s *load_mustache_from_file(const char *file_path) {
    fio_str_info_s filename_info = { .data = (char*)file_path, .len = strlen(file_path) };
    mustache_s* template = fiobj_mustache_load(filename_info);
    return template;
}

void render_page(http_s* request, const char * page_title, FIOBJ (*layout)(const char * pt, FIOBJ bc), FIOBJ (*page)(http_s *request)) {
    FIOBJ page_html = page(request);
    FIOBJ rendered_html = layout(page_title, page_html);
    fio_str_info_s rendered_html_info = fiobj_obj2cstr(rendered_html);

    http_set_header(request, HTTP_HEADER_CONTENT_TYPE, HTTP_MIMETYPE_TEXT_HTML);
    http_send_body(request, rendered_html_info.data, rendered_html_info.len);

    fiobj_free(rendered_html);
    fiobj_free(page_html);
}

void on_post_inventory(http_s *request) {
    toy_t *toy = NULL;
    record record_to_add;
    if (http_parse_body(request) == 0) {
        FIOBJ params = request->params;
        if (fiobj_type(params) == FIOBJ_T_HASH) {
            record_to_add.id = atoi(fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_ID)).data);
            record_to_add.datetime = malloc(11);
            strcpy(record_to_add.datetime, fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_DATETIME)).data);
            record_to_add.entry_type = atoi(fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_ENTRY_TYPE)).data);
            record_to_add.quantity = atoi(fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_QUANTITY)).data);
            // Find toy to add the record to
            int toy_id = atoi(fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_TOY_ID)).data);
            toy = get_toy_by_id(toy_id);
        }
    }
    if (toy != NULL) {
        stack_record(&toy, record_to_add);
        inc_inventory_record_next_id();
    }
}

void on_post_order(http_s *request) {
    queue_t *order_queue = get_order_queue();
    order_t new_order;
    if (http_parse_body(request) == 0) {
        FIOBJ params = request->params;
        if (fiobj_type(params) == FIOBJ_T_HASH) {
            new_order.id = atoi(fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_ID)).data);
            new_order.datetime = malloc(11);
            strcpy(new_order.datetime, fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_DATETIME)).data);
            new_order.toy_id = atoi(fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_TOY_ID)).data);
            new_order.quantity = atoi(fiobj_obj2cstr(fiobj_hash_get(params, HASH_KEY_QUANTITY)).data);
        }
    }
    orden(order_queue, new_order);
    inc_order_next_id();
}

FIOBJ layout_main(const char *page_title, FIOBJ body_content) {
    mustache_s* template = load_mustache_from_file("src/mustaches/layout.html.mustache");

    FIOBJ page_title_value = fiobj_str_new(page_title, strlen(page_title));
    
    FIOBJ data = fiobj_hash_new();
    fiobj_hash_set(data, HASH_KEY_BODY_CONTENT, body_content);
    fiobj_hash_set(data, HASH_KEY_PAGE_TITLE, page_title_value);

    FIOBJ rendered_html = fiobj_mustache_build(template, data);

    fiobj_mustache_free(template);
    fiobj_free(data);

    return rendered_html;
}

FIOBJ page_home(http_s *request) {
    mustache_s* template = load_mustache_from_file("src/mustaches/home.html.mustache");
    FIOBJ rendered_html = fiobj_mustache_build(template, NULL);
    fiobj_mustache_free(template);
    return rendered_html;
}

FIOBJ page_404(http_s *request) {
    mustache_s* template = load_mustache_from_file("src/mustaches/404.html.mustache");
    FIOBJ rendered_html = fiobj_mustache_build(template, NULL);
    fiobj_mustache_free(template);
    return rendered_html;
}

FIOBJ page_toys(http_s *request) {
    list_t *toy_list = get_toy_list();
    int next_id = get_toy_next_id();
    return wc_toy_grid(toy_list, next_id);
}

FIOBJ page_inventory(http_s *request) {
    toy_t *toy = NULL;
    http_parse_query(request);
    FIOBJ query = request->params;
    if (fiobj_type(query) == FIOBJ_T_HASH) {
        int toy_id = atoi(fiobj_obj2cstr(fiobj_hash_get(query, HASH_KEY_TOY_ID)).data);
        toy = get_toy_by_id(toy_id);
    }
    if (toy != NULL) {
        int next_id = get_inventory_record_next_id();
        return wc_inventory_grid(toy, next_id);
    } else {
        request->status = 404;
        return page_404(request);
    }
}

FIOBJ page_orders(http_s *request) {
    queue_t *order_queue = get_order_queue();
    int next_id = get_order_next_id();
    return wc_orders_grid(order_queue, next_id);
}

FIOBJ wc_toy_grid(list_t *target, int next_id) {
    mustache_s* template = load_mustache_from_file("src/mustaches/toy-grid.html.mustache");

    FIOBJ data = fiobj_hash_new();
    fiobj_hash_set(data, HASH_KEY_NEXT_ID, fiobj_num_new(next_id));
    
    FIOBJ toys = fiobj_ary_new();
    node_t *current = target->head;
    while (current != NULL) {
        toy_t *current_toy = current->data;
        FIOBJ entry = fiobj_hash_new();
        fiobj_hash_set(entry, HASH_KEY_ID, fiobj_num_new(current_toy->id));
        fiobj_hash_set(entry, HASH_KEY_NAME, fiobj_str_new(current_toy->name, strlen(current_toy->name)));
        fiobj_hash_set(entry, HASH_KEY_DESCRIPTION, fiobj_str_new(current_toy->description, strlen(current_toy->description)));
        fiobj_hash_set(entry, HASH_KEY_PRICE, fiobj_num_new(current_toy->price));
        fiobj_hash_set(entry, HASH_KEY_QUANTITY, fiobj_num_new(current_toy->quantity));
        fiobj_hash_set(entry, HASH_KEY_CATEGORY_ID, fiobj_num_new(current_toy->category_id));
        fiobj_hash_set(entry, HASH_KEY_CATEGORY_DESCRIPTION, fiobj_str_new("Ninguna", strlen("Ninguna")));
        fiobj_ary_push(toys, entry);
        current = current->next;
    }
    fiobj_hash_set(data, HASH_KEY_TOYS, toys);

    FIOBJ rendered_html = fiobj_mustache_build(template, data);

    fiobj_mustache_free(template);
    fiobj_free(data);

    return rendered_html;
}

FIOBJ wc_inventory_grid(toy_t *target, int next_id) {
    mustache_s* template = load_mustache_from_file("src/mustaches/inventory-grid.html.mustache");

    FIOBJ data = fiobj_hash_new();
    fiobj_hash_set(data, HASH_KEY_NEXT_ID, fiobj_num_new(next_id));
    fiobj_hash_set(data, HASH_KEY_TOY_ID, fiobj_num_new(target->id));
    
    FIOBJ inventory = fiobj_ary_new();
    record *current = target->top;
    while (current != NULL) {
        FIOBJ entry = fiobj_hash_new();
        fiobj_hash_set(entry, HASH_KEY_ID, fiobj_num_new(current->id));
        fiobj_hash_set(entry, HASH_KEY_DATETIME, fiobj_str_new(current->datetime, strlen(current->datetime)));
        fiobj_hash_set(entry, HASH_KEY_ENTRY_TYPE, fiobj_num_new(current->entry_type));
        if (current->entry_type == 0) {
            fiobj_hash_set(entry, HASH_KEY_ENTRY_TYPE_DESCRIPTION, fiobj_str_new("Entrada", 7));
        } else {
            fiobj_hash_set(entry, HASH_KEY_ENTRY_TYPE_DESCRIPTION, fiobj_str_new("Salida", 6));
        }
        fiobj_hash_set(entry, HASH_KEY_QUANTITY, fiobj_num_new(current->quantity));
        fiobj_ary_push(inventory, entry);
        current = current->sig;
    }
    fiobj_hash_set(data, HASH_KEY_INVENTORY, inventory);

    FIOBJ rendered_html = fiobj_mustache_build(template, data);

    fiobj_mustache_free(template);
    fiobj_free(data);

    return rendered_html;
}

FIOBJ wc_orders_grid(queue_t *target, int next_id) {
    mustache_s* template = load_mustache_from_file("src/mustaches/order-grid.html.mustache");

    FIOBJ data = fiobj_hash_new();
    fiobj_hash_set(data, HASH_KEY_NEXT_ID, fiobj_num_new(next_id));
    
    FIOBJ orders = fiobj_ary_new();
    order_t *current = target->first;
    while (current != NULL) {
        FIOBJ entry = fiobj_hash_new();
        fiobj_hash_set(entry, HASH_KEY_ID, fiobj_num_new(current->id));
        fiobj_hash_set(entry, HASH_KEY_DATETIME, fiobj_str_new(current->datetime, strlen(current->datetime)));
        fiobj_hash_set(entry, HASH_KEY_TOY_ID, fiobj_num_new(current->toy_id));
        fiobj_hash_set(entry, HASH_KEY_QUANTITY, fiobj_num_new(current->quantity));
        /*
        toy *current_toy = toys->head;
        while (current_toy != NULL) {
            if (current_toy->toy_id == current->toy_id) {
                fiobj_hash_set(entry, HASH_KEY_TOY_NAME, fiobj_str_new(current_toy->name, strlen(current_toy->name)));
                break;
            }
        }
        */
        switch (current->toy_id)
        {
            case 0:
                fiobj_hash_set(entry, HASH_KEY_TOY_NAME, fiobj_str_new("JUGUETE REAL",12));
                break;
            default:
                fiobj_hash_set(entry, HASH_KEY_TOY_NAME, fiobj_str_new("JUGUETE FALSO",13));
                break;
        }
        fiobj_ary_push(orders, entry);
        current = current->sig;
    }
    fiobj_hash_set(data, HASH_KEY_ORDERS, orders);
    
    FIOBJ toys = fiobj_ary_new();
        
    fiobj_hash_set(data, HASH_KEY_TOYS,toys);
    
    FIOBJ real_toy = fiobj_hash_new();
    fiobj_hash_set(real_toy, HASH_KEY_TOY_ID, fiobj_num_new(0));
    fiobj_hash_set(real_toy, HASH_KEY_TOY_NAME, fiobj_str_new("JUGUETE REAL",12));

    fiobj_ary_push(toys,real_toy);
    
    FIOBJ fake_toy = fiobj_hash_new();
    fiobj_hash_set(fake_toy, HASH_KEY_TOY_ID, fiobj_num_new(1));
    fiobj_hash_set(fake_toy, HASH_KEY_TOY_NAME, fiobj_str_new("JUGUETE FALSO",13));

    fiobj_ary_push(toys, fake_toy);

    FIOBJ rendered_html = fiobj_mustache_build(template, data);

    fiobj_mustache_free(template);
    fiobj_free(data);

    return rendered_html;
}
