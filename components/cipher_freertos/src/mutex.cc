#include "cipher/mutex.h"

#include <cstdint>

#include "freertos/semphr.h"
#include "portmacro.h"

namespace cipher {

Mutex::Mutex() { handle_ = xSemaphoreCreateMutex(); }

Mutex::~Mutex() {
    if (handle_) {
        vSemaphoreDelete(handle_);
    }
}

void Mutex::Lock() { xSemaphoreTake(handle_, portMAX_DELAY); }

void Mutex::Unlock() { xSemaphoreGive(handle_); }

bool Mutex::TryLock(uint32_t timeout_ms) {
    return xSemaphoreTake(handle_, pdMS_TO_TICKS(timeout_ms)) == pdTRUE;
}

}  // namespace cipher
