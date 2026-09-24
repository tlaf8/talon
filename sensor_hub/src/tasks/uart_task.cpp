#include "tasks/uart_task.hpp"
#include <cstring>
#include "esp_err.h"
#include "esp_log_buffer.h"
#include "freertos/FreeRTOS.h"
#include "hal/uart_types.h"
#include "talon/uart.hpp"

namespace talon::tasks {

constexpr char UART_RECV_TAG[] = "talon_uart_recv";
constexpr std::array<uint8_t, 4> TEST_DATA { 0xDE, 0xAD, 0xBE, 0xEF };

void uart_send_task(void* context) {
    auto& controller = *static_cast<talon::uart*>(context);

    ESP_ERROR_CHECK(controller.init());
    
    // never return from this, keep repeating
    for(;;) {
        controller.send(TEST_DATA);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void uart_recv_task(void* context) {
    auto& controller = *static_cast<talon::uart*>(context);
    std::array<uint8_t, 4> raw_bytes{};

    ESP_ERROR_CHECK(controller.init());
    
    // never return from this, keep repeating
    for(;;) {
        size_t bytes_read;
        if (ESP_OK == controller.recv(raw_bytes, bytes_read)) {
            if (bytes_read > 0) {
                ESP_LOGI(UART_RECV_TAG, "Got %zu bytes:", bytes_read);
                ESP_LOG_BUFFER_HEX(UART_RECV_TAG, raw_bytes.data(), bytes_read);
            }
        }
    }
}

}