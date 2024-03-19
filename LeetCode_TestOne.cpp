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
//��д��
class SolutionTwo
{
public:
    void duplicateZeros(vector<int>& arr)
    {
        //1.���ҵ����һ����
        int cur = 0, dest = -1, n = arr.size();
        while (cur < n)
        {
            if (arr[cur]) dest++;
            else dest += 2;
            if (dest >= n - 1)break;
            cur++;
        }
        //����߽����
        if (dest == n)
        {
            arr[n - 1] = 0;
            cur--; dest -= 2;
        }
        //3.�Ӻ���ǰ��ɸ�д����
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
//���Ծ���150��
//�ϲ���������
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = 0, p2 = 0;
        int sorted[m + n];//��������һ������
        int cur = 0;
        while (p1 < m || p2 < n)
        {
            if (p1 == m)//��p1�ȱ�����
                cur = nums2[p2++];//cur��ȥ����nums2[p2]��ֵ��Ȼ��++
            else if (p2 == n)//���p2�ȱ�����
                cur = nums1[p1++];//cur����ȥ��nums1[p1]��ֵ��Ȼ��++
            else if (nums1[p1] < nums2[p2])//��nums1[p1]��ֵС��nums2[p2]��ֵʱ
                cur = nums1[p1++];//curȥ��nums1[p1]��ֵ
            else//��nums1[p1]>nums2[p2]
                cur = nums2[p2++];//cur�õ�nums2[p2]��ֵ
            sorted[p1 + p2 - 1] = cur;//�õ���������sorted �õ�cur�ڲ���ֵ������ѭ�� P1+P2-1����Ϊp1,p2���±꣬����Ҫ-1��ֹԽ�����
        }
        for (int i = 0; i != m + n; ++i)//ͨ��m+n�α�������nums1�����õ�sorted�����ڵ�ֵȻ��return nums1��
        {
            nums1[i] = sorted[i];
        }
    }
};