//
// Created by Jonathan Leopold on 11/04/2026.
//

#ifndef RSA_BIGINT_H
#define RSA_BIGINT_H
#include <cstdint>
#include <string>
#include <vector>


class BigInt {
    private:
    std::vector<uint64_t> number;
    bool isNegative;
    [[nodiscard]] static std::string uint64ToHex(const uint64_t &number);
    public:
    BigInt();
    explicit BigInt(int64_t value);
    explicit BigInt(const std::string&);
    void display() const;
    void displayHex() const;
    [[nodiscard]] std::string toHexString() const;
    void operator+= (const BigInt &other);
    BigInt operator+ (const BigInt &other) const;
};

#endif //RSA_BIGINT_H
