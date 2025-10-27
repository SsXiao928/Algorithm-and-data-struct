class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        for(int i = 0; i < n; i++){
            if(matrix[i][0] <= target && matrix[i][m - 1] >= target){
                int left = 0;
                int right = m - 1;
                int mid = 0;
                while(left <= right){
                    mid = (right - left) / 2 + left;
                    if(matrix[i][mid] == target){
                        return true;
                    }
                    if(matrix[i][mid] < target){
                        left = mid + 1;
                    }
                    if(matrix[i][mid] > target){
                        right = mid - 1;
                    }
                }
                break;
            }
        }

        return false;

    }
};