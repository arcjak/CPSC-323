#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

// Define tokens
enum class Token { ID, PLUS, MULTIPLY, LEFT_PAREN, RIGHT_PAREN, END };

// Define parser states
enum class State { S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, ACCEPT, ERROR };

// Function to map states to production rules
string getProductionRule(State state) {
    switch (state) {
        case State::S1: return "E → E + T";
        case State::S2: return "E → T";
        case State::S3: return "T → T * F";
        case State::S4: return "T → F";
        case State::S5: return "F → (E)";
        case State::S6: return "F → id";
        default: return "";
    }
}

// Function to get token from input character
Token getToken(char c) {
    switch (c) {
        case '+':
            return Token::PLUS;
        case '*':
            return Token::MULTIPLY;
        case '(':
            return Token::LEFT_PAREN;
        case ')':
            return Token::RIGHT_PAREN;
        case '$':
            return Token::END;
        default:
            return Token::ID; // Assume any other character is an identifier
    }
}
// Parsing table
unordered_map<State, unordered_map<Token, pair<State, int>>> parsingTable = {
    {State::S0, {{Token::ID, {State::S5, -1}}, {Token::PLUS, {State::S4, -1}}, {Token::MULTIPLY, {State::ERROR, 1}}, {Token::LEFT_PAREN, {State::S1, -1}}, {Token::RIGHT_PAREN, {State::ERROR, 3}}, {Token::END, {State::ERROR, 3}}}},
    {State::S1, {{Token::ID, {State::S5, -1}}, {Token::PLUS, {State::S4, -1}}, {Token::MULTIPLY, {State::ERROR, 1}}, {Token::LEFT_PAREN, {State::S1, -1}}, {Token::RIGHT_PAREN, {State::ERROR, 3}}, {Token::END, {State::ERROR, 3}}}},
    {State::S2, {{Token::ID, {State::ERROR, 2}}, {Token::PLUS, {State::ERROR, 2}}, {Token::MULTIPLY, {State::S7, 1}}, {Token::LEFT_PAREN, {State::ERROR, 2}}, {Token::RIGHT_PAREN, {State::ERROR, 2}}, {Token::END, {State::ERROR, 2}}}},
    {State::S3, {{Token::ID, {State::ERROR, 4}}, {Token::PLUS, {State::ERROR, 4}}, {Token::MULTIPLY, {State::S8, 1}}, {Token::LEFT_PAREN, {State::ERROR, 4}}, {Token::RIGHT_PAREN, {State::ERROR, 4}}, {Token::END, {State::ERROR, 4}}}},
    {State::S4, {{Token::ID, {State::S5, -1}}, {Token::PLUS, {State::S4, -1}}, {Token::MULTIPLY, {State::S8, -2}}, {Token::LEFT_PAREN, {State::S1, -1}}, {Token::RIGHT_PAREN, {State::ERROR, 3}}, {Token::END, {State::ERROR, 3}}}},
    {State::S5, {{Token::ID, {State::S6, -1}}, {Token::PLUS, {State::ERROR, 5}}, {Token::MULTIPLY, {State::ERROR, 5}}, {Token::LEFT_PAREN, {State::S1, -1}}, {Token::RIGHT_PAREN, {State::ERROR, 5}}, {Token::END, {State::ERROR, 5}}}},
    {State::S6, {{Token::ID, {State::ERROR, 9}}, {Token::PLUS, {State::ERROR, 9}}, {Token::MULTIPLY, {State::ERROR, 9}}, {Token::LEFT_PAREN, {State::ERROR, 9}}, {Token::RIGHT_PAREN, {State::ERROR, 9}}, {Token::END, {State::ERROR, 9}}}},
    {State::S7, {{Token::ID, {State::S5, -1}}, {Token::PLUS, {State::ERROR, 6}}, {Token::MULTIPLY, {State::ERROR, 6}}, {Token::LEFT_PAREN, {State::S1, -1}}, {Token::RIGHT_PAREN, {State::ERROR, 6}}, {Token::END, {State::ERROR, 6}}}},
    {State::S8, {{Token::ID, {State::S5, -1}}, {Token::PLUS, {State::ERROR, 7}}, {Token::MULTIPLY, {State::ERROR, 7}}, {Token::LEFT_PAREN, {State::S1, -1}}, {Token::RIGHT_PAREN, {State::ERROR, 7}}, {Token::END, {State::ERROR, 7}}}},
    {State::S9, {{Token::ID, {State::ERROR, 10}}, {Token::PLUS, {State::ERROR, 10}}, {Token::MULTIPLY, {State::ERROR, 10}}, {Token::LEFT_PAREN, {State::ERROR, 10}}, {Token::RIGHT_PAREN, {State::ERROR, 10}}, {Token::END, {State::ERROR, 10}}}},
    {State::S10, {{Token::ID, {State::S5, -1}}, {Token::PLUS, {State::ERROR, 8}}, {Token::MULTIPLY, {State::ERROR, 8}}, {Token::LEFT_PAREN, {State::S1, -1}}, {Token::RIGHT_PAREN, {State::ERROR, 8}}, {Token::END, {State::ERROR, 8}}}},
    {State::S11, {{Token::ID, {State::ERROR, 11}}, {Token::PLUS, {State::ERROR, 11}}, {Token::MULTIPLY, {State::ERROR, 11}}, {Token::LEFT_PAREN, {State::ERROR, 11}}, {Token::RIGHT_PAREN, {State::ERROR, 11}}, {Token::END, {State::ERROR, 11}}}}
};



