#ifndef _NOTE_HPP
#define _NOTE_HPP

#include <hwlib.hpp>

// ===========================================================================
//
// frequencies of standard notes
//
// ===========================================================================

class note {
  public:
    // from https://www.seventhstring.com/resources/notefrequencies.html
    static const int A4 = 440;
    static const int A4s = 466;
    static const int B4 = 494;
    static const int C5 = 523;
    static const int C5s = 554;
    static const int D5 = 587;
    static const int D5s = 622;
    static const int E5 = 659;
    static const int F5 = 698;
    static const int F5s = 740;
    static const int G5 = 784;
    static const int G5s = 830;
    static const int A5 = 880;
    static const int A5s = 932;
    static const int B5 = 987;

    const int frequency;

    static const int dF = 1'000'000; // full measure
    static const int dH = dF / 2;    // half measure
    static const int dQ = dF / 4;    // quarter measure

    const int duration;

    friend hwlib::ostream& operator<<(hwlib::ostream& os, const note& note);

    static const char* frequency_to_string(const int frequency) {
        switch (frequency) {
            case note::A4: return "A4";
            case note::A4s: return "A4s";
            case note::B4: return "B4";
            case note::C5: return "C5";
            case note::C5s: return "C5";
            case note::D5: return "D5";
            case note::D5s: return "D5s";
            case note::E5: return "E5";
            case note::F5: return "F5";
            case note::F5s: return "F5s";
            case note::G5: return "G5";
            case note::G5s: return "G5s";
            case note::A5: return "A5";
            case note::A5s: return "A5s";
            case note::B5: return "B5";
            default: return "unknown";
        }
    }

    static const char* duration_to_string(const int duration) {
        switch (duration) {
            case note::dF: return "1/1";
            case note::dH: return "1/2";
            case note::dQ: return "1/4";
            default: return "unknown";
        }
    }
};

#endif
