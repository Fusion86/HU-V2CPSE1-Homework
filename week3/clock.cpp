#include <math.h>

#include "clock.hpp"

namespace Fusion {
    clock::clock(hwlib::window& window, hwlib::target::pin_in& btnAddMinute, hwlib::target::pin_in& btnAddHour)
        : window(window),
          btnAddMinute(btnAddMinute),
          btnAddHour(btnAddHour),
          windowCenter(window.size.x / 2, window.size.y / 2),
          clockFrame(windowCenter, std::min(window.size.x, window.size.y) / 2 - 1),
          minuteHand(windowCenter, hwlib::xy(0, 0)),
          hourHand(windowCenter, hwlib::xy(0, 0)) {
        hwlib::cout << "Window size: " << window.size << "\n";
    }

    void clock::update() {
        if (!btnAddMinute.read()) {
            time.addMinutes(1);
        }

        if (!btnAddHour.read()) {
            time.addHours(1);
        }

        if (time != prev_time) {
            drawFlag = true;
            prev_time = time;
            hwlib::cout << "Time: " << time << "\n";

            updateHand(minuteHand, time.minutes * (360 / 60), 30);
            updateHand(hourHand, time.hours * (360 / 12), 20);
        }
    }

    void clock::draw() {
        if (drawFlag) {
            drawFlag = false;
            window.clear();

            // for (int i = 0; i < 60; i++) {
            //     window.write(hwlib::xy(i, 5));
            // }

            clockFrame.draw(window);
            minuteHand.draw(window);
            hourHand.draw(window);

            window.flush();
        }
    }

    void clock::updateHand(hwlib::line& hand, int rotationDegrees, int length) {
        rotationDegrees -= 90; // Compensate for my bad math
        float radians = rotationDegrees * (PI / 180);
        int x = hand.start.x + cos(radians) * length;
        int y = hand.start.y + sin(radians) * length;
        hand.end = hwlib::xy(x, y);
    }
} // namespace Fusion
