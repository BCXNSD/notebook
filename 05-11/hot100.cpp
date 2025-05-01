// https://leetcode.cn/problems/min-stack/?envType=study-plan-v2&envId=top-100-liked
/*
当时想用两个栈 一个数字栈 一个字符串栈 但是字符串假设重复完以后 前面可能是数字和字符串 如果是字符串的话就要拼接
写的挺久的
*/
class Solution {
public:
    string decodeString(string s) {
        int n=s.size();
        stack<string> ops;
        string res="";
        auto ck=[](char c,bool ok){
            if(!ok) return (c>='0' && c<='9')?1:0;
            return (c>='a' && c<='z')?1:0;
        };
        for(int i=0;i<n;i++){
            char c=s[i];
            // cout<<res<<' ';
            if(c=='[') continue;
            else if(c==']'){
                string p=ops.top(); ops.pop();
                string k=ops.top(); ops.pop();
                int times=stoi(k);
                string x="";
                while(times--) x+=p;
                if(ops.empty()) res+=x;
                else{
                    // 如果前面还是字符 直接拼接
                    if(ops.top()[0]>='a'){
                        auto t=ops.top(); ops.pop();
                        ops.push(t+x);
                    }
                    else ops.push(x);
                }
            }
            else{
                bool ok=true;
                if(c>='0' && c<='9') ok=false;
                int j=i;
                string x="";
                while(j<n && ck(s[j],ok)) x+=s[j++];
                if(!ok){
                    ops.push(x);
                    i=j-1;
                    continue;
                }
                // 是字符串 没在栈内 直接计算
                if(ops.empty()) res+=x;
                else{
                    if(ops.top()[0]>='a'){
                        auto t=ops.top(); ops.pop();
                        ops.push(t+x);
                    }
                    else ops.push(x);
                }
                i=j-1;
            }
        }
        return res;
    }
};
