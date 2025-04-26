// https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/description/?envType=daily-question&envId=2025-04-26
const int inf=1e9;
#define ll long long
class Solution {
public:
    int mi=inf,mx=-inf;
    int mii=-1,mxi=-1;
    void resume(){mi=inf,mx=-inf,mii=-1,mxi=-1;}
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int n=nums.size();
        ll res=0;
        // 记录当前窗口中最后出现的最小值的下标以及最后出现的最大值下标
        int i=0,j=0;
        while(j<n){
            if(nums[j]>=mx){
                mx=nums[j];
                mxi=j;
            }
            if(nums[j]<=mi){
                mi=nums[j];
                mii=j;
            }
            // 当前窗口肯定不行
            if(mi<minK || mx>maxK){
                j++;
                i=j;
                resume();
                continue;
            }
            // 以j为起点 看最左边能最多是几？
            // 这是关键
            if(mi==minK && mx==maxK){
                int idx=min(mii,mxi);
                res+=(idx-i+1);
            }
            j++;
        }
        return res;
    }
};
