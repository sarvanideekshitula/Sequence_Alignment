// CPP program to implement sequence alignment
// problem.
// #include "/Users/yuktigupta/Desktop/97c39f35dab0c45a5d924dd9e50c445f-47ecad34033f986b0972cdbf4636e22f838a1313/stdc++.h"
#include<iostream>
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

// function to find out the minimum penalty
vector<string> getMinimumPenalty(string X, string Y) {
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
 
// Driver code
int main(int argc, char** argv){
    // input strings
    // string X = "AGGGCT";
    // string Y = "AGGCA";

    string X = argv[1];
    string Y = argv[2];    
    // initialising penalties of different types
    int misMatchPenalty = 3;
    int gapPenalty = 2;
 
    // Function to get minimum penalty for strings X & Y
    getMinimumPenalty(X, Y);
    return 0;
}