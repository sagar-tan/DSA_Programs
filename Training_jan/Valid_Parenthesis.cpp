/*
given a string s containing characters '(','{','[',']','}',')' determine if the input string is valid
Intuition:
- We can use a stack to keep track of the opening brackets
- If we encounter a closing bracket, we check if the stack is empty or the top of the stack is not the corresponding opening bracket
- If the stack is empty or the top of the stack is not the corresponding opening bracket, we return false
- Otherwise, we pop the top of the stack
*/
#include <iostream>
#include <stack>

using namespace std;
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s){//for each character in the string
            if (c == '(' || c == '{' || c == '['){
                st.push(c);
            } else {
                if (st.empty()){
                    return false;
                }
                if (c == ')' && st.top() != '('){
                    return false;
                }
                if (c == '}' && st.top() != '{'){
                    return false;
                }
                if (c == ']' && st.top() != '['){
                    return false;
                }
                st.pop();
            }
        }
        return st.empty();

    }

};

void main(){
    Solution sol;
    string s = "()";
    cout << sol.isValid(s) << endl;
    s = "()[]{}";
    cout << sol.isValid(s) << endl;
    s = "(]";
    cout << sol.isValid(s) << endl;
    s = "([)]";
    cout << sol.isValid(s) << endl;
    s = "{[]}";
    cout << sol.isValid(s) << endl;
}