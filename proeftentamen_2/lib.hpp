#include <hwlib.hpp>

hwlib::ostream& operator<<(hwlib::ostream& os, float f) {
    // HACK: This is not a 'legit' float printing implementation, but it works well enough for me
    constexpr int PRECISION = 1'000;
    char prefix = '\0';

    if (f < 0) {
        f *= -1;
        prefix = '-';
    }

    // Lets assume that `f = 2.3456` for all example comments
    int i = (int)f; // 'Full' number, eg. 2

    float tmp = (f - i);              // Float minus whole number, eg. 0.3456
    int dec = (int)(tmp * PRECISION); // Decimals, eg. 345
    os << prefix << i << "." << dec;  // Prints 2.345 (with precision 1000)
    return os;
}

extern "C" {
float float_multiply(float a, float b) {
    // hwlib::cout << "mult: " << a << " * " << b << "\n";
    return a * b;
}

float float_add(float a, float b) {
    // hwlib::cout << "add: " << a << " + " << b << "\n";
    return a + b;
}

// float inner_product(float a[], float b[], int length) {
//     float sum = 0;
//     for (int i = 0; i < length; i++) {
//         sum += a[i] * b[i];
//     }
//     return sum;
// }
}
