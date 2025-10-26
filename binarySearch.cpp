#include <iostream>
#include <vector>

int BinarySearch(int target, std::vector<int>& arr)
{
    int left = 0;
    int right = arr.size() - 1;
    int mid = -1;
    int res = -1;//结果

    while(left < right){
        mid = left + (right - left) / 2;
        //std::cout << mid << std::endl;
        if(arr[mid] == target){
            res = mid;
            break;
        }
        if(arr[mid] > target){
            right = mid - 1;
        }
        if(arr[mid] < target){
            left = mid + 1;
        }
    }
    if(arr[left] == target)
        res = left;

    return res;
}

int main()
{
    std::vector<int> arr = {1, 5, 8, 9, 17};

    std::cout << BinarySearch(1, arr);
}