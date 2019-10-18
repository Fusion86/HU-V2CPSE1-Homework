#include <hwlib.hpp>

#include "lib.hpp"

extern "C" float inner_product(float a[], float b[], int length);
// extern float float_zero;

void print_arr(float arr[], int length) {
    for (int i = 0; i < length; i++) {
        hwlib::cout << arr[i];
        if (i != length - 1)
            hwlib::cout << ", ";
        else
            hwlib::cout << "\n";
    }
}

int main() {
    // Make sure float_zero is a valid float
    // float_zero = 0.0f;

    // Wait for terminal
    hwlib::wait_ms(1000);

    float a[] = {2, 4, 6.39, 8};
    float b[] = {3, 6, 8.5, 12};
    int size = sizeof(a) / sizeof(a[0]);

    hwlib::cout << "a: ";
    print_arr(a, size);
    hwlib::cout << "b: ";
    print_arr(b, size);

    float res = inner_product(a, b, size);
    hwlib::cout << "inner_product: " << res << "\n";
}
