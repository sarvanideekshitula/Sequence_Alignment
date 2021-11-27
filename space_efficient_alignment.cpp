#include <iostream>
#include<bits/stdc++.h>

using namespace std;

// Assumptions
// m<=1000

int alpha[4][4] = { {0, 110, 48, 94}, 
                    {110, 0, 118, 48}, 
                    {48, 118, 0, 110}, 
                    {94, 48, 110, 0} } ;

int delta = 30;

void space_efficient_alignment(string x,string y)
{
  int m = x.length();
  int n = y.length();

  int B[1000][2];
  for (int i=0;i<m;i++)
  {
    B[i][0] = i*delta;
  }
  for (int j=0;j<n;j++)
  {
    B[0][1] = j*delta;
    for (int i=0;i<m;i++)
    {
      B[i][1] = min(  alpha[i][j] + B[i-1][0], 
                      delta + B[i-1][1], 
                      delta + B[i][0]);
    }
    for (int i=0;i<m;i++)
    {
      B[i][0] = B[i][1];
    }
  }
}

int main() 
{
} 