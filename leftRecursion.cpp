//Left Recursion

#include <bits/stdc++.h>    
using namespace std;
#define pb push_back
#define For(i,n) for(int i=0; i<n; i++)

void splitString(string s, map<char, vector<string>> &mp){
    int index = -1;
    mp[s[0]] = {};
    for(int i = 3; i < s.size(); i++){
        string temp;
        while(i < s.size() && s[i] != '|'){
            temp.pb(s[i]);
            i++;
        }
        mp[s[0]].pb(temp);
    }
}
void leftRec(map<char, vector<string>> mp, map<string, vector<string>> &modifications){
    map<string, vector<string>> copy;
    for(auto it: mp){
        vector<string> current = it.second;
        for(int i = 0; i < current.size(); i++) {
            for(int j=0; j < current[i].size();j++) {
                string to_check = string(1, current[i][j]);
                if(copy.count(to_check) && ((j + 1 < current[i].size() && string(1, current[i][j+1]) != "'") || j == current[i].size()-1)) {
                    string back = current[i].substr(0, j);
                    string front = current[i].substr(j+1, current[i].size());
                    vector<string> to_replace = copy[to_check];
                    current[i] = back + to_replace[0] + front;
                    for(int k=1;k<to_replace.size();k++) 
                        current.push_back(back + to_replace[k] + front);
                }
            }
        }
        char left = it.first;
        vector<string> alpha, beta;
        for(int i = 0; i < current.size(); i++){
            string currentString = current[i];
            string append = "";
            bool flag = false;
            for(int j = 0; j < currentString.size(); j++){
                if(currentString[j] != left) append += currentString[j];
                if(currentString[j] == left) flag = true;
            }
            if(flag) alpha.push_back(append);
            else beta.push_back(append);
        }
        string newNonTerminal = string(1, left) + "'";
        for(auto it1: beta){
            it1 += newNonTerminal;
            modifications[string(1, left)].pb(it1);
        }
        for(auto it1: alpha){
            it1 += newNonTerminal;
            modifications[newNonTerminal].pb(it1);
        }
        modifications[newNonTerminal].pb("@");
        copy[string(1, left)] = modifications[string(1, left)];
    }

    for(auto it: modifications){
        cout << it.first << " -> ";
        for(auto it1: it.second) cout << it1 << " ";
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;
    string buffer;
    getline(cin, buffer);
    map<char, vector<string>> mp;
    while(n--){
        string s;
        getline(cin, s);
        splitString(s, mp);
    }
    map<string, vector<string>> modifications;
    leftRec(mp, modifications);
    return 0;   
}
// 2
// X->X1|Y1|0
// Y->Y0|X1|1

//Output:
// X -> Y1X' 0X' 
// X' -> 1X' @ 
// Y -> 1Y' 0X'1Y' 
// Y' -> 0Y' 1X'1Y' @ 
