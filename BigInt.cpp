//
// Created by Jonathan Leopold on 11/04/2026.
//

#include "BigInt.h"

#include <iomanip>
#include <iostream>
#include <ostream>

BigInt::BigInt() = default;

BigInt::BigInt(const int64_t value) {
    number.push_back(value);
}

BigInt::BigInt(const std::string &) {

}

void BigInt::display() const {
    for (size_t i = number.size(); i>0; i--) {
        std::cout<<i-1 <<"[" << number.at(i-1)<<"] ";
    }
    std::cout<<std::endl;
}
std::string BigInt::uint64ToHex(const uint64_t &n) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(16)<<std::hex << n;
    return stream.str();
}

void BigInt::displayHex() const {
    for (size_t i = number.size(); i>0; i--) {
        //std::cout << uint64ToHex(number.at(i-1)) << " ";
    }
    std::cout<< toHexString()<<std::endl;
}

std::string BigInt::toHexString() const {
    std::string result;
    for (size_t i = number.size(); i>0; i--) {
        result += uint64ToHex(number.at(i-1)) + " ";
    }
    return result;
}


void BigInt::operator+=(const BigInt &other) {
    size_t lenLeft= number.size();
    size_t lenRight= other.number.size();
    size_t common = std::min(lenLeft, lenRight);
    bool carry = false;
    for (size_t i = 0; i < common; i++) {
        if (carry) {
            carry = __builtin_add_overflow(number.at(i),1, &number.at(i));
        }
        carry |= __builtin_add_overflow( number.at(i),other.number.at(i), &number.at(i));
    }
    size_t i = common;
    while(carry && i < lenLeft ) {
        carry = __builtin_add_overflow(number.at(i),1, &number.at(i));
        i++;
    }
    number.push_back(1);
}

BigInt BigInt::operator+(const BigInt &other) const {
    BigInt result = *this;
    result+=other;
    return result;
}
