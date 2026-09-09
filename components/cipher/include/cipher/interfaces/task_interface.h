#ifndef CIPHER_TASK_INTERFACE_H_
#define CIPHER_TASK_INTERFACE_H_

namespace cipher::interfaces {

class TaskInterface {
public:
    virtual ~TaskInterface() = default;

    virtual void Run() = 0;
    virtual void Suspend() = 0;
    virtual void Resume() = 0;
};

}  // namespace cipher::interfaces

#endif  // CIPHER_TASK_INTERFACE_H_
