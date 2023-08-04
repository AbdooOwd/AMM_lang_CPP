#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

vector<string> known_keywords = {
    "whatif",
    "orelse",
    "endif",
    "log"
};

string get_code(const string& file_path) {
    ifstream program_file(file_path);
    return string(istreambuf_iterator<char>(program_file), {});
}

void run(const string& program) {
    string keyword = "";
    bool pause_scan = false;

    bool scanning_str = false;
    string scanned_str = "";
    int double_quotes_count = 0;

    for (char c : program) {
        string char_str(1, c);
        if (find(known_keywords.begin(), known_keywords.end(), keyword) != known_keywords.end()) {
            pause_scan = true;
            if (keyword == "log") {
                if (c == '\"') {
                    double_quotes_count++;
                    scanning_str = !scanning_str;
                    continue;
                }
                if (scanning_str) {
                    scanned_str += char_str;
                }

                if (double_quotes_count == 2) {
                    cout << scanned_str << endl;

                    scanned_str = "";
                    scanning_str = false;
                    double_quotes_count = 0;

                    pause_scan = false;
                    continue;
                }
            } else if (keyword == "whatif") {
                // Handle "whatif" functionality
            } else if (keyword == "orelse") {
                // Handle "orelse" functionality
            } else if (keyword == "endif") {
                pause_scan = false;
            }
        }

        if (!pause_scan) {
            keyword += char_str;
            keyword.erase(keyword.find_last_not_of(" \n\r\t") + 1);
        }

        if (c == ';' || c == '\n') {
            keyword = "";
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <file_name>\n";
        return 1;
    }

    string filename = argv[1];
    string code = get_code(filename);
    run(code);
    return 0;
}
