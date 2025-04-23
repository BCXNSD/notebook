/*
https://www.luogu.com.cn/problem/P1966

输入 n(1≤n≤1e5) 和两个长为 n 的数组 a 和 b，元素范围 [0,2^31)。保证 a 中没有重复元素，b 中没有重复元素。

每次操作，你可以交换 a 中的一对相邻元素，或者 b 中的一对相邻元素。
为了最小化 (a[i]-b[i])^2 之和，至少要操作多少次？
输出【最小操作次数】模 1e8 - 3 的结果。

离散化+排序+置换+逆序对
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int read()
{
	int xx=0,fh=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		xx=xx*10+ch-'0';
		ch=getchar();
	}
	return fh==-1?-xx:xx;
}
const long long mod=99999997;
struct node{
	int ys;
	int pm;
	int bh;
}a1[100010],a2[100010];
bool cmp1(node x,node y)
{
	return x.ys<y.ys;
}
bool cmp2(node x,node y)
{
	return x.bh<y.bh;
}
int yxj[100010],n;
long long tr[100010],ans;
long long qm(long long x)
{
	while(x>=mod) x-=mod;
	while(x<0) x+=mod;
	return x;
}
int lbt(int x)
{
	return x&-x;
}
void xg(int i,long long x)
{
	for(;i<=n;i+=lbt(i))
	tr[i]=qm(tr[i]+x);
}
long long xw(int i)
{
	long long sum=0;
	for(;i>0;i-=lbt(i))
	sum=qm(sum+tr[i]);
	return sum;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) a1[i].ys=read(),a1[i].bh=i;
	for(int i=1;i<=n;++i) a2[i].ys=read(),a2[i].bh=i;
	sort(a1+1,a1+1+n,cmp1);
	sort(a2+1,a2+1+n,cmp1);
	for(int i=1;i<=n;++i) 
	yxj[i]=a1[i].bh;
	for(int i=1;i<=n;++i) a2[i].pm=i;
	sort(a2+1,a2+1+n,cmp2);
	for(int i=1;i<=n;++i)
	{
		xg(yxj[a2[i].pm],1);
		ans=qm(ans+xw(n)-xw(yxj[a2[i].pm]));
	}
	printf("%lld",ans);
	return 0;
}

// 下面是很久之前自己写的python版本
mod=10**8-3
global n,tree
def lowbit(x):
    return x&(-x)
def add(x):
    while x<=n:
        tree[x]+=1
        x+=lowbit(x)
def query(x):
    ans=0
    while x>0:
        ans=(ans+tree[x])%mod
        x-=lowbit(x)
    return ans

def get_rank(lst1,lst2):
    lth=len(lst1)
    
    rank=[0]*(lth+1)
    for i in range(lth):
        lst1[i]=[lst1[i],i+1]
        lst2[i]=[lst2[i],i+1]
    lst1.sort(key=lambda x:x[0])
    lst2.sort(key=lambda x:x[0])
    for i in range(lth):
        rank[lst1[i][1]]=lst2[i][1]
    return rank

def get_reverse(lst):
    ans=0
    for i in range(n):
        nums=query(lst[i])
        ans=(ans+i-nums)%mod
        add(lst[i])
    return ans
n=int(input())
a=list(map(int,input().split()))
b=list(map(int,input().split()))

tree=[0]*(10**5+10)

rank=get_rank(a,b)
ans=get_reverse(rank[1:])
print(ans)
