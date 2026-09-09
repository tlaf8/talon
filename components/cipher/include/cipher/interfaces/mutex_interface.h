#ifndef CIPHER_MUTEX_INTERFACE_H_
#define CIPHER_MUTEX_INTERFACE_H_

#include <cstdint>

namespace cipher::interfaces {

class MutexInterface {
public:
    virtual ~MutexInterface() = default;

    virtual void Lock() = 0;
    virtual void Unlock() = 0;
    virtual bool TryLock(uint32_t timeout_ms) = 0;
};

}  // namespace cipher::interfaces

#endif  // CIPHER_MUTEX_INTERFACE_H_
