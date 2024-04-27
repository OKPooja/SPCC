//LL1 parser

#include <bits/stdc++.h>    
using namespace std;
#define endl "\n";
#define pb push_back
#define For(i,n) for(int i=0; i<n; i++)

void split(vector<string> init, vector<pair<char, vector<string>>> &productions, int n){
    int index = -1;
    For(i, n){
        string curr = init[i];
        For(j, curr.size()){
            if(curr[j] == '-'){
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
void inputF_F(vector<pair<char, vector<string>>> productions,
    vector<pair<string, set<string>>> &firsttt,
    vector<pair<char, set<string>>> &follow,
    set<string> &terminals){

     //cout << "Enter first for each production: \n";
    for(auto it: productions){
        vector<string> current = it.second;
        for(int i = 0; i < current.size(); i++){
            //cout << current[i] << ": ";
            firsttt.pb({current[i], {}});
            string f;
            cin >> f;
            for(int j = 0; j < f.size(); j++){
                string temp;
                while(j < f.size() && f[j] != ','){
                    temp.pb(f[j]);
                    j++;
                }
                firsttt.back().second.insert(temp);
            }
        }
    }
    //cout << "Enter follow for each production: \n";
    for(auto it: productions){
        char current = it.first;
        //cout << current << ": ";
        follow.pb({current, {}});
        string f;
        cin >> f;
        for(int j = 0; j < f.size(); j++){
            string temp;
            while(j < f.size() && f[j] != ','){
                temp.pb(f[j]);
                j++;
            }
            follow.back().second.insert(temp);
        }
    }
    cout << "\nFirst:\n";
    for(auto it: firsttt){
        cout << it.first << " ";
        set<string> curr = it.second;
        for(auto i: curr){
            cout << i << " ";
            if(i != "@"){
                terminals.insert(i);
            }
        }
        cout << endl;
    }
    cout << "\nFollow:\n";
    for(auto it: follow){
        cout << it.first << " ";
        set<string> curr = it.second;
        for(auto i: curr){
            cout << i << " ";
            terminals.insert(i);
        }
        cout << endl;
    }
}
vector<pair<char, vector<int>>> parseTable(
    vector<pair<char, vector<string>>> productions,
    vector<pair<string, set<string>>> &firsttt,
    vector<pair<char, set<string>>> &follow,
    set<string> terminals){
   
    map<string, int> mapping;
    int m = 0;
    cout << "  ";
    for(auto it: terminals){
        cout << it << " ";
        mapping[it] = m;
        m++;
    }
    cout << endl;
    // for(auto it: mapping)
    //  cout << it.first << " " << it.second << endl;
    vector<pair<char, vector<int>>> table;
    int k = 0, i = 0, prod = 0;
    for(auto it: productions){
        int size = it.second.size();
        vector<int> curr(terminals.size(), 0);
        //size is no.of productions of that particular non-terminal
        while(size--){
            set<string> val = firsttt[k].second;
            for(auto it1: val){
                //cout << it1 << " " << mapping[it1] << endl;
                if(it1 == "@"){
                    //if there is an epsilon in the first, then we take follow of the source 
                    set<string> foll = follow[prod].second;
                    for(auto it3: foll){
                        curr[mapping[it3]] = k + 1;         //adding 1 to k because actual indexing is from 0 but I wanted to display it from 1
                    }
                    continue;
                }
                curr[mapping[it1]] = k + 1;
            }
            k++;
        }
        table.pb({it.first, curr});
        prod++;
    }
   
    for(auto it: table){
        vector<int> curr = it.second;
        cout << it.first << " ";
        for(auto it1: curr){
        	if(it1 == 0){
        		cout << '-' << " ";
        	} else{
        		cout << it1 << " ";
        	}
        }
        cout << endl;
    }
    return table;
}
int main(){
    int n;
    //cout << "Enter no. of productions: ";
    cin >> n;
    vector<pair<char, vector<string>>> productions;
    vector<string> init(n);
    //cout << "Enter productions (Use @ for epsilon): \n";
    for(int i = 0; i < n; i++)   cin >> init[i];
    set<string> terminals;

    split(init, productions, n);
   
    for(auto it: productions){
        cout << it.first << " ";
        vector<string> curr = it.second;
        For(i, curr.size()){
            cout << curr[i] << " ";
        }
        cout << endl;
    }

    vector<pair<string, set<string>>> firsttt;
    vector<pair<char, set<string>>> follow;
    inputF_F(productions, firsttt, follow, terminals);
    vector<pair<char, vector<int>>> table = parseTable(productions, firsttt, follow, terminals);
}

// 5
// E->TA
// A->+TA|@
// T->FB
// B->*FB|@
// F->(E)|id
// (,id
// @
// +
// (,id
// @
// *
// id
// (
// $
// $,)
// +,$,)
// +,$,)
// *,+,$,)