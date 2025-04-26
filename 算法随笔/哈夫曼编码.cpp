// https://www.nowcoder.com/practice/4c0419eb07c840ca8402e4f2a52cfd49
// 合并最小的两个结点 往左是0往右是1 每一个点都对应一个编码
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;

int n;
ll a[N];
ll res;
int main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    ll deep=n-1;
    priority_queue<ll,vector<ll>,greater<ll>> pq;
    for(int i=1;i<=n;i++) pq.push(a[i]);
    while(pq.size()>1){
        auto x=pq.top();pq.pop();
        auto y=pq.top();pq.pop();
        res+=x+y;
        pq.push(x+y);
    }
    cout<<res;
}
// 64 位输出请用 printf("%lld")
