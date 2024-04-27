//Follow

#include <bits/stdc++.h>    
using namespace std;
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
int main(){

    int n;
    //cout << "Enter no. of productions: ";
    cin >> n;
    vector<pair<char, vector<string>>> productions;
    vector<string> init(n);
    //cout << "Enter productions (Use $ for epsilon): \n";
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

    map<char, set<string>> firsttt;
    //cout << "Enter first for each production: \n";

    for(auto it: productions){
        char current = it.first;
        //cout << it.first << " ";
        string f;   cin >> f;
        for(int j = 0; j < f.size(); j++){
            string temp;
            while(j < f.size() && f[j] != ','){
                temp.pb(f[j]);
                j++;
            }
            firsttt[current].insert(temp);
        }
    }
    //since we took the input in reverse order
    //and follow should always start from the starting letter, hence we reverse it
    reverse(productions.begin(), productions.end());
    map<char, set<string>> follow;  
    int k = 0;
    for(auto it: productions){
        //starting symbol should have $ in its follow
    	if(k == 0){
    		follow[it.first].insert("$");
    		k++;
    	}
    	set<string> fp;
    	for(auto it1: productions){
    		vector<string> current = it1.second;
    		//cout << it1.first << " ";
    		for(int i = 0; i < current.size(); i++){
    			string temp = current[i];
                //storing the value whose follow is to be found in check variable
    			char check = it.first;
    			for(int j = 0; j < temp.size(); j++){
                    //case where we are checking if the last character of string is same as check, then we will add follow of source
    				if(j == temp.size() - 1 && temp[j] == check){
    					for(auto it3: follow[it1.first])
    						fp.insert(it3);
    				} else if(temp[j] == check){
                        //case where there is a non-terminal present after check, add first of that non-terminal
    					if(temp[j + 1] >= 'A' && temp[j + 1] <= 'Z'){
    						for(auto it3: firsttt[temp[j + 1]]){
    							fp.insert(it3);
    						}
    					} else{
                            //where you encountered a terminal, just add that terminal in follow set and break
    						string t;
    						t.pb(temp[j + 1]);
    						fp.insert(t);
    						break;
    					}
                        //if we have epsilon in our fp set then we have to check further, hence update check with the next character
    					if(fp.find("@") != fp.end()){
    						fp.erase("@");
    						check = temp[j + 1];
    					} else{
    						break;
    					}
    				}
    			}
    		}
    		for(auto it5: fp){
    			follow[it.first].insert(it5);
    		}
    	}
    }  
    for(auto it: follow){
		cout << it.first << " ";
		for(auto it1: it.second)
			cout << it1 << " ";
		cout << endl;
	}
	cout << endl;
  	return 0;   
}

// 4
// C->h|@
// B->g|@
// A->da|BC
// S->ABC|CbB|Ba
// h,@
// g,@
// d,h,g,@
// d,g,h,b,a,@

//Output:
// A $ g h 
// B $ a g h 
// C $ b g h 
// S $ 
