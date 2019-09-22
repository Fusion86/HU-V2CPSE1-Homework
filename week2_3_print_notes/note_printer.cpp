#include "note_printer.hpp"

#include <hwlib.hpp>

void note_printer::play(const note& n) {
    hwlib::cout << n << "\n";
}