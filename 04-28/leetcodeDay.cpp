// https://leetcode.cn/problems/count-subarrays-with-score-less-than-k/?envType=daily-question&envId=2025-04-28
// 比较套路的滑动窗口吧
#define ll long long
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n=nums.size();
        int i=0,j=0;
        ll sum=0,res=0;
        while(j<n){
            sum+=nums[j];
            while(sum*(j-i+1)>=k) sum-=nums[i++];
            if(sum*(j-i+1)<k) res+=(j-i+1);
            j++;
        }    
        return res;
    }
};
