#include "main.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"

static const char* TAG = "main";

extern "C" {
    void app_main(void) {
        for(;;) {
            ESP_LOGI(TAG, "Hello from ESP\n");
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}