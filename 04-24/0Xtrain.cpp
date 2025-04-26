/*
https://atcoder.jp/contests/abc332/tasks/abc332_f

输入 n(1≤n≤2e5) m(1≤m≤2e5) 和长为 n 的数组 a(0≤a[i]≤1e9)。下标从 1 开始。
输入 m 个操作，每次操作输入 L R x(0≤x≤1e9)，表示在 [L,R] 中等概率地选一个整数 i，然后把 a[i] 替换成 x。

输出最终 a[1],a[2],...,a[n] 的期望值，模 M=998244353。
注：如果期望值是一个分数 p/q，你需要输出 p*pow(q,M-2)%M。

操作一段区间的时候，假设p=1/(l+r+1)
每个数有p的概率变成x 有(1-p)的概率变成a[i]
a[i]=p*x+(1-p)*a[i]
也就是区间乘(1-p) 区间加p*x
*/
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(),(x).end()
const int N=2e5+10;
const int mod=998244353;

int n,m;
ll a[N];
struct SegTree{
	int l,r;
	ll mul_tag,add_tag;
}t[N<<2];
ll fp(ll a, ll b){
  ll res=1;
  while(b){
    if(b&1) res=res*a%mod;
    a=a*a%mod;
    b>>=1;
  }
  return res;
}
void down(int p){
	if(t[p].mul_tag!=1){
		t[p<<1].mul_tag*=t[p].mul_tag;
		t[p<<1|1].mul_tag*=t[p].mul_tag;
		
		// 这里的add标记也要下移 
		t[p<<1].add_tag*=t[p].mul_tag;
		t[p<<1|1].add_tag*=t[p].mul_tag;
		
		t[p<<1].mul_tag%=mod;
		t[p<<1|1].mul_tag%=mod;
		t[p<<1].add_tag%=mod;
		t[p<<1|1].add_tag%=mod;
		t[p].mul_tag=1;
	}
	if(t[p].add_tag){
		t[p<<1].add_tag+=t[p].add_tag;
		t[p<<1|1].add_tag+=t[p].add_tag;
		t[p<<1].add_tag%=mod;
		t[p<<1|1].add_tag%=mod;
		t[p].add_tag=0;
	}	
}
void build(int p,int l,int r){
	t[p].l=l,t[p].r=r;
	t[p].mul_tag=1;
	if(l==r) return;
	int mid=(l+r)/2;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
}
void modify_mul(int p,int x,int y,ll k){
	if(t[p].l==x && t[p].r==y){
		t[p].mul_tag=t[p].mul_tag*k%mod;
		t[p].add_tag=t[p].add_tag*k%mod;
		return; 
	}
	down(p);
	int mid=(t[p].l+t[p].r)/2;
	if(y<=mid) modify_mul(p<<1,x,y,k);
	else if(x>mid) modify_mul(p<<1|1,x,y,k);
	else modify_mul(p<<1,x,mid,k),modify_mul(p<<1|1,mid+1,y,k);
}
void modify_add(int p,int x,int y,ll k){
	if(t[p].l==x && t[p].r==y){
		t[p].add_tag=(t[p].add_tag+k)%mod;
		return; 
	}
	down(p);
	int mid=(t[p].l+t[p].r)/2;
	if(y<=mid) modify_add(p<<1,x,y,k);
	else if(x>mid) modify_add(p<<1|1,x,y,k);
	else modify_add(p<<1,x,mid,k),modify_add(p<<1|1,mid+1,y,k);
}
void spread(int p,int l,int r){
    if(l==r){
        a[l]=(a[l]*t[p].mul_tag%mod+t[p].add_tag)%mod;
        return;
    }
    down(p);
    int mid=(l+r)/2;
    spread(p<<1,l,mid),spread(p<<1|1,mid+1,r);
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
  /*
  每个数有p的概率变成x 有(1-p)的概率变成a[i]
  a[i]=p*x+(1-p)*a[i]
  也就是区间乘(1-p) 区间加p*x
  如果p等于1 那就是直接修改成x
  */
	for(int i=1,x,y,v;i<=m;i++){
		cin>>x>>y>>v;
    ll p=(y-x+1);
    if(p==1){
      modify_mul(1,x,y,0);
      modify_add(1,x,y,v);
    }
    else{
      modify_mul(1,x,y,(p-1)*fp(p,mod-2)%mod);
      modify_add(1,x,y,fp(p,mod-2)%mod*v%mod);
    }
	}
	spread(1,1,n);
	for(int i=1;i<=n;i++) cout<<a[i]<<' ';
	return 0;
}
