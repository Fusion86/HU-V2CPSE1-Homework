// Created by Wouter "Fusion86" Visser
// Licensed under the Specerijen met Eigen Risico Public License

#include <iostream>
#include <fstream>
#include <sstream>

#include "../week4/compressor.hpp"
#include "../week4/decompressor.hpp"

int main(void) {
    lz_compressor<4096> compressor;

    std::ifstream f1;
    f1.open("../week4/wilhelmus.txt");
    if (!f1.is_open()) {
        std::cerr << "input file not opened";
        return -1;
    }

    std::ofstream f2;
    f2.open("compressed_data.asm");
    if (!f2.is_open()) {
        std::cerr << "output file not opened";
        return -1;
    }

    std::stringstream ss;

    compressor.compress(
        [&f1]() -> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
        [&ss](char c) { ss << (unsigned int)c << ", "; });

    f2 << R"(.cpu cortex-m0
.align 2

.data
str_compressed:
.byte )"
       << ss.str()
       << '\n';

    f1.close();
    f2.close();
}
