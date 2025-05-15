#include "fio_cli.h"
#include "fiobj_mustache.h"
#include "main.h"

const char *TEMPLATE_FILE = "src/mustaches/layout.html.mustache";

/* TODO: edit this function to handle HTTP data and answer Websocket requests.*/
static void on_http_request(http_s *h) {
  fio_str_info_s filename_info = {.data = (char *)TEMPLATE_FILE, .len = strlen(TEMPLATE_FILE)};
  mustache_s *template = fiobj_mustache_load(filename_info);

  FIOBJ data = fiobj_hash_new();
  FIOBJ name_key = fiobj_str_new("name", 4);
  FIOBJ name_value = fiobj_str_new("User", 4); // Changed the name slightly
  fiobj_hash_set(data, name_key, name_value);

  FIOBJ rendered_html = fiobj_mustache_build(template, data);
  fio_str_info_s rendered_html_info = fiobj_obj2cstr(rendered_html);

  http_set_header(h, HTTP_HEADER_CONTENT_TYPE, fiobj_str_new("text/html", 9));
  http_send_body(h, rendered_html_info.data, rendered_html_info.len);

  fiobj_mustache_free(template);
  fiobj_free(data);
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
