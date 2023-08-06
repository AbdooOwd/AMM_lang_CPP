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

string getVar(vector<Variable> variable_array, int m_address);




// Tools funcs

// TODO: Add a function that takes an array of variables and resets each one
void reset_props();

// To check if an array has a certain element inside it
bool strArrHas(vector<string> da_array, string what); // TODO: Add This strArrHas func

/*bool varExists(vector<Variable> variable_array, string var_name) {
    return find(variable_array.begin(), variable_array.end(), var_name) != variable_array.end();
}*/


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


// A-- functions to work

string get_code(const string& file_path) {
    ifstream program_file(file_path);
    if (!program_file.is_open()) {
        cerr << "Error opening the file." << endl;
        return "";
    }
    string code((istreambuf_iterator<char>(program_file)), {});
    return code;
}

// Variable funcs

string getVarValue(vector<Variable> variable_array, int m_address) {
    string toReturn = variable_array[m_address].value;
    if (toReturn != "") return toReturn;
    else return "NULL";
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
    string var_value;
    int space_count = 0;
    bool scanning_var_name = false;
    bool scanned_var_name = false;
    string varNextScan = "name";
    enum VarNextScan {
        VAR_NAME,
        VAR_TYPE,
        VAR_VALUE
    };


    for (char c : program) {
        if (keyword == "var") { // Handle variable declarations

            // TODO: Add that variables can either be declared without type but with value or without value but with type
            // TODO: Add `getvar` keyword to get variable base on its M-Address

            pause_scan = true;

            // Skip white spaces and move to variable name
            if ((c == ' ' || c == '\n') && scanning_var_name == false && scanned_var_name == false) {
                scanning_var_name = true;
                varNextScan = "name";
            }

            // Scan variable name
            if (scanning_var_name == true) {
                if (c == ':' || c == '=') {
                    scanning_var_name = false;
                    scanned_var_name = true;

                    if (c == ':') varNextScan = "type";
                    if (c == '=') varNextScan = "value";

                } else if (c == ' ' || c == '\n') {
                    continue;
                } else {
                    var_name += c;
                }
                continue;
            }

            // Scan variable type
            if (c != ';' && varNextScan == "type") {
                if (c == '=') {
                    varNextScan = "value";
                    continue;
                }
                if (c == ' ' || c == '\n') continue;
                var_type += c;
                continue;
            }

            if (c != ';' && varNextScan == "value") {
                if (c == ' ' || c == '\n') continue;
                var_value += c;
                continue;
            }

            //cout << " - Var: " << var_name << " | Type: " << var_type << endl;

            // Add the variable to the list
            Variable new_var;
            new_var.name = var_name;
            if (var_type != "") new_var.type = var_type;
            if (var_value != "") new_var.value = var_value; // Initialize with an empty value (coming soon [; )
            variables.push_back(new_var);

            // Resets the var scanning properties
            var_name = "";
            var_type = "";
            var_value = "";
            space_count = 0;
            scanning_var_name = false;
            scanned_var_name = false;

            keyword = ""; // Reset the keyword

            pause_scan = false;
        }

        if (keyword == "log") { // Handle log statements
            pause_scan = true;

            bool new_line = true;

            if (c == '\"') {
                double_quotes_count++;
                scanning_str = !scanning_str;
                continue;
            }
            if (scanning_str == true) {
                if (c == '\n') {
                    scanned_str += " ";
                    continue;
                }
                if (c == '~') {
                    scanned_str += "\n";
                    continue;
                }
                scanned_str += c;
                continue;
            }
            if (double_quotes_count == 2) {

                if (c == '-') {
                    new_line = false;
                }

                if (new_line == true) cout << scanned_str << endl;
                else cout << scanned_str;

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

        if (keyword == "getvar") {
            pause_scan = true;

            int m_address;
            string varValue;

            if (c == ' ') continue;

            m_address = (int) c;
            varValue = getVarValue(variables, 0);
            cout << varValue << endl;

            pause_scan = false;
        }

        // DEV
        if (keyword == "getvars") {
            for (int i = 0; i < sizeof(variables); i++) {
                cout << variables[i].name << ": " << variables[i].type << " = " << variables[i].value << endl;
            }
        }

        if (pause_scan == false && c != ';' && c != '\n' && c != ' ') {
            keyword += c;
        }

        if (c == ';') { // TODO: Add comments
            keyword = "";
            continue;
        }
    }
}


// So simple... The main funciton... hahaha

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: <compiler path> <filename.amm>" << endl;
        return 1;
    }

    string filename = argv[1];
    string code = get_code(filename);

    run(code); // This is where EVERYTHING happens

    return 0;
}
