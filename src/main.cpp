#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "BigInt.h"

/// Splits a string by a delimiter
/// @param str the string that needs splitting into items
/// @param delimiter used for determining the start and end of items
/// @return a vector that contains the items split by the delimiter
std::vector<std::string> split(const std::string &str, const char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        if (!item.empty()) result.push_back(item);
    }
    return result;
}

std::optional<std::string> readFile(const std::string &fileName) {
    std::ifstream fileHandle(fileName);
    if (!fileHandle.is_open()) {
        return nullptr;
    }
    std::string myText;
    std::string fileContent;
    while (std::getline(fileHandle, myText)) {
        fileContent += myText;
    }
    fileHandle.close();
    return fileContent;
}

struct sshRsaItem {
    uint32_t length;
    BigInt value;
};

int testReadFile() {
    //std::cout << "Try opening id_rsa.pub file.\nThe current path is "<<std::filesystem::current_path() << "!\n";
    std::string fileName =R"(..\KeyData\id_rsa.pub)";
    std::string fileName2 =R"(..\test.txt)";
    auto fileContent = readFile(fileName);
    if(!fileContent.has_value()) {
        std::cout << "Failed to open" << fileName << "!\n";
        return -1;
    }
    auto items = split(fileContent.value(), ' ');
    for (auto &item : items) {
        std::cout <<"=====================\n"<< item<<std::endl;
    }
    std::cout <<"Length of vector: "<< items.size() << std::endl;
    return 0;
}
int testBigInt() {
    auto a = BigInt(UINT64_MAX);
    auto b = BigInt(20);
    a.displayHex();
    b.displayHex();
    std::cout <<"=====================\n";
    auto c = a + b;
    c.display();
    c.displayHex();
    return 0;
}

/// This is the main entry point
/// @return error code
int main() {
    //return testReadFile();
    //testBigInt();
    // const std::string aAsStr= "1fffffffffffffffffffffffffffffffff";
    // const std::string bAsStr= "fffffffffff";
    //
    //
    // auto a = BigInt(aAsStr);
    // auto b = BigInt(bAsStr);
    // a+=b;
    // a+=BigInt(1);

    auto toSplittingIdx = [](size_t s) {
        uint64_t nearest2power =std::ceil( std::log2(s));
        return (1<<(nearest2power-1));
    };
    for (size_t s = 1; s<20; s++) {
        std::cout <<s<<"\t:\t"<< toSplittingIdx(s)<<std::endl;
    }
    // 1                [0] -> splitting idx = 1
    // 2             [1][0] -> splitting idx = 1
    // 3          [2][1][0] -> splitting idx = 2
    // 4       [3][2][1][0] -> splitting idx = 2
    // 5    [4][3][2][1][0]

}

