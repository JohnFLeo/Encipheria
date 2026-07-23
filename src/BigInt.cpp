//
// Created by Jonathan Leopold on 11/04/2026.
//

#include "BigInt.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
//region  Constructors
BigInt::BigInt() = default;

BigInt::BigInt(const int64_t value) {
    isNegative=false;
    number.push_back(value);
}

BigInt::BigInt(const std::string &str) {
    isNegative=false;
    setNumber(str);
}
BigInt::BigInt( const size_t end, const size_t start, const BigInt &source){
    if (end < start) {
        number.clear();
        number.push_back(0);
        isNegative=false;
        return;
    }
    const std::deque<uint64_t> range(&source.number[start], &source.number[end]);
    number = range;
    isNegative=source.isNegative;
}
//endregion
//region Printing
void BigInt::display() const {
    uint64_t i = number.size()-1;
    for (auto it = number.rbegin(); it!=number.rend(); ++it, i--) {
        std::cout<< i <<"[" << number.at(i)<<"] ";
    }
    std::cout<<std::endl;
}
void BigInt::displayHex() const {
    std::cout<< toHexString(" ")<<std::endl;
}
std::string BigInt::uint64ToHex(const uint64_t &n) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(16)<<std::hex << n;
    return stream.str();
}

std::string BigInt::toHexString(const std::string& filler) const {
    std::string result;
    for (auto it = number.rbegin(); it!=number.rend(); ++it) {
        result += uint64ToHex(*it)+filler;
    }
    return result;
}
//endregion
//region Direct block manipulation

/// Converts a string in hexformat(MSB left) to a uint64_t
/// @param str a string in hexformat(MSB left) that represents a number
/// @returns a uint64_t that contains the value
uint64_t BigInt::getUint64(const std::string &str) {
    //std::cout << str << std::endl;
    return std::stoull(str, nullptr,16);
}
///Sets a new value by splitting the string in substrings of length 16 and gets the corresponding uint64
void BigInt::setNumber(const std::string &str) {
    number.clear();
    const size_t offset = str.size()%16;
    std::string leftNumber;
    //If the size of the string doesn't fit perfectly in the 16 long substrings
    if(offset!=0) {
        leftNumber = str.substr(0,offset);
        number.push_front(getUint64(leftNumber));
    }
    for (size_t i = offset; i < str.size(); i+=16) {
        leftNumber = str.substr(i,16);
        number.push_front(getUint64(leftNumber));
    }
}

void BigInt::addBlocks(const uint64_t &amount) {
    number.resize(number.size()+amount,0);
}
//endregion
//region Arithmetic
/* Case: a.size < b.size
 * a = [ a0 ] [ a1 ]
 * b = [ b0 ] [ b1 ] [ b2 ] [ b3 ] [ b4 ]
 * idxA starts at size of a minus one and gets smaller the bigger i gets (analog for idxB)
 * idxA and idxB are the same distance away from their ending
 * example:
 *   i = 1 -> a[idxA] = [ a0 ], b[idxB] = [ b3 ]
 *   i = 3 -> a[idxA] =  null , b[idxB] = [ b1 ] etc.
 *
 * after i = 2: idxA < 0 and thus the number b[idxB] is inserted at the front of a
 *
 * Case: a.size >= b.size
 * a = [ a0 ] [ a1 ] [ a2 ] [ a3 ] [ a4 ]
 * b = [ b0 ] [ b1 ]
 * before i = 2: idxB >  0 and thus an addition is performed
 * example:
 *   i = 1 -> a[idxA] = a[idxA] + b[idxB] =[ a3 ]+ [ b0 ]
 * after  i = 2: idxB <= 0 and thus
 * example:
 *   i = 3 -> a[idxA] = a[idxA] + null] =[ a3 ]+ 0
 *
 * when an addition is performed the carry if present is collected and returned
 */


/// adds two entries and cleans invalid inputs
/// - if idxA is invalid then a is extended in the front
/// - if idxB is invalid then nothing needs to be done
/// - if both indexes are valid a normal addition is performed
/// @param a number that receives the result and acts as operand
/// @param b other operand
/// @param idxA index points to value that should be added (can be less than 0)
/// @param idxB index points to value that should be added (can be less than 0)
/// @return true if an addition resulted in an overflow
bool addBIfPossible(BigInt &a, const BigInt &b, const int idxA, const int idxB) {
    if(idxA<0) {
        a.number.push_back(b.number.at(idxB));
        return false;
    }
    if(idxB<0) {
        return false;
    }
    return __builtin_add_overflow(a.number.at(idxA),b.number.at(idxB), &a.number.at(idxA));
}
/// adds 1 to an entry and cleans invalid inputs
/// - if idxA is invalid then a is extended in the front
/// - if idxA is valid a normal addition is performed
/// @param a number that receives the result and acts as operand
/// @param idxA index points to value that should be added (can be less than 0)
/// @return true if an addition resulted in an overflow
bool addOneIfPossible(BigInt &a,  const int idxA) {
    if(idxA<0) {
        a.number.push_back(1);
        return false;
    }
    return __builtin_add_overflow(a.number.at(idxA),1, &a.number.at(idxA));
}

/// The addition is performed by iterating over all indexes of the number with a higher length
/// Two indexes are used to keep track of the numbers that should be added together
/// - idxA starts at size of a minus one and gets smaller the bigger i gets (analog for idxB)
/// - idxA and idxB are the same distance away from their numbers ending
/// - example:
///  @code
///  a = [ a0 ] [ a1 ]
///  b = [ b0 ] [ b1 ] [ b2 ] [ b3 ] [ b4 ]
///   i = 1 -> a[idxA] = [ a0 ], b[idxB] = [ b3 ]
///   i = 3 -> a[idxA] =  null , b[idxB] = [ b1 ] etc.
///  @endcode
/// - adding is performed by helper methods that catch the possible negative indexes
/// - if a carry happened during one iteration an additional 1 is added to the number
/// - at the end if a carry is still present it is written into a new number that gets inserted at the front
/// @param a receives the result of the addition and acts as an operand
/// @param b other operand
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
    if(carry) a.number.push_back(1);
}

/// Performs an addition that is constructed by adding the corresponding entries of two BigInts
/// This is performed by individual adding and keeping track of overflows
/// @param other the other operand
void BigInt::operator+=(const BigInt &other) {
    addAB(*this ,other);
}

BigInt BigInt::operator+(const BigInt &other) const {
    BigInt result = *this;
    result+=other;
    return result;
}


/// The multiplication works by splitting the 2 number of length n in two parts
/// ((a1<<n/2)+a0) * ((b1<<n/2))
/// Then 3 products are calculated
/// a1 * b1 = c2
/// a0 * b0 = c1
/// (a1 + a0)*(b1+b0) = c0
/// Die folgende Formel setzt diese Teilprodukte zu einem gesamten zusammen
/// (c2<<n) + ((c0-c1-c2)<<n/2) + c1
/// @param other
BigInt BigInt::operator*(const BigInt &other) const{
    return BigInt(0);
}
//endregion