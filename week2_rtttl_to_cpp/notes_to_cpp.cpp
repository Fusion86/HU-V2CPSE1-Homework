#include "notes_to_cpp.hpp"

void notes_to_cpp::start(std::ostream os) {
    if (started) return;

    started = true;
}

void notes_to_cpp::play(const note& n) {
    if (!started) return;
}

void notes_to_cpp::end() {
    started = false;
}
