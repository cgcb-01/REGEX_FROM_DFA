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

//startFinal
void startFinal()
{
   transition.push_back(make_tuple("Start0","ε",startSt)); //start state
   for(int i=0;i<finalSt.size();i++)
    transition.push_back(make_tuple(finalSt[i],"ε","Final0"));//Final state
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
