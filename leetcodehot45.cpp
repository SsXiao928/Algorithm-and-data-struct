#include <iostream>
#include <vector>

class Solution {
public:
    int jump(std::vector<int>& nums) {
        int step = 0, end = 0, maxpos = 0, n = nums.size();
        for(int i = 0; i < n - 1; ++i){
            if(i <= end){
                maxpos = std::max(maxpos, i + nums[i]);
            }
            if(end == i){
                end = maxpos;
                step++;
            }
        }
        return step;
    }
};