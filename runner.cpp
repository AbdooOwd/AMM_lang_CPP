#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

std::vector<std::string> known_keywords = {
    "whatif",
    "orelse",
    "endif",
    "log"
};

string get_code(const string& file_path) {
    ifstream program_file(file_path);
    return string(istreambuf_iterator<char>(program_file), {});
}