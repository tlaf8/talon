#ifndef CIPHER_TASK_H_
#define CIPHER_TASK_H_

#include <functional>

#include "cipher/interfaces/task_interface.h"
#include "freertos/idf_additions.h"

namespace cipher {

class Task : public interfaces::TaskInterface {
public:
    using TaskFunction = std::function<void()>;

    Task(const char* name, uint32_t stack_size, uint32_t priority,
         TaskFunction entry_point);
    ~Task();

    void Run() override;
    void Suspend() override;
    void Resume() override;

private:
    static void TaskEntry(void* parameter);

    const char* name_;
    uint32_t stack_size_;
    uint32_t priority_;
    TaskFunction function_;

    TaskHandle_t handle_;
};

}  // namespace cipher

#endif  // CIPHER_TASK_H_
