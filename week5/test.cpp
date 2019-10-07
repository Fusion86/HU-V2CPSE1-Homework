#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <array>
#include <iostream>
#include <sstream>
#include <vector>

#include "set.hpp"

TEST_CASE("no duplicates") {
    set<int, 10> set;
    set.add(1);
    set.add(5);
    set.add(20);
    set.add(20);
    set.add(20);
    set.add(20);
    set.add(100);
    std::stringstream ss;
    ss << set;
    REQUIRE(ss.str() == "1, 5, 20, 100");
}

TEST_CASE("max size") {
    set<int, 5> set;
    for (int i = 0; i < 10; i++)
        set.add(i);
    std::stringstream ss;
    ss << set;
    REQUIRE(ss.str() == "0, 1, 2, 3, 4");
}

TEST_CASE("remove items") {
    set<std::string, 5> set;
    set.add("test");
    set.add("string");
    set.add("remove");
    set.remove("remove");
    set.remove("ohno");
    std::stringstream ss;
    ss << set;
    REQUIRE(ss.str() == "test, string");
}

TEST_CASE("char max") {
    set<char, 10> set;
    for (int i = 0; i < 10; i++)
        set.add('a' + i);
    REQUIRE(set.max() == 'a' + 9); // 106 == 'j'
}

TEST_CASE("std::array<char, 3> max") {
    std::vector<std::array<char, 3>> items = {
        std::array<char, 3>{' ', ' ', ' '},
        std::array<char, 3>{'u', 's', 'e'},
        std::array<char, 3>{'l', 'e', 's'},
        std::array<char, 3>{'s', ' ', 'w'},
        std::array<char, 3>{'a', 't', 'e'},
        std::array<char, 3>{'r', ' ', ':'},
        std::array<char, 3>{'(', ' ', ' '},
    };

    set<std::array<char, 3>, 10> set;
    for (const auto& item : items)
        set.add(item);

    // Taken from https://stackoverflow.com/a/36315647/2125072
    REQUIRE(set.max() == *max_element(items.begin(), items.end()));
}
