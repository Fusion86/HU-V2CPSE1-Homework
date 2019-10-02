// Created by Wouter "Fusion86" Visser
// Licensed under the Specerijen met Eigen Risico Public License

#pragma once

#include <hwlib.hpp>
#include <array>
#include <math.h>

#ifndef PI
#define PI 3.14159265
#endif

namespace Fusion {
    struct clock_time {
        int hours;
        int minutes;
        int seconds;

        void addSeconds(int s) {
            seconds += s;
            if (seconds > 59) {
                addMinutes(seconds / 60);
                seconds = seconds % 60;
            }
        }

        void addMinutes(int m) {
            minutes += m;
            if (minutes > 59) {
                addHours(minutes / 60);
                minutes = minutes % 60;
            }
        }

        void addHours(int h) {
            hours = (hours + h) % 12;
        }

        bool operator==(const clock_time& rhs) {
            return hours == rhs.hours && minutes == rhs.minutes && seconds == rhs.seconds;
        }

        bool operator!=(const clock_time& rhs) {
            return !(*this == rhs);
        }

        friend hwlib::ostream& operator<<(hwlib::ostream& os, const clock_time& time) {
            return os << hwlib::setfill('0')
                      << hwlib::setw(2)
                      << time.hours
                      << ":"
                      << hwlib::setfill('0')
                      << hwlib::setw(2)
                      << time.minutes
                      << ":"
                      << hwlib::setfill('0')
                      << hwlib::setw(2)
                      << time.seconds;
        }
    };

    class clock {
      private:
        clock_time time = {0};
        clock_time prev_time = {1};
        hwlib::window& window;
        hwlib::target::pin_in btnAddMinute;
        hwlib::target::pin_in btnAddHour;

        hwlib::xy windowCenter;
        hwlib::circle clockFrame;
        hwlib::line hourHand;
        hwlib::line minuteHand;
        hwlib::line secondHand;

        // When set to true the next .draw() call will redraw the screen
        bool drawFlag = false;

        // Last time (in us since startup) when time was updated
        uint_fast64_t prev_time_update = 0;

      public:
        clock(hwlib::window& window, hwlib::target::pin_in& btnAddMinute, hwlib::target::pin_in& btnAddHour);
        void update();
        void draw();

      private:
        void updateHand(hwlib::line& hand, int rotationDegrees, int length);
    };

    // Calculate rotation endpoint xy where origin = 0,0
    constexpr hwlib::xy calcRotationEnd(int rotationDegrees, int radius) {
        float radians = (rotationDegrees - 90) * (PI / 180); // -90 because we want the clock to start at 0 and not 3 o'clock
        return hwlib::xy(
            cos(radians) * radius,
            sin(radians) * radius);
    }

    template <typename T, std::size_t S>
    constexpr const std::array<T, S> buildLookupTable(int length) {
        std::array<T, S> arr;
        int stepSize = 360 / S;
        for (size_t i = 0; i < S; i++) {
            arr[i] = calcRotationEnd(stepSize * i, length);
        }
        return arr;
    }

    // Build table for 12 hours
    static constexpr std::array<hwlib::xy, 12> hourLineEnd = buildLookupTable<hwlib::xy, 12>(15);

    // Build table for 60 minutes
    static constexpr std::array<hwlib::xy, 60> minuteLineEnd = buildLookupTable<hwlib::xy, 60>(30);

    // Build table for 60 seconds
    static constexpr std::array<hwlib::xy, 60> secondLineStart = buildLookupTable<hwlib::xy, 60>(24);
    static constexpr std::array<hwlib::xy, 60> secondLineEnd = buildLookupTable<hwlib::xy, 60>(32);
} // namespace Fusion
