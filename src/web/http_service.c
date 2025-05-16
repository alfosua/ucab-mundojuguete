#include "fio_cli.h"
#include "fiobj_mustache.h"
#include "main.h"
#include <string.h>

FIOBJ wc_inventory_grid();

const char* TEMPLATE_FILE = "src/mustaches/layout.html.mustache";

/* TODO: edit this function to handle HTTP data and answer Websocket requests.*/
static void on_http_request(http_s* h) {
    fio_str_info_s filename_info = { .data = (char*)TEMPLATE_FILE, .len = strlen(TEMPLATE_FILE) };
    mustache_s* template = fiobj_mustache_load(filename_info);

    FIOBJ html_mime_type = fiobj_str_new("text/html", 9);
    
    FIOBJ data = fiobj_hash_new();
    
    FIOBJ body_content_key = fiobj_str_new("body_content", 12);
    FIOBJ body_content_value = wc_inventory_grid();
    fiobj_hash_set(data, body_content_key, body_content_value);
    
    const char* page_title = "Home";
    FIOBJ page_title_key = fiobj_str_new("page_title", 10);
    FIOBJ page_title_value = fiobj_str_new(page_title, strlen(page_title));
    fiobj_hash_set(data, page_title_key, page_title_value);

    FIOBJ rendered_html = fiobj_mustache_build(template, data);
    fio_str_info_s rendered_html_info = fiobj_obj2cstr(rendered_html);

    http_set_header(h, HTTP_HEADER_CONTENT_TYPE, html_mime_type);
    http_send_body(h, rendered_html_info.data, rendered_html_info.len);

    fiobj_mustache_free(template);
    fiobj_free(html_mime_type);
    fiobj_free(data);
}

FIOBJ wc_inventory_grid() {
    const char *TEMPLATE_FILE = "src/mustaches/inventory-grid.html.mustache";
    fio_str_info_s filename_info = { .data = (char*)TEMPLATE_FILE, .len = strlen(TEMPLATE_FILE) };
    mustache_s* template = fiobj_mustache_load(filename_info);

    FIOBJ data = fiobj_hash_new();

    FIOBJ inventory = fiobj_ary_new();

    FIOBJ first_entry = fiobj_hash_new();
    fiobj_hash_set(first_entry, fiobj_str_new("id", 2), fiobj_str_new("1", 1));
    fiobj_hash_set(first_entry, fiobj_str_new("datetime", 8), fiobj_str_new("2025-05-15", 10));
    fiobj_hash_set(first_entry, fiobj_str_new("entry_type", 10), fiobj_str_new("In", 2));
    fiobj_hash_set(first_entry, fiobj_str_new("quantity", 8), fiobj_str_new("10", 2));
    fiobj_ary_push(inventory, first_entry);

    FIOBJ second_entry = fiobj_hash_new();
    fiobj_hash_set(second_entry, fiobj_str_new("id", 2), fiobj_str_new("1", 1));
    fiobj_hash_set(second_entry, fiobj_str_new("datetime", 8), fiobj_str_new("2025-05-15", 10));
    fiobj_hash_set(second_entry, fiobj_str_new("entry_type", 10), fiobj_str_new("In", 2));
    fiobj_hash_set(second_entry, fiobj_str_new("quantity", 8), fiobj_str_new("10", 2));
    fiobj_ary_push(inventory, second_entry);

    fiobj_hash_set(data, fiobj_str_new("inventory", 9), inventory);

    FIOBJ rendered_html = fiobj_mustache_build(template, data);

    return rendered_html;
}

/* starts a listeninng socket for HTTP connections. */
void initialize_http_service(void) {
    /* listen for inncoming connections */
    if (http_listen(fio_cli_get("-p"), fio_cli_get("-b"),
                                       .on_request = on_http_request,
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
}
