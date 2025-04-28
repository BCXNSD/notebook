/*
https://atcoder.jp/contests/abc212/tasks/abc212_d

一开始，有一个空的可重集合。
输入 q(1≤n≤2e5)，然后输入 q 个询问，格式如下：
"1 x"：把 x(1≤x≤1e9) 加到可重集合中。
"2 x"：把可重集合中的元素都增加 x(1≤x≤1e9)。
"3"：输出可重集合中的最小值，然后删除这个最小值。保证此时集合非空。
*/

// 与其将前面插入的所有的数都加上一个sum值 不如将当前的数减去之前的sum值
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int q;
int op,x;
ll sum=0;
int main(){
    
    multiset<ll> st;
    cin>>q;
    while(q--){
        cin>>op;
        if(op==1){
            cin>>x;
            st.insert(x-sum);
        }
        else if(op==2){
            cin>>x;
            sum+=x;
        }
        else{
            cout<<*st.begin()+sum<<'\n';
            st.erase(st.begin());
        }
    }
    return 0;
}
