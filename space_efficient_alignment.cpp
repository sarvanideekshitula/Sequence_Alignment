#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "./stdc++.h"
using namespace std;

int alpha[4][4] = { {0, 110, 48, 94}, 
                    {110, 0, 118, 48}, 
                    {48, 118, 0, 110}, 
                    {94, 48, 110, 0} };

int gapPenalty = 30;

int getNumber(char ch) {
  if(ch == 'A'){
    return 0;
  } else if(ch == 'C') {
    return 1;
  } else if(ch == 'G') {
    return 2;
  } else{
    return 3;
  }
}

vector<string> SequenceAlignmentDP(string X, string Y) {
    int m = X.length(); 
    int n = Y.length(); 
   
    // Creating 2D vector for storing the optimal substructure answers
    vector<vector<int> > dp(m+1,vector<int>(n+1,0));

    // Base cases
    for (int i = 0; i <=m; i++) {
        dp[i][0] = i * gapPenalty;
    } 

    for (int j= 0; j <=n; j++) {
        dp[0][j] = j * gapPenalty;
    } 

    // calculating the minimum penalty
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j - 1] + alpha[getNumber(X[i-1])][getNumber(Y[j-1])], min(dp[i - 1][j] + gapPenalty, dp[i][j - 1] + gapPenalty));
            }
        }
    }

    int i = m, j = n;
    string align1 = "", align2 = "";

    while (i > 0 && j > 0) {
      if(dp[i][j] == dp[i-1][j] + gapPenalty) {
        align1 = X[i-1] + align1;
        align2 = "_" + align2;
        i = i-1;
      } else if(dp[i][j] == dp[i][j-1] + gapPenalty) {
        align1 = "_" + align1;
        align2 = Y[j-1] + align2;
        j = j-1;
      } else if(dp[i][j] == dp[i-1][j-1] + alpha[getNumber(X[i-1])][getNumber(Y[j-1])]){
        align1 = X[i-1] + align1;
        align2 = Y[j-1] + align2;
        i = i-1;
        j = j-1;
      }
    }

    if(i > 0){
      align1 = X.substr(0, i) + align1;
    }
    if(j > 0){
      align2 = Y.substr(0, j) + align2;
    }
    int diff = align1.length() - align2.length();
    if(diff < 0){
      diff = -diff;
      for(int i=0;i<diff;i++){
        align1 = align1 + "_";
      }
    }
    if(diff > 0){
      for(int i=0;i<diff;i++){
        align2 = align2 + "_";
      }
    }
    vector<string> dpOutput;

    dpOutput.push_back(align1);
    dpOutput.push_back(align2);
    dpOutput.push_back(to_string(dp[m][n]));
    return dpOutput;
}

vector<int> SpaceEfficientAlignment(string x,string y, string alignment) {
  int m = x.length();
  int n = y.length();
  
  vector<vector<int> > B(m+1, vector<int>(2));
  vector<int> res;

  for (int i=0;i<=m;i++) {
    B[i][0] = i * gapPenalty;
  }

  for (int j=1;j<=n;j++) {
    B[0][1] = j * gapPenalty;
    for (int i=1;i<=m;i++) {
      int p, q, r;
      if(alignment == "forward") {
        p =  alpha[getNumber(x[i-1])][getNumber(y[j-1])] + B[i-1][0];
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

  for(int i=0;i<=m;i++) {
    res.push_back(B[i][1]);
  }

  return res;
}

vector<string> Divide_and_Conquer_Alignment(string X, string Y) {
  int m = X.length(), n = Y.length();

  if(m <= 2 || n <= 2){
    return SequenceAlignmentDP(X, Y);
  }

  int midY = n / 2;

  vector<int> forwardAlignment = SpaceEfficientAlignment(X, Y.substr(0, midY), "forward");
  vector<int> backwardAlignment = SpaceEfficientAlignment(X, Y.substr(midY), "backward");

  vector<int> alignmentSum;
  int q = 0, min = INT_MAX;

  for(int j=0;j<=m;j++) {
    int val = forwardAlignment[j] + backwardAlignment[m-j];
    alignmentSum.push_back(val);
  }

  for(int j=0;j<alignmentSum.size();j++) {
    if(alignmentSum[j] < min){
      min = alignmentSum[j];
      q = j;
    }
  }

  forwardAlignment.clear();
  backwardAlignment.clear();
  alignmentSum.clear();

  vector<string> forward = Divide_and_Conquer_Alignment(X.substr(0, q), Y.substr(0, midY));
  vector<string> backward = Divide_and_Conquer_Alignment(X.substr(q), Y.substr(midY));

  vector<string> dcOutput;
  for(int k=0;k<3;k++) {
    if(k == 2) {
      stringstream convert(forward[k]);
      int x = 0;
      convert >> x;

      stringstream convert2(backward[k]);
      int y = 0;
      convert2 >> y;

      string s = to_string(x + y);
      dcOutput.push_back(s);
    } else {
      dcOutput.push_back(forward[k] + backward[k]);
    }
  }

  return dcOutput;
}

vector<string> String_Generation(string filename) {
  string file = "BaseTestcases_CS570FinalProject_Updated/" + filename;
  freopen(file.c_str(), "r", stdin);

  vector<string> result;
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
  result.push_back(s1);
  result.push_back(s2);

  return result;
}

int main(int argc, char** argv) 
{ 
  string X = argv[1];
  string Y = argv[2];

  // string X = "ACACACTGACTACTGACTGGTGACTACTGACTGGACTGACTACTGACTGGTGACTACTGACTGG";
  // string Y = "TTATTATACGCGACGCGATTATACGCGACGCG";
  // vector<string> Strings = String_Generation("input1.txt");
  vector<string> result = Divide_and_Conquer_Alignment(X, Y);
  // cout << result[0].substr(0, 50) << endl;
  // cout << result[1].substr(0, 50) << endl;
  // cout << result[2] << endl;
  return 0;
} 
