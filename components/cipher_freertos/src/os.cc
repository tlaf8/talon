#include "cipher/os.h"

#include "freertos/FreeRTOS.h"

namespace cipher {

void OS::Sleep(uint32_t ms) { vTaskDelay(pdMS_TO_TICKS(ms)); }

}  // namespace cipher
