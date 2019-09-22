#include "notes_to_cpp.hpp"

void notes_to_cpp::start() {
    if (started) return;
    started = true;
    os << R"(#pragma once

#include "melody.hpp"

class meldody : public melody {
  public:
    void play(note_player& p) {)";
}

void notes_to_cpp::play(const note& n) {
    if (!started) return;
    os << "\n        p.play(note{" << n.frequency << ", " << n.duration << "});";
}

void notes_to_cpp::end() {
    started = false;
    os << R"(
    }
};)";
}
