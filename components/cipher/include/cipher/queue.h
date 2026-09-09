#ifndef CIPHER_QUEUE_H_
#define CIPHER_QUEUE_H_

#include <cstdint>

#include "cipher/interfaces/queue_interface.h"
#include "freertos/idf_additions.h"

namespace cipher {

class Queue : public interfaces::QueueInterface {
public:
    Queue(size_t item_size, size_t length);
    ~Queue();

    bool Send(const void* item, uint32_t timeout_ms) override;
    bool Receive(void* item, uint32_t timeout_ms) override;
    size_t Size() const override;

private:
    QueueHandle_t handle_;
};

}  // namespace cipher

#endif  // CIPHER_QUEUE_H_
