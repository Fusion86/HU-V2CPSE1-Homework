// Created by Wouter "Fusion86" Visser
// Licensed under the Specerijen met Eigen Risico Public License

#include <hwlib.hpp>

#include "note_player_gpio.hpp"
#include "rtttl_player.hpp"

#include "my_melody.cpp"

int main(void) {

    namespace target = hwlib::target;
    auto lsp = target::pin_out(target::pins::d7);
    auto p = note_player_gpio(lsp);
    hwlib::wait_ms(10);

    auto melody = my_melody();

    for (;;) {
        melody.play(p);
        hwlib::wait_ms(2000);
    }
}
