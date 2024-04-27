//TAC

#include<bits/stdc++.h>
using namespace std;
#define pb push_back
map<char, int> op = {
    {'(', 5},
    {'*', 4},
    {'/', 3},
    {'+', 2},
    {'-', 1},
    {'$', 0}
};

bool isVariable(char ch){
    return (ch >= 'a' && ch <= 'z') or (ch >= 'A' && ch <= 'Z');
}
bool isOperator(char ch){
    return op.count(ch);
}
int main(){

    string input;
    cin >> input;

    string newInput = "";
    char counter = 'A';
    int i;
    //unary
    for(i = 0; i < input.size(); i++){
        if(i == 0 and input[i] == '-' && isVariable(input[i + 1])){
            cout << counter << " = " << "-" << input[i + 1] << endl;
            newInput.pb(counter++);
            i++;
        } else if(i + 2 < input.size() && isOperator(input[i]) && input[i + 1] == '-' && isVariable(input[i + 2])){
            cout << counter << " = " << "-" << input[i + 2] << endl;
            newInput.pb(input[i]);
            newInput.pb(counter++);
            i += 2;
        } else{
            newInput.pb(input[i]);
        }
    }
    if(i < input.size())
        newInput.pb(input[i]);
    input = newInput;

    stack<char> st;
    st.push('$');
    string postfix = "";
    //infix to postfix
    for(int i = 0; i < input.size(); i++){
        if(input[i] == '('){
            st.push(input[i]);
            continue;
        }
        if(input[i] == ')'){
            while(st.top() != '('){
                postfix.pb(st.top());
                st.pop();
            }
            st.pop();
            continue;
        }
        if(isVariable(input[i])){
            postfix.pb(input[i]);
            continue;
        }
        while(st.size() > 1 and st.top() != '(' and op[st.top()] >= op[input[i]]){
            postfix.pb(st.top());
            st.pop();
        }
        st.push(input[i]);
    }
    while(st.size() > 1){
        postfix.pb(st.top());
        st.pop();
    }
    for(int i = 0; i < postfix.size(); i++){
        if(isVariable(postfix[i])){
            st.push(postfix[i]);
            continue;
        }
        char ch2 = st.top();
        st.pop();
        char ch1 = st.top();
        st.pop();
        char opt = postfix[i];
        if(opt == '='){
            cout << ch1 << " " << opt << " " << ch2 << endl;
        } else{
            cout << counter << " = " << ch1 << " " << opt << " " << ch2 << endl;
        }
        st.push(counter++);
    }
    return 0;
}
// a=b*-c+d

// A = -c
// B = b * A
// C = B + d
// a = C
