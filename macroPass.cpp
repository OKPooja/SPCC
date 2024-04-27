//Macro Pass

#include <bits/stdc++.h>    
using namespace std;
#define pb push_back
#define For(i,n) for(int i=0; i<n; i++)

void splitString(string s, vector<string> &split){

	For(i, s.size()){
		string temp;
		while(i < s.size() && s[i] != ' '){
			temp.pb(s[i]);
			i++;
		}
		split.pb(temp);
	}
	// for(auto it: split)
	// 	cout << it << " ";    
    // cout << endl;
}
void calcALA(vector<vector<string>> code, map<string, int> &ALA){
	int index = 0;
    for(auto it: code){
    	vector<string> curr = it;
    	for(auto it1: curr){
    		if(it1[0] == '&'){		//anything starting with & is added in ALA
    			if(it1[it1.size() - 1] == ','){
    				string temp = it1.substr(0, it1.size() - 1);
    				if(!ALA.count(temp)){
    					ALA[temp] = index;
    					index++;
    				}
    			} else{
    				if(!ALA.count(it1)){
    					ALA[it1] = index;
    					index++;
    				}
    			}
    		}
    	}
    }
    cout << endl;
    cout << "ALA: \n";
    for(auto it: ALA)
    	cout << it.second << " " << it.first << endl;
}
void calcMDTandMNT(vector<vector<string>> code, map<int, string> &MDT, map<string, int> &ALA, map<int, string> &MNT){

	int k = 1;
	bool flag = true;
	for(int i = 0; i < code.size(); i++){
		if(code[i][0] == "MACRO"){
			flag = true;
			i++;
			string s;
			for(int j = 0; j < code[i].size(); j++){
				//for label 
				if(code[i][j][0] != '&' && flag){
					MNT[k] = code[i][j];
					flag = false;
				} 
				s += code[i][j] + " ";
			}
			MDT[k] = s;
			k++;
			continue;
		}
		vector<string> current = code[i];
		string temp;
		for(int j = 0; j < current.size(); j++){
			string arg;
			if(current[j][current[j].size() - 1] == ','){
				arg = current[j].substr(0, current[j].size() - 1);
			} else{
				arg = current[j];
			}
			if(ALA.count(arg)){
				string s = "#";
				s += ALA[arg] + '0';
				temp += s + " ";
			} else{
				temp += current[j] + " ";
			}
		}
		MDT[k] = temp;
		k++;
	}
	cout << endl;
	cout << "MDT: \n";
	for(auto it: MDT){
		cout << it.first << " " << it.second << endl;
	}
	cout << endl;
	cout << "MNT: \n";
	for(auto it: MNT){
		cout << it.first << " " << it.second << endl;
	}
}

int main(){

    int n;
    cin >> n;
    string t;
    getline(cin, t);
    map<string, int> ALA;
    map<int, string> MDT, MNT;
    vector<vector<string>> code;

    while(n--){
    	string s;
    	getline(cin, s);
    	vector<string> split;
    	splitString(s, split);
    	code.pb(split);
    }

    //ALA
    calcALA(code, ALA);
    //MDT and MNT
    calcMDTandMNT(code, MDT, ALA, MNT);
  	return 0;   
}

//Input:
// 9
// MACRO
// &LAB INCR &ARG1, &ARG2, &ARG3
// &LAB A 1, &ARG1
// A 2, &ARG2
// A 3, &ARG3
// MEND
// MACRO
// N
// MEND

//Output:
// ALA: 
// 1 &ARG1
// 2 &ARG2
// 3 &ARG3
// 0 &LAB

// MDT: 
// 1 &LAB INCR &ARG1, &ARG2, &ARG3 
// 2 #0 A 1, #1 
// 3 A 2, #2 
// 4 A 3, #3 
// 5 MEND 
// 6 N 
// 7 MEND 

// MNT: 
// 1 INCR
// 6 N

