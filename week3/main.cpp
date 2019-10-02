#include <hwlib.hpp>

#include "clock.hpp"

int main(void) {
    namespace target = hwlib::target;

    auto scl = target::pin_oc(target::pins::scl);
    auto sda = target::pin_oc(target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    auto display = hwlib::glcd_oled(i2c_bus, 0x3c); // Usage: display.write(hwlib::xy(i, 10));

    auto btnAddMinute = target::pin_in(hwlib::target::pins::d8);
    auto btnAddHour = target::pin_in(hwlib::target::pins::d9);

    clock_time time = {0};
    clock_time prev_time = {1};

    for (;;) {
        btnAddMinute.refresh();
        btnAddHour.refresh();

        if (!btnAddMinute.read()) {
            time.incrMinutes();
        }

        if (!btnAddHour.read()) {
            time.incrHours();
        }

        // Only print time when it actually changed
        if (time != prev_time) {
            hwlib::cout << time << "\n";
            prev_time = time;
        }
    }
}
