/*
https://www.luogu.com.cn/problem/P1966

输入 n(1≤n≤1e5) 和两个长为 n 的数组 a 和 b，元素范围 [0,2^31)。保证 a 中没有重复元素，b 中没有重复元素。

每次操作，你可以交换 a 中的一对相邻元素，或者 b 中的一对相邻元素。
为了最小化 (a[i]-b[i])^2 之和，至少要操作多少次？
输出【最小操作次数】模 1e8 - 3 的结果。

离散化+排序+置换+逆序对
*/
#include<bits/stdc++.h>
using namespace std;


int main(){

  return 0;
}
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
