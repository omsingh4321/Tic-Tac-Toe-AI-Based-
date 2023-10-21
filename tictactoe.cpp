#include <bits/stdc++.h>
using namespace std;
bool flag=true;
int winner=-1;
bool check(vector<vector<char>>board)
{
  int count=0;
  for(auto p:board)
  {
    for(auto k:p){
        if(k!='#') count++;
    }
  }
  if(count==board.size()*board.size()){
    
    return true;
  }
  //for row
  for(auto row:board)
  {
    int cnt=0;
    for(int col:row) if(col=='X') cnt++;
    if(cnt==board[0].size()) return true;
    cnt=0;
    for(int col:row) if(col=='O') cnt++;
    if(cnt==board[0].size()) return true;
  }
  int row=0;
  int col=0;
  int cntx=0;
  int cnto=0;
  while(row<board.size() && col<board[0].size())
  {
   if(board[row][col]=='X') cntx++;
   if(board[row][col]=='O') cnto++;
   row++;
   col++;
  }
  if(cntx==board.size()) return true;
  if(cnto==board[0].size()) return true;
  row=0;
  col=board[0].size()-1;
  cntx=0;
  cnto=0;
  while(row<board.size())
  {
   if(board[row][col]=='X') cntx++;
   if(board[row][col]=='O') cnto++;
     row++;
     col--;
  }
   if(cntx==board.size()) return true;
  if(cnto==board[0].size()) return true;
row=0;
col=0;
while(col<board.size())
{
   cntx=0;
  cnto=0;
  row=0;
   while(row<board.size())
    {
     if(board[row][col]=='X') cntx++;
     if(board[row][col]=='O') cnto++;
     row++;
    }
    if(cntx==board.size()) return true;
  if(cnto==board[0].size()) return true;
col++;
}

return false;

  
}

pair<int,pair<int,int>> Solve(int i,int j,vector<vector<char>>board,map<pair<int,int>,int>M)
{
    
if(i<0 || j<0 || i==board.size() || j==board.size()) return {INT_MAX,{-1,-1}};

if(board[i][j]!='#' || M[{i,j}]==1) return {INT_MAX,{-1,-1}};
M[{i,j}]=1;
board[i][j]='X';

if(check(board)){ 

    return {0,{i,j}};
}
pair<int,pair<int,int>>Index={INT_MAX,{-1,-1}};
for(int p=-1;p<=1;p++)
{
    for(int r=-1;r<=1;r++)
    {
     if(p==0 && r==0) continue;
      pair<int,pair<int,int>>temp=Solve(i+p,j+r,board,M);
     
      if(temp.first<Index.first) Index=temp;
    }
}
if(Index.first!=INT_MAX) Index.first=Index.first+1;
return Index;
}


void Select (vector<vector<char>>&board)
{
if(check(board)) {
   if(winner==-1) winner=0;
    flag=false;
    return;
}
pair<int,pair<int,int>>Index={INT_MAX,{-1,-1}};
 for(int i=0;i<board.size();i++)
 {
    for(int j=0;j<board[i].size();j++)
    {
        if(board[i][j]=='#')
        {
          map<pair<int,int>,int>M;
          pair<int,pair<int,int>>temp= Solve(i,j,board,M);
          if(Index.first>temp.first) Index=temp;

        }
    }
 }
board[Index.second.first][Index.second.second]='O';
if(check(board)) {
   if(winner==-1) winner=0;
    flag=false;
    return;
}
}

int main()
{
vector<vector<char>>board(3,vector<char>(3,'#'));
    for(auto p:board){
        for(auto t:p) {
            cout<<t<<" ";
        }
       cout<<endl;
     }
     cout<<endl;
    while(flag)
    {
     cout<<"Enter the position of indexes to place"<<endl;
     int i,j;
     cin>>i>>j;
     if(i>2 || j>2 || i<0 || j<0) cout<<"Program terminated"<<endl;
     if(board[i][j]!='#') cout<<"Program terminated"<<endl;
     board[i][j]='X';
     Select(board);
     if(!flag) break;
     for(auto p:board){
        for(auto t:p) {
            cout<<t<<" ";
        }
       cout<<endl;
     }
    }
 for(auto p:board){
        for(auto t:p) {
            cout<<t<<" ";
        }
       cout<<endl;
     }
if(winner==0) cout<<"Machine won"<<endl;
else if(winner==1) cout<<"You won"<<endl;
else cout<<"Nobody Wins"<<endl;

}