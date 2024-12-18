#include <iostream>
#include <sstream>
#include <iomanip>

std::string encodeQuotedPrintable(const std::string& input) {
    std::ostringstream encoded;
    size_t lineLength = 0;

    for (char c : input) {
        if ((c < 33 || c > 126 || c == '=')) {
            if (lineLength + 3 > 76) {
                encoded << "=\r\n";
                lineLength = 0;
            }
            encoded << '=' << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)(unsigned char)c;
            lineLength += 3;
        }
        else {
            if (lineLength + 1 > 76) {
                encoded << "=\r\n";
                lineLength = 0;
            }
            encoded << c;
            lineLength++;
        }
    }

    return encoded.str();
}
