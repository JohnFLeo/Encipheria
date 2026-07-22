//
// Created by johnfleo on 7/22/26.
//
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "BigInt.h"
TEST_CASE("BigInt creation", "[BigInt][constructor]") {
    auto a = BigInt(UINT64_MAX);
    auto b = BigInt(20);
    auto c = BigInt("1ffffffffffffffff");
    a.display();a.displayHex();
    b.display();
    c.display();
    REQUIRE(a.number[0] == UINT64_MAX);
    REQUIRE(b.number[0] == 20);
    REQUIRE(c.number[0] == UINT64_MAX);
    REQUIRE(c.number[1] == 1);
    REQUIRE(c.toHexString() == "1ffffffffffffffff");
}
TEST_CASE("BigInt printing", "[BigInt][print]") {

}
TEST_CASE("BigInt basic arithmetic operations", "[BigInt][math]") {

}
TEST_CASE("BigInt edge cases and exception handling", "[BigInt][exceptions]") {

}