#include <iostream>
#include <sstream>
#include <iomanip>

#ifndef QUOTED_PRINTABLE_H
#define QUOTED_PRINTABLE_H

#include <string>

std::string encodeQuotedPrintable(const std::string& input);
std::string decodeQuotedPrintable(const std::string& input);

#endif 

int main() {
    setlocale(LC_ALL, "rus");
    std::string input = "Сергей";
    std::string encoded = encodeQuotedPrintable(input);
    std::cout << "Encoded:\n" << encoded << "\n\n";
    try {
        std::string decoded = decodeQuotedPrintable(encoded);
        std::cout << "Decoded:\n" << decoded << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error decoding: " << e.what() << "\n";
    }

    return 0;
}
