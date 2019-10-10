// Created by Wouter "Fusion86" Visser
// Licensed under the Specerijen met Eigen Risico Public License

#include <hwlib.hpp>

extern "C" {
void uart_put_char(char c) {
    hwlib::cout << c;
}

void decode_str_compressed();
}

int main(void) {
    // Wait for the PC console to start
    hwlib::wait_ms(2000);

    decode_str_compressed();
}
