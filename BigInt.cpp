//
// Created by Jonathan Leopold on 11/04/2026.
//

#include "BigInt.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ostream>

BigInt::BigInt() = default;

BigInt::BigInt(const int64_t value) {
    isNegative=false;
    number.push_back(value);
}

BigInt::BigInt(const std::string &str) {
    isNegative=false;
    setNumber(str);
}

void BigInt::display() const {
    for (size_t i = 0; i<number.size(); i++) {
        std::cout<<i <<"[" << number.at(i)<<"] ";
    }
    std::cout<<std::endl;
}
std::string BigInt::uint64ToHex(const uint64_t &n) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(16)<<std::hex << n;
    return stream.str();
}

void BigInt::displayHex() const {
    std::cout<< toHexString()<<std::endl;
}

std::string BigInt::toHexString() const {
    std::string result;
    for (unsigned long i : number) {
        result += uint64ToHex(i) + " ";
    }
    return result;
}
/// Converts a string in hexformat(MSB left) to a uint64_t
/// @param str a string in hexformat(MSB left) that represents a number
/// @returns a uint64_t that contains the value
uint64_t BigInt::getUint64(const std::string &str) {
    //std::cout << str << std::endl;
    return std::stoull(str, nullptr,16);
}
void BigInt::setNumber(const std::string &str) {
    number.clear();
    const size_t offset = str.size()%16;
    std::string leftNumber;
    if(offset!=0) {
        leftNumber = str.substr(0,offset);
        number.push_back(getUint64(leftNumber));
    }
    for (size_t i = offset; i < str.size(); i+=16) {
        leftNumber = str.substr(i,16);
        number.push_back(getUint64(leftNumber));
    }
}


bool addBIfPossible(BigInt &a, const BigInt &b, const int idxA, const int idxB) {
    if(idxA<0) {
        a.number.push_front(b.number.at(idxB));
        return false;
    }
    if(idxB<0) {
        return false;
    }
    return __builtin_add_overflow(a.number.at(idxA),b.number.at(idxB), &a.number.at(idxA));
}
bool addOneIfPossible(BigInt &a,  const int idxA) {
    if(idxA<0) {
        a.number.push_front(1);
        return false;
    }
    return __builtin_add_overflow(a.number.at(idxA),1, &a.number.at(idxA));
}

void addAB(BigInt &a, const BigInt &b) {
    const size_t bigger = std::max( a.number.size(),b.number.size() );
    bool carry = false;
    for (int i = 0; i < bigger; i++) {
        const int idxA = static_cast<int>(a.number.size())-1-i;
        const int idxB = static_cast<int>(b.number.size())-1-i;
        if (carry) {
            carry = addOneIfPossible(a,idxA);
        }
        carry |= addBIfPossible(a,b,idxA,idxB);
    }
    if(carry) a.number.push_front(1);
}

void BigInt::operator+=(const BigInt &other) {
    std::cout << " ";
    displayHex();
    std::cout << "+";
    other.displayHex();
    std::cout << "====================\n";
    addAB(*this ,other);

    //std::cout << "====================\n";
    std::cout << " ";
    displayHex();
    display();
    std::cout << std::endl;
}

BigInt BigInt::operator+(const BigInt &other) const {
    BigInt result = *this;
    result+=other;
    return result;
}
