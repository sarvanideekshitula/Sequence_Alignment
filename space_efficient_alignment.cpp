#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// int alpha[4][4] = { {0, 110, 48, 94}, 
//                     {110, 0, 118, 48}, 
//                     {48, 118, 0, 110}, 
//                     {94, 48, 110, 0} };

int alpha[4][4] = { {0, 2, 2, 2}, 
                    {2, 0, 2, 2}, 
                    {2, 2, 0, 2}, 
                    {2, 2, 2, 0} };

int delta = 3;

int getNumber(char ch){
  if(ch == 'A'){
    return 0;
  } else if(ch == 'C'){
    return 1;
  } else if(ch == 'G'){
    return 2;
  } else{
    return 3;
  }
}

 vector<int> Space_Efficient_Alignment(string x,string y) {
   cout << x << " " << y << endl;
  int m = x.length();
  int n = y.length();
  vector<vector<int> > B(m+1, vector<int>(2));
  vector<int> res;
  for (int i=0;i<=m;i++) {
    B[i][0] = i*delta;
  }
  for (int j=1;j<=n;j++) {
    B[0][1] = j*delta;
    for (int i=1;i<=m;i++) {
      B[i][1] = min(min(alpha[getNumber(x[i])][getNumber(y[j])] + B[i-1][0], delta + B[i-1][1]), delta + B[i][0]);
    }
    for (int i=0;i<=m;i++) {
      B[i][0] = B[i][1];
    }
  }
  for(int i=0;i<m;i++){
    res.push_back(B[i][1]);
  }
  return res;
}

void Divide_and_Conquer_Alignment(string X, string Y){
  int m = X.length(), n = Y.length(); 
  // if m<=2 and n<=2 use naive approach
  vector<int> res1 = Space_Efficient_Alignment(X.substr(0, n/2+1), Y);
  for(int j=0;j<res1.size();j++) {
      cout << res1[j] << endl;
  }

  reverse(Y.begin(), Y.end());
  string temp = X.substr(n/2+1, n);
  reverse(temp.begin(), temp.end());

  cout << endl;
  vector<int> res2 = Space_Efficient_Alignment(temp, Y);
  for(int j=0;j<res2.size();j++) {
      cout << res2[j] << endl;
  }
}

int main() {
  string s1="AGGGCT", s2="AGGCA";
  Divide_and_Conquer_Alignment(s1, s2);
  return 0;
} 