// https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/?envType=daily-question&envId=2025-05-01
/*
贪心的思路+二分
遍历所有工人，每个工人贪心的完成最难完成的任务
*/
#define ll long long
class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        int n=tasks.size(),m=workers.size();
        sort(tasks.begin(),tasks.end());
        sort(workers.begin(),workers.end());
        auto ck=[&](int mid){
            vector<int> w;
            for(int i=m-mid;i<m;i++) w.push_back(workers[i]);
            multiset<int> mst;
            for(int i=0;i<mid;i++) mst.insert(tasks[i]);
            // 让每一工人完成最难的可以完成的任务
            int k=pills;
            for(int i=0;i<mid;i++){
                auto it=mst.upper_bound(w[i]);
                if(it==mst.begin()){
                    // 用药
                    if(!k) return false;
                    k-=1;
                    auto jt=mst.upper_bound(w[i]+strength);
                    if(jt==mst.begin()) return false;
                    jt--;
                    mst.erase(jt);
                }
                else{
                    it--;
                    mst.erase(it);
                }
            }
            return true;
        };
        int l=0,r=min(n,m);
        while(l<=r){
            int mid=(l+r)/2;
            if(ck(mid)) l=mid+1;
            else r=mid-1;
        }
        return r;
    }
};
