#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std; 

bool needsEncoding(char c) {
    return !(
        (c >= 33 && c <= 60) || (c >= 62 && c <= 126) || c == '\t' || c == ' ');
}

string encodeQuotedPrintable(const string& input) {
    ostringstream encoded;
    int lineLength = 0;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (lineLength >= 73) {
            encoded << "=" << "\r\n";
            lineLength = 0;
        }

        if (needsEncoding(c)) {
            encoded << "=" << std::uppercase << hex << setw(2) << setfill('0') << (int)(unsigned char)c;
            lineLength += 3;
        }
        else {
            if (c == ' ' || c == '\t') {
                if (i == input.size() - 1 || input[i + 1] == '\n' || input[i + 1] == '\r') {
                    encoded << "=" << uppercase << hex << setw(2) << setfill('0') << (int)(unsigned char)c;
                    lineLength += 3;
                }
                else {
                    encoded << c;
                    lineLength += 1;
                }
            }
            else {
                encoded << c;
                lineLength += 1;
            }
        }
    }

    return encoded.str();
}

string decodeQuotedPrintable(const string& input) {
    ostringstream decoded;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '=' && i + 2 < input.size()) {
            if (input[i + 1] == '\r' && input[i + 2] == '\n') {
                i += 2;
            }
            else {
                istringstream hexValue(input.substr(i + 1, 2));
                int value;
                hexValue >> hex >> value;
                decoded << static_cast<char>(value);
                i += 2;
            }
        }
        else {
            decoded << input[i];
        }
    }
    return decoded.str();
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string text = "name = Сергей ";

    string encoded = encodeQuotedPrintable(text);
    cout << "Encoded: " << encoded << endl;

    string decoded = decodeQuotedPrintable(encoded);
    cout << "Decoded: " << decoded << endl;

    return 0;
}
