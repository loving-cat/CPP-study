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