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
    [[nodiscard]] static std::string uint64ToHex(const uint64_t &number);

    BigInt();
    explicit BigInt(int64_t value);
    explicit BigInt(const std::string&);
    void display() const;
    void displayHex() const;
    [[nodiscard]] std::string toHexString() const;
    static uint64_t getUint64(const std::string &str);
    void setNumber(const std::string&);
    void operator+= (const BigInt &other);
    BigInt operator+ (const BigInt &other) const;
};

#endif //RSA_BIGINT_H
