// Created by Wouter "Fusion86" Visser
// Licensed under the Specerijen met Eigen Risico Public License

#include "notes_to_cpp.hpp"

void notes_to_cpp::start() {
    if (started) return;
    started = true;
    os << R"(#include "melody.hpp"

class my_melody : public melody {
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
