#include <iostream>
#include <stack>
#include <string>
#include <vector>


using namespace std;

template<typename T> class Parsing {
public:
// Function to parse the input string
bool parse_Input(string input) {
    vector<int> stk;
    stk.push_back(0);  // Push initial state
    
    // Parsing table
    int parsingTable[12][9] = {
        {5, 0, 0, 4, 0, 0},
        {0, 6, 0, 0, 0, -7},
        {0, -2, 7, 0, -2, -2},
        {0, -4, -4, 0, -4, -4},
        {5, 0, 0, 4, 0, 0},
        {0, -6, -6, 0, -6, -6},
        {5, 0, 0, 4, 0, 0},
        {5, 0, 0, 4, 0, 0},
        {0, 6, 0, 0, 11, -3},
        {0, -1, 7, 0, -1, -1},
        {0, -3, -3, 0, -3, -3},
        {0, -5, -5, 0, -5, -5}
    };
    int gotoTable[12][3] = {
        {1, 2, 3},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {8, 2, 3},
        {0, 0, 0},
        {0, 9, 3},
        {0, 0, 10},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    cout << "Input: " << input << endl;
    cout << "Stack:" << endl;
    cout << "Step\tStack <--\tInput  \t\tTable\t\tAction" << endl;
    int count = 0;
    while (count <= input.size()-1) {
        
        int currentState = stk.back();
        
        int currentSymbol;
        cout << "-" << "\t";
        for (int i =0; i < stk.size(); i++)
        {
            cout << stk[i] << " ";
        }
        cout << "\t\t" << input.substr(count) << "\t\t";

        // Check for 'id' token
        if (input[count] == 'i' && count + 1 < input.size() && input[count + 1] == 'd') {
            currentSymbol = 0; // 'id' token
            count++;
        } else {
            switch (input[count]) {
                case '+': currentSymbol = 1; break;
                case '*': currentSymbol = 2; break;
                case '(': currentSymbol = 3; break;
                case ')': currentSymbol = 4; break;
                case '$': currentSymbol = 5; break;
                default: return false; // Invalid input
            }
        }

        int action = parsingTable[currentState][currentSymbol];


        // Print stack contents
        

        if (action == 0) {
            cout << "Invalid input";
            return false;
        }
        else if (action == -1) {
            cout << "R" << parsingTable[currentState][currentSymbol]/-1 << "\t\t";
            cout << "Reduce by E -> E + T";
            stk.pop_back();
            stk.pop_back();
            stk.pop_back();

            stk.push_back(gotoTable[stk[stk.size()-1]][0]);


        } else if (action == -2) {
            cout << "R" << parsingTable[currentState][currentSymbol]/-1 << "\t\t";
            cout << "Reduce by E -> T";
            stk.pop_back();
            stk.push_back(gotoTable[stk[stk.size()-1]][0]);


        } else if (action == -3) {
            cout << "R" << parsingTable[currentState][currentSymbol]/-1 << "\t\t";
            cout << "Reduce by T -> T * F";
            stk.pop_back(); stk.pop_back(); stk.pop_back();
            stk.push_back(2);


        } else if (action == -4) {
            cout << "R" << parsingTable[currentState][currentSymbol]/-1 << "\t\t";
            cout << "Reduce by T -> F";
            stk.pop_back(); 
            stk.push_back(gotoTable[stk[stk.size()-1]][1]);
        } else if (action == -5) {
            cout << "R" << parsingTable[currentState][currentSymbol]/-1 << "\t\t";
            cout << "Reduce by F -> (E)";
            stk.pop_back();
            stk.pop_back();
            stk.pop_back();

            stk.push_back(gotoTable[stk[stk.size()-1]][2]);

        } else if (action == -6) {
            cout << "R" << parsingTable[currentState][currentSymbol]/-1 << "\t\t";
            cout << "Reduce by F -> id" <<  gotoTable[stk[stk.size()-1]][2];
            stk.pop_back();
            stk.push_back(gotoTable[stk[stk.size()-1]][2]);
            cout << stk[stk.size()-1];
        }
     else if (action == 1) {
            cout << "S" << parsingTable[currentState][currentSymbol] << "\t\t";
            cout << "Shift to state " << parsingTable[currentState][currentSymbol];
            stk.push_back(parsingTable[currentState][currentSymbol]);
                        count++;

        } else if (action == 2) {
            cout << "S" << parsingTable[currentState][currentSymbol] << "\t\t";
            cout << "Shift to state " << parsingTable[currentState][currentSymbol];
            stk.push_back(parsingTable[currentState][currentSymbol]);
                        count++;

        } else if (action == 3) {
            cout << "S" << parsingTable[currentState][currentSymbol] << "\t\t";
            cout << "Shift to state " << parsingTable[currentState][currentSymbol];
            stk.push_back(parsingTable[currentState][currentSymbol]);
                        count++;

        }else if (action == 4) {
            cout << "S" << parsingTable[currentState][currentSymbol] << "\t\t";
            cout << "Shift to state " << parsingTable[currentState][currentSymbol];
            stk.push_back(parsingTable[currentState][currentSymbol]);
                        count++;

        }else if (action == 5) {
            cout << "S" << parsingTable[currentState][currentSymbol] << "\t\t";
            cout << "Shift " << parsingTable[currentState][currentSymbol];
            stk.push_back(parsingTable[currentState][currentSymbol]);
                        count++;

        }else if (action == 6) {
            cout << "S" << parsingTable[currentState][currentSymbol] << "\t\t";
            cout << "Shift to state " << parsingTable[currentState][currentSymbol];
            stk.push_back(parsingTable[currentState][currentSymbol]);
                        count++;

        }else if (action == 7) {
            cout << "S" << parsingTable[currentState][currentSymbol] << "\t\t";
            cout << "Shift to state " << parsingTable[currentState][currentSymbol];
            stk.push_back(parsingTable[currentState][currentSymbol]);
            count++;

        }else if (action == -7) {
            cout << "Accept";
            return true;
        }else if (action == 0) {
            cout << "Error";
            return false;
        } else {
            cout << "S" << action << "\t\t";
            cout << "Shift to state " << action;
            stk.push_back(action);
                        count++;

        }

        cout << endl;
    }

    return false;
}
};

int main() {
    // Test input strings
    string inputs[] = {"(id+id)*id$", "id*id$", "(id*)$"};
    int numInputs = sizeof(inputs) / sizeof(inputs[0]);
    Parsing<string> pf1;

    for (int i = 0; i < numInputs; ++i) {
        bool result = pf1.parse_Input(inputs[i]);
        cout << (result ? "\nAccepted" : "\nRejected") << endl << endl;
    }
    

    return 0;
}
