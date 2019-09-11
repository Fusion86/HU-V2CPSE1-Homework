#include "note.hpp"

#include <hwlib.cpp>

hwlib::ostream& operator<<(hwlib::ostream& os, const note& note) {
    os << "freq: "
       << hwlib::setw(4)
       << note.frequency
       << "  time: "
       << hwlib::setw(6)
       << note.duration;
    return os;
}
