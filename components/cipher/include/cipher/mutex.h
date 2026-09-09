#ifndef CIPHER_MUTEX_H_
#define CIPHER_MUTEX_H_

#include "cipher/interfaces/mutex_interface.h"
#include "freertos/idf_additions.h"

namespace cipher {

class Mutex : public interfaces::MutexInterface {
public:
    Mutex();
    ~Mutex();

    void Lock() override;
    void Unlock() override;
    bool TryLock(uint32_t timeout_ms) override;

private:
    SemaphoreHandle_t handle_;
};

}  // namespace cipher

#endif  // CIPHER_MUTEX_H_
