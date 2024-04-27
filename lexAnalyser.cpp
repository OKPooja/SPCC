//Lex Analyser

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, n) for (int i = 0; i < n; i++)

void print(set<string> a){
    for(auto it: a)
        cout << it << " ";
    cout << endl;
}
void splitString(string s, vector<string> &split){
    For(i, s.size()){
        string temp;
        while((i < s.size() && s[i] != 32)){
            if(s[i]== ';'){
                split.pb(";");
                break;
            }
            temp.pb(s[i]);
            i++;
        }
        split.pb(temp);   
    }
}
int main() {
    
    set<string> keywords({"int", "float", "char", "continue","for", "if", "break", "while", "string", "double"});  
    set<string> operators({"+", "-", "*", "%", "/", "<", ">", "="});
    set<string> separators({";", ",", ":", "(", ")", "[", "]", "{", "}"});

    map<string, set<string>> ans;

    int n;
    //cout << "Enter no. of lines of code you want to enter: ";
    cin >> n;
    //cout << "Enter code: ";
    string buffer;
    getline(cin, buffer);

    while(n--){

        string s;
        getline(cin, s);
        vector<string> split;
        splitString(s, split);

        For(i, split.size()){
            if(isdigit(split[i][0])){
                ans["constants"].insert(split[i]);
            } else if(keywords.find(split[i]) != keywords.end()){
                ans["keywords"].insert(split[i]);
            } else if(operators.find(split[i]) != operators.end()){
                ans["operators"].insert(split[i]);
            } else if(separators.find(split[i]) != separators.end()){
                ans["separators"].insert(split[i]);
            } else if(split[i][0] == '"'){
                //strings like "Hello how are you?"
            	ans["constants"].insert(split[i].substr(1, split[i].size() - 2));
            } else{
                //to handle the case of i++ or i--;
            	if(operators.find(string(1,split[i][1])) != operators.end()){
            		ans["operators"].insert(string(1,split[i][1]));
            		ans["identifier"].insert(string(1,split[i][0]));
            	} else{
            		ans["identifier"].insert(split[i]);
            	}
                
            }
        }
    }
    for(auto it: ans){
        cout << it.first << ": ";
        print(it.second);
    }

    return 0;
}
// 2
// string a = "Hello";
// for ( int i = 0; i < n; i++ );

// constants: 0 Hello 
// identifier:  a i n 
// keywords: for int string 
// operators: + < = 
// separators: ( ) ; 