// Function to parse input string
bool parseInput(const string& input) {
    stack<State> stateStack;
    stateStack.push(State::S0); // Initial state
    string remainingInput = input + "$";
    size_t inputIndex = 0;

    cout << "Input: " << input << endl;
    cout << "Stack:" << endl;
    cout << "Step\tStack\t\t\tInput\tAction" << endl;

    while (!stateStack.empty()) {
        State currentState = stateStack.top();
        char nextInput = remainingInput[inputIndex];
        Token nextToken = getToken(nextInput);

        if (parsingTable[currentState].find(nextToken) != parsingTable[currentState].end()) {
            pair<State, int> nextState = parsingTable[currentState][nextToken];

            // Display parsing step along with the stack content
            cout << inputIndex << "\t";
            stack<State> tempStack = stateStack;
            while (!tempStack.empty()) {
                cout << static_cast<int>(tempStack.top()) << " ";
                tempStack.pop();
            }
            cout << "\t\t" << remainingInput.substr(inputIndex) << "\t";

            // Apply action
            switch (nextState.second) {
                case -1:
                    stateStack.push(nextState.first);
                    inputIndex++;
                    cout << "Shift " << static_cast<int>(nextState.first) << endl;
                    break;
                case 1:
                    stateStack.push(nextState.first);
                    cout << "Reduce " << getProductionRule(nextState.first) << endl;
                    break;
                case 0:
                    cout << "Accept" << endl;
                    return true;
                default:
                    cout << "Error" << endl;
                    return false;
            }
        } else {
            cout << inputIndex << "\t";
            stack<State> tempStack = stateStack;
            while (!tempStack.empty()) {
                cout << static_cast<int>(tempStack.top()) << " ";
                tempStack.pop();
            }
            cout << "\t\t" << remainingInput.substr(inputIndex) << "\t";
            cout << "Error: No transition for state " << static_cast<int>(currentState) << " and token " << static_cast<int>(nextToken) << endl;
            return false;
        }
    }

    return false;
}

int main() {
    // Test cases
    string inputs[] = {"(id+id)*id$", "id*id", "(id*)$"};
    for (const string& input : inputs) {
        if (parseInput(input)) {
            cout << "Output: String is accepted." << endl;
        } else {
            cout << "Output: String is not accepted." << endl;
        }
        cout << endl;
    }

    return 0;
}