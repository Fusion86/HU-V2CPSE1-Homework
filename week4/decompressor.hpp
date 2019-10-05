#pragma once

#include <array>
#include "match.hpp"

class lz_decompressor {
  private:
    static constexpr auto buffer_length = 100;
    std::array<char, buffer_length> buffer;

  public:
    template <typename S, typename W>
    void decompress(S read, W write) {
        for (;;) {
            auto c = read();
            if (c == 0) { return; }
            if (c != '@') {
                add(c, write);
            } else {
                int offset = read() - '0';
                int length = read() - '0';
                add(match(offset, length), write);
            }
        }
    }

  private:
    template <typename W>
    void add(char c, W write) {
        write(c);
        for (int i = buffer_length; i > 0; --i) {
            buffer[i] = buffer[i - 1];
        }
        buffer[0] = c;
    }

    template <typename W>
    void add(match m, W write) {
        while (m.length--) {
            add(buffer[m.offset], write);
        }
    }
};
