#pragma once

#include <hwlib.hpp>

struct clock_time {
    int hours;
    int minutes;

    void incrMinutes(int m = 1) {
        minutes += m;
        if (minutes > 60) {
            incrHours(minutes / 60);
            minutes = minutes % 60;
        }
    }

    void incrHours(int h = 1) {
        hours = (hours + h) % 24;
    }

    bool operator==(const clock_time& rhs) {
        return hours == rhs.hours && minutes == rhs.minutes;
    }

    bool operator!=(const clock_time& rhs) {
        return !(*this == rhs);
    }

    friend hwlib::ostream& operator<<(hwlib::ostream& os, const clock_time& time) {
        return os << "Current time: "
                  << hwlib::setfill('0')
                  << hwlib::setw(2)
                  << time.hours
                  << ":"
                  << hwlib::setfill('0')
                  << hwlib::setw(2)
                  << time.minutes;
    }
};
