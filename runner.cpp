#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string get_code(string file_path, bool per_line = false) {

    ifstream code_file(file_path); // Gets file
    if (!code_file.is_open()) { // Checks if the file exists
        cout << "Error opening the file." << endl;
        return "";
    }

    if (per_line == false) { // Gets file content
        std::string content((std::istreambuf_iterator<char>(code_file)),
        std::istreambuf_iterator<char>());
        std::cout << content << std::endl;
    } else {
        std::string line;
        while (std::getline(code_file, line)) {
        // Process the line here
        std::cout << line << std::endl;
        }
    }

}

void run(string file_path) {

    string code = get_code(file_path); // Stores the file content in `code` variable

}


int main(int argc, char const *argv[]) {
    // The command to run the program is "gcc main.cpp -lstdc++ -o main.o"
    get_code(argv[1]);
    return 0;
}
