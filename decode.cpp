#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>

std::string decodeQuotedPrintable(const std::string& input) {
    std::ostringstream decoded;
    size_t i = 0;

    while (i < input.size()) {
        if (input[i] == '=') {

            if (i + 1 < input.size() && input[i + 1] == '\r' && input[i + 2] == '\n') {
                i += 3;
            }
            else if (i + 2 < input.size()) {

                std::string hexCode = input.substr(i + 1, 2);
                char decodedChar = static_cast<char>(std::stoi(hexCode, nullptr, 16));
                decoded << decodedChar;
                i += 3;
            }
            else {
                throw std::invalid_argument("Invalid Quoted-Printable encoding");
            }
        }
        else {
            decoded << input[i];
            i++;
        }
    }

    return decoded.str();
}
