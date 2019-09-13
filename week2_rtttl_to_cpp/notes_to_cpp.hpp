#pragma once

#include <iostream>

#include "note_player.hpp"

class notes_to_cpp : public note_player {
  private:
    bool started = false;

  public:
    void start(std::ostream os);
    void play(const note& n) override;
    void end();
};
