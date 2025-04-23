/*
https://atcoder.jp/contests/abc346/tasks/abc346_d

输入 n(2≤n≤2e5)，长为 n 的 01 字符串 s，长为 n 的数组 a(1≤a[i]≤1e9)。

修改 s，使其中【恰好】包含一对相邻相同字符。
例如 10010 是符合要求的，11001 是不符合要求的（有两对相邻相同字符 11 和 00）。

修改 s[i] 的代价是 a[i]。
输出最小总代价。

进阶：把一对改成两对，K 对，要怎么做？
*/
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
#define ll long long

int n;
string s;
ll a[N];
// 前i个字符以j结尾并且交替的最小代价
ll pre[N][2],suf[N][2];
void init(){
  pre[1][0]=(s[1]=='1')*a[1],pre[1][1]=(s[1]=='0')*a[1];
  suf[n][0]=(s[n]=='1')*a[n],suf[n][1]=(s[n]=='0')*a[n];
  for(int i=2;i<=n;i++){
    int j=s[i]-'0';
    pre[i][j]=pre[i-1][j^1];
    pre[i][j^1]=pre[i-1][j]+a[i];
  }
  for(int i=n-1;i>=1;i--){
    int j=s[i]-'0';
    suf[i][j]=suf[i+1][j^1];
    suf[i][j^1]=suf[i+1][j]+a[i];
  }
}
int main(){
  cin>>n;
  cin>>s;
  s=' '+s;
  // 枚举相邻的数对 然后前后缀分解 更新最小值
  for(int i=1;i<=n;i++) cin>>a[i];
  init();
  ll res=1e18;
  for(int i=2;i<=n;i++){
    for(int j=0;j<2;j++){
        ll t=0;
        t+=((s[i-1]-'0')!=j)*a[i-1];
        t+=((s[i]-'0')!=j)*a[i];
        t+=pre[i-2][j^1];
        t+=suf[i+1][j^1];
      res=min(res,t);
    }
  }
  cout<<res;
  return 0;
}
