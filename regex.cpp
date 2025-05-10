#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

// Global Declaration
vector<string> st;
vector<string> finalSt;
string startSt;
vector<tuple<string, string, string>> transition;
vector<string> symbols;

// Add Start0 and Final0 using epsilon transitions
void startFinal() {
    transition.push_back({"Start0", "E", startSt});
    for (const string &f : finalSt) {
        transition.push_back({f, "E", "Final0"});
    }
}

// Merge transitions with same source and destination
void merging() {
    for (size_t i = 0; i < transition.size(); ++i) {
        for (size_t j = i + 1; j < transition.size();) {
            if (get<0>(transition[i]) == get<0>(transition[j]) && get<2>(transition[i]) == get<2>(transition[j])) {
                string merged = get<1>(transition[i]) + "U(" + get<1>(transition[j])+")";
                transition[i] = {get<0>(transition[i]), merged, get<2>(transition[i])};
                transition.erase(transition.begin() + j);
            } else {
                j++;
            }
        }
    }
}

string simplifyRegex(const string regex) {
    string result = regex;

    // Remove outermost brackets if they enclose the entire expression unnecessarily
    while (result.size() >= 2 && result.front() == '(' && result.back() == ')') {
        int depth = 0;
        bool balanced = true;
        for (size_t i = 0; i < result.size(); ++i) {
            if (result[i] == '(') depth++;
            else if (result[i] == ')') depth--;

            // If at any point the parentheses close fully before the end, it's not outermost
            if (depth == 0 && i != result.size() - 1) {
                balanced = false;
                break;
            }
        }

        // If fully balanced and only at the end, strip one pair of outer brackets
        if (balanced) {
            result = result.substr(1, result.size() - 2);
        } else {
            break;
        }
    }

    return result;
}


// Generate Regular Expression
string regexForm() {
    startFinal();
    merging();

    for (const string &state : st) {
        vector<pair<string, string>> in, out;
        vector<string> loop;

        for (size_t j = 0; j < transition.size();) {
            string from = get<0>(transition[j]);
            string symbol = get<1>(transition[j]);
            string to = get<2>(transition[j]);

            if (from == state && to == state) {
                if (symbol != "E") loop.push_back(symbol);
                transition.erase(transition.begin() + j);
            } else if (to == state) {
                in.push_back({from, symbol});
                transition.erase(transition.begin() + j);
            } else if (from == state) {
                out.push_back({to, symbol});
                transition.erase(transition.begin() + j);
            } else {
                j++;
            }
        }

        string loopRegex = "";
        if (!loop.empty()) {
            loopRegex = "(" + loop[0];
            for (size_t i = 1; i < loop.size(); ++i)
                loopRegex += "U" + loop[i];
            loopRegex += ")*";
        }

        for (const auto &i : in) {
            for (const auto &o : out) {
                string left = (i.second == "E") ? "" : i.second;
                string right = (o.second == "E") ? "" : o.second;
                string expr = left + loopRegex + right;
                if (!expr.empty()) {
                    transition.push_back({i.first, expr, o.first});
                }
            }
        }
    }

    // Combine transitions from Start0 to Final0
    string finalExpr = "";
    for (const auto &t : transition) {
        if (get<0>(t) == "Start0" && get<2>(t) == "Final0") {
            if (!get<1>(t).empty()) {
                if (!finalExpr.empty())
                    finalExpr = "(" + finalExpr + ")U(" + get<1>(t) + ")";
                else
                    finalExpr = get<1>(t);
            }
        }
    }

    return simplifyRegex(finalExpr);
}


// Insert transitions from user input
void insertTransition() {
    cout << "Insert the Transition Table:\n";
    for (const string &s : st) {
        cout << "For state '" << s << "':\n";
        for (const string &sym : symbols) {
            string nextState;
            cout << "  On symbol '" << sym << "' goes to: ";
            cin >> nextState;
            transition.push_back({s, sym, nextState});
        }
    }
}

int main() {
    cout << "Enter the states in the DFA (type -1 to stop):\n";
    while (true) {
        string s;
        cin >> s;
        if (s == "-1") break;
        st.push_back(s);
    }

    cout << "\nEnter the Start State: ";
    cin >> startSt;

    cout << "\nEnter the Final States (type -1 to stop):\n";
    while (true) {
        string f;
        cin >> f;
        if (f == "-1") break;
        finalSt.push_back(f);
    }

    cout << "\nEnter the transition symbols (type -1 to stop):\n";
    while (true) {
        string sym;
        cin >> sym;
        if (sym == "-1") break;
        symbols.push_back(sym);
    }

    insertTransition();

    cout << "\n----------------------------------------\n";
    cout << "         TRANSITION TABLE               \n";
    cout << "----------------------------------------\n";
    cout << "STATE\t| SYMBOL\t| NEXT STATE\n";
    cout << "----------------------------------------\n";
    for (const auto &t : transition) {
        cout << get<0>(t) << "\t| " << get<1>(t) << "\t| " << get<2>(t) << endl;
    }

    string regexval = regexForm();

    cout << "\n----------------------------------------\n";
    cout << "The Regular Expression is: " << regexval << endl;
    cout << "----------------------------------------\n";
    return 0;
}

