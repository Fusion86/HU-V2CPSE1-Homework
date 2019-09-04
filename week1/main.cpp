#include <hwlib.hpp>

extern "C" {
void application();
void print_asciz(const char *s);

void uart_put_char(char c) {
    hwlib::cout << c;
}
}

// void print_asciz(const char *s) {
//     while (*s != '\0') {
//         uart_put_char(*s);
//         ++s;
//     }
// }

// void application() {
//     print_asciz("Hello world\n");
// }

int main(void) {
    namespace target = hwlib::target;

    // wait for the PC console to start
    hwlib::wait_ms(2000);

    application();
}
