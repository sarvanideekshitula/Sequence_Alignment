#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

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
  int m = x.length();
  int n = y.length();
  
  vector<vector<int> > B(m+1, vector<int>(2));

  vector<int> res;
  
  for (int i=0;i<=m;i++) 
  {
    B[i][0] = i*delta;
  }
  
  for (int j=1;j<=n;j++) 
  {

    B[0][1] = j*delta;
    for (int i=1;i<=m;i++) 
    {
      int mismatch_penalty = alpha[getNumber(x[i-1])][getNumber(y[j-1])];

      B[i][1] = min( mismatch_penalty+B[i-1][0], delta + min( B[i-1][1], B[i][0] ) );
    }

    for (int i=0;i<=m;i++) 
    {
      B[i][0] = B[i][1];
    }
  }

  for(int i=0;i<=m;i++){
    res.push_back(B[i][1]);
  }

  return res;
}

string Divide_and_Conquer_Alignment(string X, string Y)
{
  int m = X.length(), n = Y.length();

  // if m<=2 and n<=2 use naive approach

  vector<int> forward_B = Space_Efficient_Alignment(Y, X.substr(0, n/2+1));

  int min_index_forward = min_element(forward_B.begin(), forward_B.end()) - forward_B.begin() - 1;
  int min_val_forward = forward_B[min_index_forward + 1];
  

  reverse(Y.begin(), Y.end());
  string temp = X.substr(n/2+1, n);
  reverse(temp.begin(), temp.end());

  vector<int> backward_B = Space_Efficient_Alignment(Y, temp);
  int min_index_backward = n - (min_element(backward_B.begin(), backward_B.end()) -backward_B.begin()) ;
  int min_val_backward = backward_B[n - min_index_backward];

  for (int i=0;i<backward_B.size();i++)
  {
    cout<<backward_B[i]<<endl;
  }
  cout<<"--------------"<<endl;

  int min_index = -1;
  reverse(Y.begin(), Y.end());
  if (min_val_backward<min_val_forward)
  {
    min_index = min_index_backward;
  }
  else
  {
    min_index = min_index_forward;
  }

  cout<<"Y = "<< Y.substr(0, min_index+1) <<" and " << Y.substr(min_index+1, n);

  string X_l = X.substr(0, n/2+1);
  string X_r = X.substr(n/2+1, n);

  string Y_l = Y.substr(0, min_index+1);
  string Y_r = Y.substr(min_index+1, n);

  string a = Divide_and_Conquer_Alignment(X_l, Y_l);
  string b = Divide_and_Conquer_Alignment(X_r, Y_r);

  return a+b;
}

int main() 
{
  string X="AGGCTTT", Y="ATTGA";
  
  string alignment = Divide_and_Conquer_Alignment(X, Y);

  return 0;
} 
