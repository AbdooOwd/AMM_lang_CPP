#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> known_keywords = {
    "whatif",
    "orelse",
    "endif",
    "log"
};

string get_code(const string& file_path) {
    ifstream program_file(file_path);
    if (!program_file.is_open()) {
        cerr << "Error opening the file." << endl;
        return "";
    }
    string code((istreambuf_iterator<char>(program_file)), {});
    return code;
}

void run(const string& program) {
    // Very important function
    string keyword = "";
    bool pause_scan = false;

    // Str scanning stuff
    bool scanning_str = false;
    string scanned_str = "";
    int double_quotes_count = 0;

    for (char c : program) { // Checks every character in the .amm file
        if (keyword == "log") { // Print function
            pause_scan = true;
            if (c == '\"') {
                double_quotes_count++;
                scanning_str = !scanning_str;
                continue;
            }
            if (scanning_str == true) {
                scanned_str += c;
            }

            if (double_quotes_count == 2) {
                cout << scanned_str << endl;

                scanned_str = "";
                scanning_str = false;
                double_quotes_count = 0;

                pause_scan = false;

                continue;
            }
        }

        if (pause_scan == false) {
            keyword += c;
            //keyword.erase(remove(keyword.begin(), keyword.end(), ' '), keyword.end());
        }

        if (c == ';') {
            keyword = "";
            continue;
        }

        if (keyword == "whatif") {
            // Implement the logic for "whatif" keyword
            // For example, check some conditions and execute code accordingly
        } else if (keyword == "orelse") {
            // Implement the logic for "orelse" keyword
            // For example, execute some other code
        } else if (keyword == "endif") {
            // Implement the logic for "endif" keyword
            // For example, handle the end of a block or condition
        } else {
            bool is_known_keyword = false;
            for (const string& known_keyword : known_keywords) {
                if (keyword == known_keyword) {
                    is_known_keyword = true;
                    break;
                }
            }

            //if (!is_known_keyword) {
            //    cout << " [ERROR]" << endl;
            //}
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: <compiler path> <filename.amm>" << endl;
        return 1;
    }

    string filename = argv[1];
    string code = get_code(filename);

    // Printing the code content
    // cout << "Content of " << filename << ":\n";
    // cout << code << endl;

    run(code);

    return 0;
}
