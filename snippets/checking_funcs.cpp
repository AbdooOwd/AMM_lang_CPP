#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// Available Data types in A--
vector<string> data_types = {
    "int",
    "float",
    "str",
    "bool",
    "array"
};


// Some checking funcs

bool isInteger(const std::string& s) {
    try {
        size_t pos;
        std::stoi(s, &pos);
        return pos == s.length();
    } catch (std::invalid_argument&) {
        return false;
    } catch (std::out_of_range&) {
        return false;
    }
}

bool isFloat(const std::string& s) {
    try {
        size_t pos;
        std::stof(s, &pos);
        return pos == s.length();
    } catch (std::invalid_argument&) {
        return false;
    } catch (std::out_of_range&) {
        return false;
    }
}

bool isDouble(const std::string& s) {
    try {
        size_t pos;
        std::stod(s, &pos);
        return pos == s.length();
    } catch (std::invalid_argument&) {
        return false;
    } catch (std::out_of_range&) {
        return false;
    }
}

bool isValidDataType(const string& type) {
    return find(data_types.begin(), data_types.end(), type) != data_types.end();
}

bool isValidValueForType(const string& value, const string& type) {
    if (type == "int") {
        return isInteger(value);
    } else if (type == "float") {
        return isFloat(value);
    } else if (type == "str") {
        return true;
    } else if (type == "bool") {
        return (value == "true" || value == "false");
    } else if (type == "array") {
        // Implement the logic to check if the value is a valid array representation
        // (e.g., "[1, 2, 3]") based on your language's array syntax rules.
        // For simplicity, we'll skip this part in this example.
        return true;
    } else {
        return false;
    }
}