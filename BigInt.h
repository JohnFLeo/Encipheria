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
    public:
    BigInt();
    explicit BigInt(int64_t);
    explicit BigInt(const std::string&);
    void putAt(size_t index, uint64_t number);
    void display() const;
    BigInt operator+ (const BigInt &other) const;

};

#endif //RSA_BIGINT_H
