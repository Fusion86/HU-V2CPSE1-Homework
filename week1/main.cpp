#include <hwlib.hpp>

extern "C" {
void application();
void print_asciz(const char *s);

void uart_put_char(char c) {
    hwlib::cout << c;
}

char invert_char(char c) {
    if (c > 64 && c < 91)
        return c + 32;
    if (c > 96 && c < 123)
        return c - 32;
    return c;
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
