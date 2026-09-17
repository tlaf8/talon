#include "talon/uart.hpp"
#include "driver/uart.h"
#include "esp_err.h"
#include "freertos/projdefs.h"
#include "hal/uart_types.h"
#include "soc/gpio_num.h"

namespace talon {

constexpr char UART_TAG[] = "talon_uart";

uart::uart(uart_port_t port, gpio_num_t rx, gpio_num_t tx, int ring_buf_size)
: port_(port), tx_(rx), rx_(tx), config_{}, ring_buf_size_(ring_buf_size) {
    config_.baud_rate = 115200;
    config_.data_bits = UART_DATA_8_BITS;
    config_.parity = UART_PARITY_DISABLE;
    config_.stop_bits = UART_STOP_BITS_1;
    config_.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    config_.source_clk = UART_SCLK_DEFAULT;
}

uart::~uart() {
    // remove the driver if we had installed it during init
    if (initialized_) {
        uart_driver_delete(port_);
    }
}

esp_err_t uart::init() {
    // install the driver
    if (const esp_err_t err = uart_driver_install(
        port_, 
        ring_buf_size_, 
        ring_buf_size_, 
        16, 
        nullptr, 
        0
    ); err != ESP_OK) {
        return err;
    }

    // set up communication parameters
    if (const esp_err_t err = uart_param_config(
        port_, 
        &config_
    ); err != ESP_OK) {
        return err;
    }

    // set uart pins
    if (const esp_err_t err = uart_set_pin(
        port_, 
        tx_, 
        rx_, 
        UART_PIN_NO_CHANGE, 
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE
    ); err != ESP_OK) {
        return err;
    }

    // initialized correctly if we reached here
    initialized_ = true;

    return ESP_OK;
}

esp_err_t uart::send(std::span<uint8_t> data) {
    if (!initialized_) {
        ESP_LOGE(UART_TAG, "UART port %d not installed.\n", port_);
        return ESP_ERR_INVALID_STATE;
    }

    const int bytes_written = static_cast<size_t>(uart_write_bytes(
        port_, 
        data.data(), 
        data.size_bytes()
    ));

    return (bytes_written != data.size_bytes()) ? ESP_FAIL : ESP_OK;
}

esp_err_t uart::recv(std::span<uint8_t> buffer, std::size_t& bytes_read, uint32_t timeout_ms) {
    if (!initialized_) {
        ESP_LOGE(UART_TAG, "UART port %d not installed.\n", port_);
        return ESP_ERR_INVALID_STATE;
    }

    size_t bytes_received = static_cast<size_t>(uart_read_bytes(
        port_, 
        buffer.data(), 
        buffer.size_bytes(), 
        pdMS_TO_TICKS(timeout_ms)
    ));

    // set read bytes if the driver succeeded
    if (bytes_received < 0) {
        return ESP_FAIL;
    } else {
        bytes_read = bytes_received;
        return ESP_OK;
    }
}

}
