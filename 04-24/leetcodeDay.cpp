/*
每一枚举到满足的右端点的时候，后面都是满足的，然后让左端点一直往前移动直到不满足
*/
class Solution {
public:
    int c[2010];
    int res,k=0;
    int countCompleteSubarrays(vector<int>& nums) {
        for(auto &x:nums){
            c[x]++;
            if(c[x]==1) k++;
        }
        int n=nums.size();
        vector<int> cnt(2010,0);
        int i=0,j=0,kk=0;
        while(j<n){
            cnt[nums[j]]++;
            if(cnt[nums[j]]==1) kk++;
            while(kk==k){
                res+=(n-j);
                cnt[nums[i]]--;
                if(cnt[nums[i]]==0) kk--;
                i++;
            }
            j++;
        }
        return res;
    }
};
