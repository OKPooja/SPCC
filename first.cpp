//First

#include <bits/stdc++.h>    
using namespace std;
#define endl "\n";
#define ll long long int
#define pb push_back
#define For(i,n) for(int i=0; i<n; i++)

void split(vector<string> init, vector<pair<char, vector<string>>> &productions, int n){
    int index = -1;
    For(i, n){
        string curr = init[i];
        For(j, curr.size()){
            if(curr[j] == '-'){
                //left character that is the source
                productions.pb({curr[j - 1], {}});
                index = j + 1;
                continue;
            }
            if(j > index && curr[j] == '|'){
                string a;
                for(int k = index + 1; k < j; k++){
                    a.pb(curr[k]);
                }
                index = j;
                productions[i].second.pb(a);
                continue;
            }
            //mostly to handle last character if there is no | symbol
            if(j > index && j == curr.size() - 1){
                string a;
                for(int k = index + 1; k <= j; k++){
                    a.pb(curr[k]);
                }
                index = j;
                productions[i].second.pb(a);
            }
        }
    }
}
int main (){

    int n;
    //cout << "Enter no. of productions: ";
    cin >> n;
    vector<pair<char, vector<string>>> productions;
    vector<string> init(n);
    //cout << "Enter productions (Use $ for epsilon): ";
    For(i, n)   cin >> init[i];
    split(init, productions, n);
    // for(auto it: productions){
    //     cout << it.first << " ";
    //     vector<string> curr = it.second;
    //     For(i, curr.size()){
    //         cout << curr[i] << " ";
    //     }
    //     cout << endl;
    // }
    map<char, set<char>> first;
    for(auto it: productions){
        vector<string> s = it.second;
        first[it.first] = {};
        For(i, s.size()){
            string curr = s[i];
            bool continueOrNot = true;
            For(k, curr.size()){
                //cout << curr << "\n";
                if(continueOrNot){
                    if(curr[k] >= 'a' && curr[k] <= 'z'){
                        first[it.first].insert(curr[k]);
                        break;
                    }
                    if(curr[k] == '@'){
                        first[it.first].insert('@');
                        continue;
                    }
                    continueOrNot = false;
                    //if encountered a capital letter add that letter ka first in the current letter's first
                    if(curr[k] >= 'A' && curr[k] <= 'Z'){
                        set<char> cont = first[curr[k]];
                        for(char elem: cont){
                            first[it.first].insert(elem);
                            //if there is an epsilon present in the first then we can check further hence continueOrNot is set to true
                            if(elem == '@'){
                                continueOrNot = true;
                            }
                        }
                    }
                } else{
                    break;
                }
            }
        }
    }
    for (auto it : first) {
        cout << it.first << " ";
        set<char> temp = it.second;
        if(temp.size()){
            for(auto i: temp)
                cout << i << " ";
            cout << endl;
        }
    }
}


// 4
// C->h|@
// B->g|@
// A->da|BC
// S->ABC|CbB|Ba

//Output:
// A @ d g h 
// B @ g 
// C @ h 
// S @ a b d g h 

