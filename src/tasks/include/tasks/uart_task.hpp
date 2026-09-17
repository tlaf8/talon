#pragma once

namespace talon::tasks {

void uart_recv_task(void* context);
void uart_send_task(void* context);

}