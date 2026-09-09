idf_component_register(
    SRCS
        "src/mutex.cc"
        "src/queue.cc"
        "src/task.cc"
        "src/os.cc"

    REQUIRES
        cipher
        freertos
)
