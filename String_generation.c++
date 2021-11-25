#include <iostream>
#include <sstream>
using namespace std;

int main() {
	freopen("BaseTestcases_CS570FinalProject/input1.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    string res1, res2;
	string s1;
	cin >> s1;
	string p;
	while(true){
	    cin >> p;
	    if(int(p[0]) >= 48 && int(p[0]) <= 57){
	        stringstream convert(p);
	        int x = 0;
	        convert >> x;
	        if(x < s1.length()){
	            res1 = s1;
	            s1.insert(x+1, res1);
	        }
	    } else{
	        break;
	    }
	}
	string s2 = p;
	int j;
	while(cin >> j){
        if(j < s2.length()){
            res2 = s2;
            s2.insert(j+1, res2);
        }
	}
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl; 
	return 0;
}
