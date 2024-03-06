#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include <esp_system.h>
#include <nvs_flash.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "driver/gpio.h"
#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/api.h>
#include <lwip/netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "spi_flash_mmap.h"
#include <esp_http_server.h>
#include "esp_spiffs.h"

#define INDEX_HTML_PATH "/spiffs/index.html"

#define LED_RED     23
#define LED_YELLOW  21
#define LED_GREEN   18

// const char *TAG = "espressif"; // TAG for debug

typedef struct 
{
    char            index_html[4096];
    char            response_data[4096];
    int             led_red_state;
    int             led_yellow_state;
    int             led_green_state;
} esp_http_server_t;

/**
 * @author  dendifuadi
 * @brief   Initialization for retrieve html file
 * @param   esp_http_server http server parameters
 */
void initi_web_page_buffer(esp_http_server_t *esp_http_server);

/**
 * @author  dendifuadi
 * @brief   
 * @param   req
 */
esp_err_t send_web_page(httpd_req_t *req);

httpd_handle_t setup_server(void);
#endif