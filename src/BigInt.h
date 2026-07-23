//
// Created by Jonathan Leopold on 11/04/2026.
//

#ifndef RSA_BIGINT_H
#define RSA_BIGINT_H
#include <cstdint>
#include <deque>
#include <string>
#include <vector>


class BigInt {

public:
    std::deque<uint64_t> number;
    bool isNegative{};

    //Constructors
    BigInt();
    explicit BigInt(int64_t value);
    explicit BigInt(const std::string&);
    explicit BigInt( size_t end,size_t start, const BigInt &source);

    //Printing
    void display() const;
    void displayHex() const;
    [[nodiscard]] static std::string uint64ToHex(const uint64_t &number);
    [[nodiscard]] std::string toHexString(const std::string& filler="") const;

    //Direct block manipulation
    void setNumber(const std::string&);
    static uint64_t getUint64(const std::string &str);
    // TODO
    BigInt getRange(size_t start, size_t end) const;
    void addBlocks(const uint64_t &amount);
    void adjustSize(const uint64_t &newSize);
    static void equalizeSize(BigInt &a, BigInt &b);
    //Bitwise Operators
    /* TODO
     * void operator~ ();
     * void operator&= (const BigInt &other);
     * void operator|= (const BigInt &other);
     * void operator^= (const BigInt &other);
     * void operator<< (const uint64_t &shiftAmount);
     * void operator>> (const uint64_t &shiftAmount);
     */
    //Arithmetic Operators
    void operator+= (const BigInt &other);
    BigInt operator+ (const BigInt &other) const;
    BigInt operator* (const BigInt &other) const;
    /* TODO
     * void operator++ ();
     * void operator-- ();
     */

};

#endif //RSA_BIGINT_H
