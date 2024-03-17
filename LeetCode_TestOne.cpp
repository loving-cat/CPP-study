#include<iostream>
#include<string>
#include<vector>
using namespace std;

//normal
//team 17 �绰�������ĸ���
class Solution {
    string _numToStr[10] = { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
public:
    //��һ���ݹ��Ӻ���
    void Combinations(const string& digits, size_t di, string combineStr, vector<string>& v)
    {
        if (di == digits.size())//��di�����һ���ʱ��
        {
            v.push_back(combineStr);//�ѻ�õ��ַ�β�嵽string���͵�combineStr��Ȼ�󷵻�
            return;
        }
        int num = digits[di] - '0';//ȡ���ַ�2 ɾ���ַ�0 ����ȡ��2
        string str = _numToStr[num];//�ڼ����ȡ���ĸ���
        for (auto ch : str)
        {
            Combinations(digits, di + 1, combineStr + ch, v);
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> v;
        if (digits.size() == 0)//�����������ǿմ�
            return v;
        Combinations(digits, 0, "", v);
        std::cout << std::endl;
        return v;
    }
};