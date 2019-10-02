// Created by Wouter "Fusion86" Visser
// Licensed under the Specerijen met Eigen Risico Public License

#include "clock.hpp"

namespace Fusion {
    clock::clock(hwlib::window& window, hwlib::target::pin_in& btnAddMinute, hwlib::target::pin_in& btnAddHour)
        : window(window),
          btnAddMinute(btnAddMinute),
          btnAddHour(btnAddHour),
          windowCenter(window.size.x / 2, window.size.y / 2),
          clockFrame(windowCenter, std::min(window.size.x, window.size.y) / 2 - 1),
          hourHand(windowCenter, hwlib::xy(0, 0)),
          minuteHand(windowCenter, hwlib::xy(0, 0)),
          secondHand(windowCenter, hwlib::xy(0, 0)) {
        hwlib::cout << "Window size: " << window.size << "\n";
    }

    void clock::update() {
        auto now = hwlib::now_us();

        // If 1 second has passed since last update
        if (prev_time_update + 1'000'000 < now) {
            prev_time_update += 1'000'000; // Set prev_time_update to when it should've been updated (NOT to now, to avoid drift)
            time.addSeconds(1);
        }

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

            // Update hands (set end position to origin + rotation)
            hourHand.end = hourHand.start + hourLineEnd[time.hours];
            minuteHand.end = minuteHand.start + minuteLineEnd[time.minutes];
            secondHand.start = windowCenter + secondLineStart[time.seconds];
            secondHand.end = windowCenter + secondLineEnd[time.seconds];
        }
    }

    void clock::draw() {
        if (drawFlag) {
            drawFlag = false;
            window.clear();
            clockFrame.draw(window);
            hourHand.draw(window);
            minuteHand.draw(window);
            secondHand.draw(window);
            window.flush();
        }
    }
} // namespace Fusion
