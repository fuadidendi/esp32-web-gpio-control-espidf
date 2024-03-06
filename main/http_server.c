#include "http_server.h"

extern esp_http_server_t   esp_server_drv;

void initi_web_page_buffer(esp_http_server_t *esp_http_server)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true};

    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));

    memset((void *)esp_http_server->index_html, 0, sizeof(esp_http_server->index_html));
    struct stat st;
    if (stat(INDEX_HTML_PATH, &st))
    {
        // ESP_LOGE(TAG, "index.html not found");
        return;
    }

    FILE *fp = fopen(INDEX_HTML_PATH, "r");
    if (fread(esp_http_server->index_html, st.st_size, 1, fp) == 0)
    {
        // ESP_LOGE(TAG, "fread failed");
    }
    fclose(fp);
}

esp_err_t send_web_page(httpd_req_t *req)
{
    int response;
    char state1[5];
    char state2[5];
    char state3[5];

    if(esp_server_drv.led_red_state) strcpy(state1, "ON");
    else strcpy(state1, "OFF");

    if(esp_server_drv.led_yellow_state) strcpy(state2, "ON");
    else strcpy(state2, "OFF");

    if(esp_server_drv.led_green_state) strcpy(state3, "ON");
    else strcpy(state3, "OFF");

    sprintf(esp_server_drv.response_data, esp_server_drv.index_html, state1, state2, state3);
    
    response = httpd_resp_send(req, esp_server_drv.response_data, HTTPD_RESP_USE_STRLEN);
    return response;
}

esp_err_t get_req_handler(httpd_req_t *req)
{
    return send_web_page(req);
}

esp_err_t led_red_on_handler(httpd_req_t *req)
{
    gpio_set_level(LED_RED, 1);
    esp_server_drv.led_red_state = 1;
    return send_web_page(req);
}

esp_err_t led_red_off_handler(httpd_req_t *req)
{
    gpio_set_level(LED_RED, 0);
    esp_server_drv.led_red_state = 0;
    return send_web_page(req);
}

esp_err_t led_yellow_on_handler(httpd_req_t *req)
{
    gpio_set_level(LED_YELLOW, 1);
    esp_server_drv.led_yellow_state = 1;
    return send_web_page(req);
}

esp_err_t led_yellow_off_handler(httpd_req_t *req)
{
    gpio_set_level(LED_YELLOW, 0);
    esp_server_drv.led_yellow_state = 0;
    return send_web_page(req);
}

esp_err_t led_green_on_handler(httpd_req_t *req)
{
    gpio_set_level(LED_GREEN, 1);
    esp_server_drv.led_green_state = 1;
    return send_web_page(req);
}

esp_err_t led_green_off_handler(httpd_req_t *req)
{
    gpio_set_level(LED_GREEN, 0);
    esp_server_drv.led_green_state = 0;
    return send_web_page(req);
}

httpd_uri_t uri_get = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = get_req_handler,
    .user_ctx = NULL};

httpd_uri_t uri_red_on = {
    .uri = "/ledRedOn",
    .method = HTTP_GET,
    .handler = led_red_on_handler,
    .user_ctx = NULL};

httpd_uri_t uri_red_off = {
    .uri = "/ledRedOff",
    .method = HTTP_GET,
    .handler = led_red_off_handler,
    .user_ctx = NULL};

httpd_uri_t uri_yellow_on = {
    .uri = "/ledYellowOn",
    .method = HTTP_GET,
    .handler = led_yellow_on_handler,
    .user_ctx = NULL};

httpd_uri_t uri_yellow_off = {
    .uri = "/ledYellowOff",
    .method = HTTP_GET,
    .handler = led_yellow_off_handler,
    .user_ctx = NULL};

httpd_uri_t uri_green_on = {
    .uri = "/ledGreenOn",
    .method = HTTP_GET,
    .handler = led_green_on_handler,
    .user_ctx = NULL};

httpd_uri_t uri_green_off = {
    .uri = "/ledGreenOff",
    .method = HTTP_GET,
    .handler = led_green_off_handler,
    .user_ctx = NULL};

httpd_handle_t setup_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_red_on);
        httpd_register_uri_handler(server, &uri_red_off);
        httpd_register_uri_handler(server, &uri_yellow_on);
        httpd_register_uri_handler(server, &uri_yellow_off);
        httpd_register_uri_handler(server, &uri_green_on);
        httpd_register_uri_handler(server, &uri_green_off);
    }

    return server;
}