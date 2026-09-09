#ifndef CIPHER_OS_H_
#define CIPHER_OS_H_

#include <cstdint>

namespace cipher {

class OS {
public:
    static void Sleep(uint32_t ms);
};

}  // namespace cipher

#endif  // CIPHER_OS_H_
