#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>

#ifdef mod_enabled
    #include <json/value.h> // For keyword modding
#endif

using namespace std;

#pragma GCC diagnostic ignored "-Wconversion-null"
#pragma GCC diagnostic ignored "-Wpointer-arith"


// Available Keywords in A--

bool mod_enabled = false; // Make this true to be able to mod the lang using JSON (still a WIP)

// Error handling (not sophisticated)
bool errorFound = false;

vector<string> known_keywords = {
    "whatif",
    "orelse",
    "endif",
    "log",
    "input",
    "var",
    "math"
};

vector<string> math_operators = {
    "+",
    "-",
    "*",
    "/"
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


// Originally in run func

string keyword = "";
bool pause_scan = false;
// Comment detection
bool isComment = false;


// Any scanning stuff
string scanned_thing = "";
int i_counter = 0;
int cur_line = 1;


// --- log
bool scanning_str = false;
string scanned_str = "";
int double_quotes_count = 0;


// --- Vars
vector<Variable> variables;
    
string var_name;
string var_type;
string var_value;
string varNextScan = "name";
int space_count = 0;
bool scanning_var_name = false;
bool scanned_var_name = false;
enum VarNextScan {
    VAR_NAME,
    VAR_TYPE,
    VAR_VALUE
};


// Var resetting
vector<string> var_props_str = {
    var_name,
    var_type,
    var_value
};
vector<bool> var_props_bool = {
    scanning_var_name,
    scanned_var_name
};


// --- math
bool start_scan = false;
bool show_work = false;
int number1 = NULL;
int number2 = NULL;
string cur_operator = "";


// --- If stuff
bool isInCondition = false;
string condition1 = "";
string condition2 = "";
char cur_conditioner = NULL;
bool condition_success;


// Some Todos

// TODO: Improve error handling
// TODO: Add 'orelse'
// TODO: Improve the if system with more conditions in one
// TODO: Store input


string getVar(vector<Variable> variable_array, int m_address);


// ### Tools funcs

// Function template to reset any variable to its default value
template <typename T>
void resetToDefault(T& variable) {
    if constexpr (std::is_same_v<T, bool>) {
        variable = false; // Set boolean variables to true
    } else if constexpr (is_same_v<T, string>) {
        variable = "";
    } else if constexpr (is_same_v<T, int>) {
        variable = 0;
    } else if constexpr (is_same_v<T, double>) {
        variable = 0.0;
    } else if constexpr (is_same_v<T, char>) {
        variable = NULL;
    }
    
    else {
        variable = T{}; // Assign the default value to the variable
    }
}

template <typename T>
void resetArrVars(vector<T> arr) {
    for (T var : arr) {
        resetToDefault(var);
    }
}

// To check if an array has a certain element inside it
template <typename T>
bool arrayHas(vector<T>& arr, const T& element) {
    auto it = find(arr.begin(), arr.end(), element);
    return (it != arr.end());
}

bool isSpaceLine(char character) {
    if (character == ' ' || character == '\n') return true;
    else return false;
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

void show_err(string error_message) {
    cout << "[ERROR] : " << cur_line <<" > " << error_message << endl;
}

template <typename T>
bool check_condition(const T& our_condition1, const T& our_condition2, char cur_conditioner) {
    switch (cur_conditioner) {
        case '=':
            return our_condition1 == our_condition2;
        case '>':
            return our_condition1 > our_condition2;
        case '<':
            return our_condition1 < our_condition2;
        default:
            return false;
    }
}

bool lazy_check_cond(string cond1, string cond2, char condener) {
    cout << cond1 << " " << cond2 << " " << condener << endl;

    if (cond1 == cond2) return true;
    else return false;
}

// Variable funcs

string getVarValue(vector<Variable> variable_array, int m_address) {

int arr_size = 0; // FIXME: Add Array Size

    if ((arr_size - 1) < m_address) {
        cout << " Tried Getting: " << m_address << " - Array's size: " << arr_size << endl;
        return "M_ADDRESS TOO BIG";
    }

    string toReturn = variable_array[m_address].value;
    if (toReturn != "") return toReturn;
    else return "NULL";
}



void run(const string& program) {
    char conditioner = NULL;

    for (char c : program) {

        if (c == '\n') {
            cur_line++;
        }

        if (keyword == "whatif") {

            if (isInCondition == true) {
                show_err("Already in an 'if' statement");
                break;
            }

            pause_scan = true;

            if (isSpaceLine(c)) continue;

            if (c == '>' || c == '<' || c == '=' || c == ';') {
                if (condition1 == "") condition1 = scanned_thing;
                else condition2 = scanned_thing;

                resetToDefault(scanned_thing);
                if (conditioner == NULL) {
                    conditioner = c;
                }
            }

            if (c != '<' && c != '>' && c != '=' && c != ';') {
                scanned_thing += c;
                continue;
            }

            if (condition1 != "" && condition2 != "" && c == ';') {
                cur_conditioner = conditioner;

                // Checking the success of the condition
                condition_success = check_condition(condition1, condition2, conditioner);

                if (condition_success) {

                    pause_scan = false;
                } else {
                    pause_scan = true;
                }

                isInCondition = true; // We start the IF statemen
                resetToDefault(keyword);
                
                continue;
            }
        }

        else if (keyword == "orelse" && isInCondition == true) {
            // Else system

        }

        else if (keyword == "endif" && isInCondition == true) {

            resetToDefault(conditioner);
            resetToDefault(condition1);
            resetToDefault(condition2);

            isInCondition = false;
            resetToDefault(keyword);
        }

        else if (keyword == "math") {

            pause_scan = true;

            if (isSpaceLine(c)) continue;

            if (c == '_') show_work = true;

            if (c != ' ' && start_scan == false) {
                start_scan = true;
            }

            if (start_scan == true) {
                if (isSpaceLine(c)) continue;

                if ((  arrayHas<string>(math_operators, string(1, c))  ) || (c == ';')) {
                    if (arrayHas<string>(math_operators, string(1, c))) {
                        cur_operator = string(1, c);
                    }
                    
                    if (number1 == NULL) {
                        number1 = stoi(scanned_thing);
                    } else {
                        number2 = stoi(scanned_thing);
                    }
                    resetToDefault(scanned_thing);
                    //continue;
                }
                if (!isSpaceLine(c) && c != ';' && c != '.' && c != '_'
                 && !(arrayHas<string>(math_operators, string(1, c)))) {
                    scanned_thing += c;
                    continue;
                }
            }

            if ((number1 != NULL) && (number2 != NULL)) {
                //cout << "Mathy: " << number1 << " " << cur_operator << " " << number2 << endl;
                //cout << "Result: " << (number1 + number2) << endl;

                double result = 0.0;

                if (cur_operator == "+") {
                    result = (number1+number2);
                } else if (cur_operator == "-") {
                    result = (number1-number2);
                } else if (cur_operator == "/") {
                    result = (number1/number2);
                } else if (cur_operator == "*") {
                    result = (number1*number2);
                }

                if (show_work == true)
                    cout << number1 << " " << cur_operator << " " << number2 << " = " << result << endl;
                else
                    cout << result << endl;
                
                start_scan = false;
            }

            if (c == ';') {
                resetToDefault(keyword);
                resetToDefault(scanned_thing);
                number1 = NULL;
                number2 = NULL;
                resetToDefault(cur_operator);
                resetToDefault(start_scan);
                pause_scan = false;
            }
        }

        else if (keyword == "var") { // Handle variable declarations

            pause_scan = true;

            // Skip white spaces and move to variable name
            if (isSpaceLine(c) && scanning_var_name == false && scanned_var_name == false) {
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

                } else if (isSpaceLine(c)) {
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
                if (isSpaceLine(c)) continue;
                var_type += c;
                continue;
            }

            if (c != ';' && varNextScan == "value") {
                if (isSpaceLine(c)) continue;
                var_value += c;
                continue;
            }

            if (c == ';') {
                // Add the variable to the list
                Variable new_var;
                new_var.name = var_name;
                if (var_type != "") new_var.type = var_type;
                if (var_value != "") new_var.value = var_value; // Initialize with an empty value (coming soon [; )
                variables.push_back(new_var);

                // Resets the var scanning properties
                /*var_name = "";
                var_type = "";
                var_value = "";
                space_count = 0;
                scanning_var_name = false;
                scanned_var_name = false;*/

                resetArrVars(var_props_str);
                resetArrVars(var_props_bool);
                resetToDefault(space_count);

                keyword = ""; // Reset the keyword

                pause_scan = false;
            }
        }

        else if (keyword == "log") { // Handle log statements
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

        else if (keyword == "input") { // Handle input statements
            string user_input;
            cin >> user_input;
            // You might want to handle type conversion here based on the variable's data type.
            // For simplicity, we'll skip this part in this example.
        }

        else if (keyword == "getvar") {
            pause_scan = true;

            if (c == ';') continue;

            int m_address;
            string varValue;

            if (c == ' ' || c == ';') continue;

            // FIXME: `c` not converting to int properly
            cout << c << endl;
            m_address = (int) c;
            varValue = getVarValue(variables, m_address);
            cout << varValue << endl;

            pause_scan = false;
        }

        // DEV
        else if (keyword == "getvars") {
            for (int i = 0; i < sizeof(variables); i++) {
                cout << variables[i].name << ": " << variables[i].type << " = " << variables[i].value << endl;
            }
        }

        else if (pause_scan == false && c != ';' && c != '\n' && c != ' ') {
            keyword += c;
        }

        else if (isComment == true && c == '\n') {
            resetToDefault(keyword);
            pause_scan = false;
            isComment = false;
            continue;
        }

        else if (c == '#' && isComment == false) {
        resetToDefault(keyword);
            pause_scan = true;
            isComment = true;
            continue;
        }

        if (c == ';') {
            pause_scan = false;
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

    if (errorFound == true) {
        return 1;
    }

    return 0;
}
