#include "cipher/task.h"

#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

namespace cipher {

Task::Task(const char* name, uint32_t stack_size, uint32_t priority,
           TaskFunction function)
    : name_(name),
      stack_size_(stack_size),
      priority_(priority),
      function_(function),
      handle_(nullptr) {}

Task::~Task() = default;

void Task::TaskEntry(void* parameter) {
    auto* task = static_cast<Task*>(parameter);
    task->function_();
    vTaskDelete(nullptr);
}

void Task::Run() {
    xTaskCreate(TaskEntry, name_, stack_size_, this, priority_, &handle_);
}

void Task::Suspend() { vTaskSuspend(handle_); }

void Task::Resume() { vTaskResume(handle_); }

}  // namespace cipher
