#pragma once

#include "driver/uart.h"
#include "esp_err.h"
#include "hal/uart_types.h"
#include "soc/gpio_num.h"
#include <cstdint>
#include <span>

namespace talon {

class uart {
public:
    uart(uart_port_t port, gpio_num_t rx, gpio_num_t tx, int ring_buf_size);
    ~uart();

    esp_err_t init();
    esp_err_t send(std::span<const uint8_t> data);
    esp_err_t recv(std::span<uint8_t> buffer, std::size_t& bytes_read, uint32_t timeout_ms = 250);

private:
    uart_port_t port_;
    gpio_num_t tx_;
    gpio_num_t rx_;
    uart_config_t config_;
    int ring_buf_size_;
    bool initialized_{false};
};
    
}