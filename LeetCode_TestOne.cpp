#include<iostream>
#include<string>
#include<vector>
using namespace std;

//normal
//team 17 电话号码的字母组合
class Solution {
    string _numToStr[10] = { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
public:
    //做一个递归子函数
    void Combinations(const string& digits, size_t di, string combineStr, vector<string>& v)
    {
        if (di == digits.size())//当di到最后一层的时候
        {
            v.push_back(combineStr);//把获得的字符尾插到string类型的combineStr，然后返回
            return;
        }
        int num = digits[di] - '0';//取到字符2 删除字符0 才能取到2
        string str = _numToStr[num];//第几层就取到哪个串
        for (auto ch : str)
        {
            Combinations(digits, di + 1, combineStr + ch, v);
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> v;
        if (digits.size() == 0)//当传过来的是空串
            return v;
        Combinations(digits, 0, "", v);
        std::cout << std::endl;
        return v;
    }
};
//复写数
class SolutionTwo
{
public:
    void duplicateZeros(vector<int>& arr)
    {
        //1.先找到最后一个数
        int cur = 0, dest = -1, n = arr.size();
        while (cur < n)
        {
            if (arr[cur]) dest++;
            else dest += 2;
            if (dest >= n - 1)break;
            cur++;
        }
        //处理边界情况
        if (dest == n)
        {
            arr[n - 1] = 0;
            cur--; dest -= 2;
        }
        //3.从后向前完成复写操作
        while (cur >= 0)
        {
            if (arr[cur]) arr[dest--] = arr[cur--];
            else
            {
                arr[dest--] = 0;
                arr[dest--] = 0;
                cur--;
            }
        }
    }
};
//面试经典150题
//合并有序数组
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = 0, p2 = 0;
        int sorted[m + n];//创建另外一个数组
        int cur = 0;
        while (p1 < m || p2 < n)
        {
            if (p1 == m)//当p1先遍历完
                cur = nums2[p2++];//cur就去先拿nums2[p2]的值，然后++
            else if (p2 == n)//如果p2先遍历完
                cur = nums1[p1++];//cur就先去拿nums1[p1]的值，然后++
            else if (nums1[p1] < nums2[p2])//当nums1[p1]的值小于nums2[p2]的值时
                cur = nums1[p1++];//cur去拿nums1[p1]的值
            else//当nums1[p1]>nums2[p2]
                cur = nums2[p2++];//cur拿到nums2[p2]的值
            sorted[p1 + p2 - 1] = cur;//用第三个数组sorted 拿到cur内部的值，依次循环 P1+P2-1，因为p1,p2是下标，所以要-1防止越界访问
        }
        for (int i = 0; i != m + n; ++i)//通过m+n次遍历，让nums1数组拿到sorted数组内的值然后return nums1；
        {
            nums1[i] = sorted[i];
        }
    }
};