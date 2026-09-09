#include "cipher/os.h"
#include "cipher/task.h"
#include "esp_log.h"

namespace {

constexpr char kTag[] = "talon";

void HelloWorld() {
    static unsigned long count = 0;
    while (true) {
        ESP_LOGI(kTag, "Hello world x%d", count++);
        cipher::OS::Sleep(1000);
    }
}

}  // namespace

extern "C" void app_main(void) {
    static cipher::Task hello_task("hello", 4096, 5, HelloWorld);

    hello_task.Run();
}
