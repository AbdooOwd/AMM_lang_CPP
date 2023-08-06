#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Available Keywords in A--
vector<string> known_keywords = {
    "whatif",
    "orelse",
    "endif",
    "log",
    "input",
    "var"
};

// Available Data types in A--
vector<string> data_types = {
    "int",
    "float",
    "str",
    "bool",
    "array"
};

struct Variable {
    string name;
    string type;
    string value;
};

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
    string keyword = "";
    bool pause_scan = false;

    // Str scanning stuff
    bool scanning_str = false;
    string scanned_str = "";
    int double_quotes_count = 0;

    // Vars
    vector<Variable> variables;
    
    string var_name;
    string var_type;
    bool scanning_var_name = true;

    for (char c : program) {
        if (keyword == "var") { // Handle variable declarations
            pause_scan = true;

            // Skip white spaces and move to variable name
            if (c == ' ') {
                continue;
            }

            // Scan variable name
            if (scanning_var_name == true) {
                if (c == ' ') {
                    scanning_var_name = false;
                } else {
                    var_name += c;
                }
            }

            // Skip white spaces and move to variable type
            if (c == ' ') {
                continue;
            }

            // Scan variable type
            if (c != ' ') {
                var_type += c;
            }

            cout << "Var: " << var_name << " | Type: " << var_type << endl;

            // Add the variable to the list
            Variable new_var;
            new_var.name = var_name;
            new_var.type = var_type;
            new_var.value = ""; // Initialize with an empty value
            variables.push_back(new_var);

            keyword = ""; // Reset the keyword
            continue;
        }

        if (keyword == "log") { // Handle log statements
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
                keyword = "";
                continue;
            }
        }

        if (keyword == "input") { // Handle input statements
            string user_input;
            cin >> user_input;
            // You might want to handle type conversion here based on the variable's data type.
            // For simplicity, we'll skip this part in this example.
        }

        // Existing code...

        if (pause_scan == false && c != ';' && c != '\n' && c != ' ') {
            keyword += c;
        }

        if (c == ';') {
            keyword = "";
            continue;
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

    run(code);

    return 0;
}
