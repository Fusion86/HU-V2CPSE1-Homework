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
            return hours == rhs.hours && minutes == rhs.minutes;
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
                      << time.minutes;
        }
    };

    class clock {
      private:
        clock_time time = {0};
        clock_time prev_time = {1};
        hwlib::window& window;
        hwlib::target::pin_in btnAddMinute;
        hwlib::target::pin_in btnAddHour;
        bool drawFlag = false;

        hwlib::xy windowCenter;
        hwlib::circle clockFrame;
        hwlib::line minuteHand;
        hwlib::line hourHand;

      public:
        clock(hwlib::window& window, hwlib::target::pin_in& btnAddMinute, hwlib::target::pin_in& btnAddHour);
        void update();
        void draw();

      private:
        void updateHand(hwlib::line& hand, int rotationDegrees, int length);
    };

    // Calculate rotation endpoint xy where origin = 0,0
    constexpr hwlib::xy calcRotationEnd(int rotationDegrees, int radius) {
        float radians = rotationDegrees * (PI / 180);
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
    static constexpr std::array<hwlib::xy, 12> hourLineEnds = buildLookupTable<hwlib::xy, 12>(20);

    // Build table for 60 minutes
    static constexpr std::array<hwlib::xy, 60> minuteLineEnds = buildLookupTable<hwlib::xy, 60>(30);
} // namespace Fusion
