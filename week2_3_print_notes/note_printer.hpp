#pragma once

#include "note_player.hpp"

class note_printer : public note_player {
  public:
    void play(const note& n) override;
};