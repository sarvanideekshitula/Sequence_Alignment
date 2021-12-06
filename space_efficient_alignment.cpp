#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "./stdc++.h"
using namespace std;

int alpha[4][4] = { {0, 2, 2, 2}, 
                    {2, 0, 2, 2}, 
                    {2, 2, 0, 2}, 
                    {2, 2, 2, 0} };

int misMatchPenalty = 3;
int gapPenalty = 2;

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

vector<string> getMinimumPenalty(string X, string Y, int pxy, int pgap) {
    int i, j; 

    int m = X.length(); 
    int n = Y.length(); 
   
    // Creating 2D vector for storing the optimal substructure answers
    vector<vector<int> > dp(m+1,vector<int>(n+1,0));

    // Base cases
    for (i = 0; i <=m; i++) {
        dp[i][0] = i * pgap;
    } 

    for (j= 0; j <=n; j++) {
        dp[0][j] = j * pgap;
    } 
    
    // calculating the minimum penalty
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
              // alpha[getNumber(X[i-1])][getNumber(Y[j-1])]
                dp[i][j] = min(dp[i - 1][j - 1] + pxy , min(dp[i - 1][j] + pgap, dp[i][j - 1] + pgap));
            }
        }
    }
 
    // Reconstructing the solution
    int l = n + m; // maximum possible length
     
    i = m; j = n;
     
    int xpos = l;
    int ypos = l;
 
    // Final answers for the respective strings
    int xans[l+1], yans[l+1];
     
    while ( !(i == 0 || j == 0)) {
        if (X[i - 1] == Y[j - 1]) {
            xans[xpos--] = (int)X[i - 1];
            yans[ypos--] = (int)Y[j - 1];
            i--; j--;
        }
        else if (dp[i - 1][j - 1] + pxy == dp[i][j]) {
            xans[xpos--] = (int)X[i - 1];
            yans[ypos--] = (int)Y[j - 1];
            i--; j--;
        }
        else if (dp[i - 1][j] + pgap == dp[i][j]) {
            xans[xpos--] = (int)X[i - 1];
            yans[ypos--] = (int)'_';
            i--;
        }
        else if (dp[i][j - 1] + pgap == dp[i][j]) {
            xans[xpos--] = (int)'_';
            yans[ypos--] = (int)Y[j - 1];
            j--;
        }
    }
    while (xpos > 0) {
        if (i > 0) xans[xpos--] = (int)X[--i];
        else xans[xpos--] = (int)'_';
    }
    while (ypos > 0) {
        if (j > 0) yans[ypos--] = (int)Y[--j];
        else yans[ypos--] = (int)'_';
    }
 
    int id = 1;
    for (i = l; i >= 1; i--) {
        if ((char)yans[i] == '_' && (char)xans[i] == '_') {
            id = i + 1;
            break;
        }
    }

    vector<string> res;
    string s1="", s2="";
    for (i = id; i <= l; i++) {
        s1 = s1 = (char)xans[i];
    }
    for (i = id; i <= l; i++) {
        s2 = s2 + (char)yans[i];
    }
    res.push_back(s1);
    res.push_back(s2);
    res.push_back(to_string(dp[m][n]));
    return res;
}

vector<int> Space_Efficient_Alignment(string x,string y, string alignment) {
  int m = x.length();
  int n = y.length();
  
  vector<vector<int> > B(m+1, vector<int>(2));

  vector<int> res;
  int mismatchCost=0;

  for (int i=0;i<=m;i++) {
    B[i][0] = i * gapPenalty;
  }
  for (int j=0;j<n;j++) {
    B[0][1] = j * gapPenalty;
    for (int i=1;i<=m;i++) {
      int p, q, r;
      if(alignment == "forward"){
        p =  alpha[getNumber(x[i-1])][getNumber(y[j])] + B[i-1][0];
      } else {
        p = alpha[getNumber(x[m-i])][getNumber(y[n-j])] + B[i-1][0];
      }
      q = gapPenalty + B[i-1][1];
      r = gapPenalty + B[i][0];
      B[i][1] = min(min(p,q), r);
    }

    for (int i=0;i<=m;i++) {
      B[i][0] = B[i][1];
    }
  }

  for(int i=0;i<=m;i++){
    res.push_back(B[i][1]);
  }

  return res;
}

vector<string> Divide_and_Conquer_Alignment(string X, string Y) {
  // cout << X << endl;
  int m = X.length(), n = Y.length();

  if(m <= 2 or n <= 2){
    return getMinimumPenalty(X, Y, misMatchPenalty, gapPenalty);
  }
  int midY = n/2;

  vector<int> forwardAlignment = Space_Efficient_Alignment(X, Y.substr(0,midY), "forward");

  vector<int> backwardAlignment = Space_Efficient_Alignment(X, Y.substr(midY+1,n), "backward");

  vector<int> sum;
  int q = 0, min = INT_MAX;
  for(int j=0;j<=m;j++) {
    int val = forwardAlignment[j] + backwardAlignment[m-j];
    sum.push_back(val);
  }
  for(int j=0;j<sum.size();j++) {
    if(sum[j] < min){
      min = sum[j];
      q = j;
    }
  }
  forwardAlignment.clear();
  backwardAlignment.clear();
  sum.clear();

  vector<string> forward = Divide_and_Conquer_Alignment(X.substr(0, q), Y.substr(0, midY));

  vector<string> backward = Divide_and_Conquer_Alignment(X.substr(q+1, n), Y.substr(midY+1, n));

  vector<string> res;
  for(int k=0;k<3;k++){
    if(k == 2){
      stringstream convert(forward[k]);
      int x = 0;
      convert >> x;

      stringstream convert2(backward[k]);
      int y = 0;
      convert2 >> y;

      string s = to_string(x + y);
      res.push_back(s);
    } else {
      res.push_back(forward[k] + backward[k]);
    }
  }
  return res;
}

int main() { 
  string X = "AGGGCT";
  string Y = "AGGCA";
  vector<string> result = Divide_and_Conquer_Alignment(X, Y);
  cout << result[0] << endl;
  cout << result[1] << endl;
  cout << result[2] << endl;
  return 0;
} 
