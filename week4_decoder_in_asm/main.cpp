#include <hwlib.hpp>

extern "C" {
void uart_put_char(char c) {
    hwlib::cout << c;
}
}

int main(void) {
    // wait for the PC console to start
    hwlib::wait_ms(2000);
}
