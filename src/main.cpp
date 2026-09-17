#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "hal/uart_types.h"
#include "talon/uart.hpp"
#include "tasks/uart_task.hpp"

extern "C" {
    void app_main(void) {
        static talon::uart uart_send{
            UART_NUM_1,
            GPIO_NUM_1,
            GPIO_NUM_2,
            1024
        };

        static talon::uart uart_recv{
            UART_NUM_2,
            GPIO_NUM_11,
            GPIO_NUM_12,
            1024
        };

        xTaskCreate(
            talon::tasks::uart_send_task,
            "uart_task_send",
            4096,
            &uart_send,
            4,
            nullptr
        );

        xTaskCreate(
            talon::tasks::uart_recv_task,
            "uart_task_recv",
            4096,
            &uart_recv,
            5,
            nullptr
        );
    }
}