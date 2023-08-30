#include <bits/stdc++.h>

using namespace std;

/*
[nums] always has to be sorted in ascending order for this to work.
If sorted in descending order then conditions can be reversed, but array must be sorted.
*/
int binarySearch(vector<int> nums, int target)
{
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2; // to avoid integer overflow when  (lo + hi) > INT_MAX
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] > target)
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return -1; // when target is not found in the array
}

int main()
{
    return 0;
}