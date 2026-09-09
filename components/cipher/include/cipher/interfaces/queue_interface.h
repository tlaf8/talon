#ifndef CIPHER_QUEUE_INTERFACE_H_
#define CIPHER_QUEUE_INTERFACE_H_

#include <cstddef>
#include <cstdint>

namespace cipher::interfaces {

class QueueInterface {
public:
    virtual ~QueueInterface() = default;

    virtual bool Send(const void* item, uint32_t timeout_ms) = 0;
    virtual bool Receive(void* item, uint32_t timeout_ms) = 0;
    virtual size_t Size() const = 0;
};

}  // namespace cipher::interfaces

#endif  // CIPHER_QUEUE_INTERFACE_H_
