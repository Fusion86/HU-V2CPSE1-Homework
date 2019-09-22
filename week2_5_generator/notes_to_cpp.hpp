#pragma once

#include <iostream>

#include "note_player.hpp"

class notes_to_cpp : public note_player {
  private:
    std::ostream& os;
    bool started = false;

  public:
    notes_to_cpp(std::ostream& os) : os(os) {}
    void start();
    void play(const note& n) override;
    void end();
};
