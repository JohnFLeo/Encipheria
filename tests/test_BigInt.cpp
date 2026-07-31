//
// Created by johnfleo on 7/22/26.
//
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "BigInt.h"
TEST_CASE("BigInt creation", "[BigInt][constructor]") {
    SECTION("UINT64 max val") {
        std::cout<<"===[UINT64 max val]==="<<std::endl;
        auto a = BigInt(UINT64_MAX);
        a.display();
        REQUIRE(a.number[0] == UINT64_MAX);
    }
    SECTION("normal small value") {
        std::cout<<"===[normal small value]==="<<std::endl;
        auto b = BigInt(20);
        b.display();
        REQUIRE(b.number[0] == 20);

    }
    // TODO negative values
    // TODO range copy

    SECTION("value that doesn't fit in one block only") {
        std::cout<<"===[value that doesn't fit in one block only]==="<<std::endl;
        auto c = BigInt("1ffffffffffffffff");
        c.display();
        REQUIRE(c.number[0] == UINT64_MAX);
        REQUIRE(c.number[1] == 1);
        REQUIRE(c.toHexString() == "0000000000000001ffffffffffffffff");
    }
}
TEST_CASE("BigInt direct block manipulation", "[BigInt][blockMaipulation]") {
    SECTION("adding blocks") {
        std::cout<<"===[Adding blocks]==="<<std::endl;
        BigInt a(33);
        std::cout<<"Before:\t";
        a.display();
        a.addBlocks(2);
        std::cout<<"After:\t";
        a.display();
        REQUIRE(a.number[0] == 33);
        REQUIRE(a.number[1] == 0);
        REQUIRE(a.number[2] == 0);
        REQUIRE(a.number.size()==3);
    }
}
TEST_CASE("BigInt basic arithmetic operations", "[BigInt][math]") {
    SECTION("Addition one block each") {
        std::cout<<"===[Addition one block each]==="<<std::endl;
        BigInt a(1);
        BigInt b(2);
        std::cout<<"a:\t";
        a.display();
        std::cout<<"b:\t";
        b.display();
        auto c = a+b;
        std::cout<<"c = a+b:\t";
        c.display();
        REQUIRE(c.number[0]==3);
    }
    SECTION("Addition two blocks each") {
        std::cout<<"===[Addition two blocks each]==="<<std::endl;
        BigInt a("10000000000000000");
        BigInt b("20000000000000000");
        std::cout<<"a:\t";
        a.display();
        std::cout<<"b:\t";
        b.display();
        auto c = a+b;
        std::cout<<"c = a+b:\t";
        c.display();
        REQUIRE(c.number[0]==0);
        REQUIRE(c.number[1]==3);
    }
    SECTION("Addition with overflow") {
        std::cout<<"===[Addition with overflow]==="<<std::endl;
        BigInt a(UINT64_MAX);
        BigInt b(1);
        std::cout<<"a:\t";
        a.display();
        std::cout<<"b:\t";
        b.display();
        auto c = a+b;
        std::cout<<"c = a+b:\t";
        c.display();
        REQUIRE(c.number[0]==0);
        REQUIRE(c.number[1]==1);
    }
    SECTION("Addition with overflow that ripples through") {
        std::cout<<"===[Addition with overflow that ripples through]==="<<std::endl;
        BigInt a(UINT64_MAX);
        BigInt b(std::string(32, 'f'));
        std::cout<<"a:\t";
        a.display();
        std::cout<<"b:\t";
        b.display();
        auto c = a+b;
        std::cout<<"c = a+b:\t";
        c.display();
        REQUIRE(c.number[0]==UINT64_MAX -1);
        REQUIRE(c.number[1]==0);
        REQUIRE(c.number[2]==1);
    }
}
TEST_CASE("BigInt edge cases and exception handling", "[BigInt][exceptions]") {

}