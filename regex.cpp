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


//Finding the regular expression
string regexForm()
{
   void startFinal(); 
    
}

// Finding the transition Table
void insertTransition()
{
    cout << "Insert the Transition Table:" << endl;
    for (int i = 0; i < st.size(); i++)
    {
        cout << "For " << st[i] << ", insert the transitions:\n";
        for (int j = 0; j < symbols.size(); j++)
        {
            string nextState;
            cout << "  On symbol '" << symbols[j] << "' goes to: ";
            cin >> nextState;
            transition.push_back(make_tuple(st[i], symbols[j], nextState));
        }
    }
}

int main()
{
    // Input the States
    cout << "Enter the states in the DFA:\n";
    while (true)
    {
        string s;
        cout << "State: ";
        cin >> s;
        st.push_back(s);
        char choice;
        cout << "Continue adding states (y/n)? ";
        cin >> choice;
        if (choice != 'y') break;
    }
