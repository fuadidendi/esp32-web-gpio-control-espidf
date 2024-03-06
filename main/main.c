#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "spi_flash_mmap.h"
#include <esp_http_server.h>
#include "esp_spiffs.h"

#include "connect_wifi.h"
#include "http_server.h"

// static const char *TAG = "espressif"; // TAG for debug
esp_http_server_t   esp_server_drv;

void app_main()
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    connect_wifi();
    // GPIO initialization
    esp_rom_gpio_pad_select_gpio(LED_RED);
    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
    esp_rom_gpio_pad_select_gpio(LED_YELLOW);
    gpio_set_direction(LED_YELLOW, GPIO_MODE_OUTPUT);
    esp_rom_gpio_pad_select_gpio(LED_GREEN);
    gpio_set_direction(LED_GREEN, GPIO_MODE_OUTPUT);

    if (wifi_connect_status)
    {
        // ESP_LOGI(TAG, "LED Control SPIFFS Web Server is running ... ...\n");
        initi_web_page_buffer(&esp_server_drv);
        setup_server();
    }
}