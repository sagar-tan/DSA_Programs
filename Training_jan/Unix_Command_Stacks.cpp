/*
input path = "/.../a/../b/c/../d/./"
output = "/.../b/d/"
"..." is a valid name for a directory in this problem
".." means previous/parent directory
"." means we will stay in the same directory
"...." any periods sequence other that the above rules is a valid directory name
*/
#include <bits/stdc++.h>
#include <stack>
using namespace std;
class Solution {
    public:
        string simplifyPath(string path){
            stack<string> st;
            string result = "";
            for (int i = 0; i < path.length(); i++){
                if (path[i] == '/'){//if the character is not a '/'
                    continue;
                }
                string current = "";
                while (i < path.length() && path[i] != '/'){
                    current += path[i];
                    i++;
                }
                if (current == ".."){
                    if (!st.empty()){
                        st.pop();
                    }
                } else if (current != "." && current != ""){
                    st.push(current);
                }
            }
            while (!st.empty()){//while the stack is not empty
                result = "/" + st.top() + result;//add the top of the stack to the result
                st.pop();
            }
            return result.empty() ? "/" : result;//if the result is empty return "/" else return result
        }
};
int main(){
    Solution sol;
    string path = "/a/./b/../../c/";
    cout << sol.simplifyPath(path) << endl;
    path = "/home/";
    cout << sol.simplifyPath(path) << endl;
    path = "/../";
    cout << sol.simplifyPath(path) << endl;
    path = "/home//foo/";
    cout << sol.simplifyPath(path) << endl;
    path = "/a/./b/../../c/";
    cout << sol.simplifyPath(path) << endl;
    path = "/a/../../b/../c//.//";
    cout << sol.simplifyPath(path) << endl;
    path = "/a//b////c/d//././/..";
    cout << sol.simplifyPath(path) << endl;
    return 0;
}
