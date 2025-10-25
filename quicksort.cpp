//j寻找比基准元素大的元素
//i之前包括i指向的是比基准元素小的元素
#include <iostream>
#include <algorithm>
#include <vector>

int partition(std::vector<int>& arr, int left, int right)
{
    int i = left - 1;
    for(int j = left; j < right; j++){
        if(arr[j] < arr[right]){
            i++;
            std::swap(arr[i], arr[j]);
        }

    }
    std::swap(arr[i + 1], arr[right]);
    return i + 1;
}

void quicksort(std::vector<int>& arr, int left, int right)
{
    if(left < right){
        int par = partition(arr, left, right);
        quicksort(arr, left, par - 1);
        quicksort(arr, par + 1, right);

    }

}

int main()
{
    std::vector<int> arr = {5, 1, 7, 3 ,9, 6};
    quicksort(arr, 0, arr.size() - 1);
    for(int i = 0; i < arr.size(); i++){
        std::cout << arr[i] << std::endl;
    }
}