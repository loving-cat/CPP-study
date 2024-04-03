#pragma once
#include<iostream>
#include<assert.h>
#include<stack>
#include<queue>
#include<set>
#include<string>
//leetcode 155
//˼·��ʹ������stackȥд��һ��������val һ���洢��Сval��ʵʱ����
class MinStack {
public:
    MinStack() {

    }

    void push(int val) {
        _st.push(val);
        if (_minst.empty() || val <= _minst.top())
        {
            _minst.push(val);
        }
    }

    void pop() {
        if (_minst.top() == _st.top())
        {
            _minst.pop();
        }
        _st.pop();
    }

    int top() {
        return _st.top();
    }

    int getMin() {
        return _minst.top();
    }

    stack<int> _st;
    stack<int> _minst;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */


//ţ�� JZ31 ջ��ѹ�롢��������
//���������������У���һ�����б�ʾջ��ѹ��˳��
// ���жϵڶ��������Ƿ����Ϊ��ջ�ĵ���˳�򡣼���ѹ��ջ���������־�����ȡ�
// ��������1, 2, 3, 4, 5��ĳջ��ѹ��˳��
// ����4, 5, 3, 2, 1�Ǹ�ѹջ���ж�Ӧ��һ���������У�
// ��4, 3, 5, 1, 2�Ͳ������Ǹ�ѹջ���еĵ������С�
//1. 0 <= pushV.length == popV.length <= 1000
//2. - 1000 <= pushV[i] <= 1000
//3. pushV ���������־�����ͬ

//˼·����.�Ȱ���ջ������ջ
//          ��.ջ��Ԫ�غͳ�ջ�����Ƿ�ƥ��
//             a.���ƥ�䣬���������ݣ�ֱ����ƥ��orջΪ�� ���آ�
//             b.�����ƥ��ͷ��� ��
//������־��
//1.��ջ�������� ----ջ��Ϊ��
//2.��ջ����û�е�β --> ��ƥ������

class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     *
     *
     * @param pushV int����vector
     * @param popV int����vector
     * @return bool������
     */
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        // write code here
        int pushi = 0, popi = 0;
        stack<int> st;
        while (pushi < pushV.size())
        {
            st.push(pushV[pushi++]);
            while (!st.empty() && st.top() == popV[popi])//��stջ��Ϊ����st��ջ��Ԫ����popV[popi]Ԫ����ȣ����ջ
            {
                ++popi;
                st.pop();
            }
        }
        return st.empty();//��ջΪ��ʱ������ȫ��ƥ�䣬return true��
    }
};

//150. �沨�����ʽ��ֵ
//�е�
//��ر�ǩ
//�����ҵ
//����һ���ַ������� tokens ����ʾһ������ �沨����ʾ�� ��ʾ���������ʽ��
//
//�������ñ��ʽ������һ����ʾ���ʽֵ��������
//
//ע�⣺
//
//��Ч�����Ϊ '+'��'-'��'*' �� '/' ��
//ÿ����������������󣩶�������һ������������һ�����ʽ��
//��������֮��ĳ������� ����ض� ��
//���ʽ�в����������㡣
//������һ�������沨����ʾ����ʾ���������ʽ��
//�𰸼������м������������ 32 λ ������ʾ��
//
//
//ʾ�� 1��
//
//���룺tokens = ["2", "1", "+", "3", "*"]
//�����9
//���ͣ�����ʽת��Ϊ��������׺�������ʽΪ��((2 + 1) * 3) = 9
//ʾ�� 2��
//
//���룺tokens = ["4", "13", "5", "/", "+"]
//�����6
//���ͣ�����ʽת��Ϊ��������׺�������ʽΪ��(4 + (13 / 5)) = 6
//ʾ�� 3��
//
//���룺tokens = ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
//�����22
//���ͣ�����ʽת��Ϊ��������׺�������ʽΪ��
//((10 * (6 / ((9 + 3) * -11))) + 17) + 5
//= ((10 * (6 / (12 * -11))) + 17) + 5
//= ((10 * (6 / -132)) + 17) + 5
//= ((10 * 0) + 17) + 5
//= (0 + 17) + 5
//= 17 + 5
//= 22
//
//
//��ʾ��
//
//1 <= tokens.length <= 104
//tokens[i] ��һ�������"+"��"-"��"*" �� "/"���������ڷ�Χ[-200, 200] �ڵ�һ������
//
//
//�沨�����ʽ��
//
//�沨�����ʽ��һ�ֺ�׺���ʽ����ν��׺����ָ���д�ں��档
//
//ƽ��ʹ�õ���ʽ����һ����׺���ʽ����(1 + 2) * (3 + 4) ��
//����ʽ���沨�����ʽд��Ϊ((1 2 + ) (3 4 + )*) ��
//�沨�����ʽ��Ҫ�����������ŵ㣺
//
//ȥ�����ź���ʽ�����壬��ʽ����д�� 1 2 + 3 4 + *Ҳ�������ݴ���������ȷ�����
//�ʺ���ջ�������㣺������������ջ�����������ȡ��ջ���������ֽ��м��㣬�������ѹ��ջ��

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        set<string> s = { "+","-","*","/" };
        for (auto& str : tokens)
        {
            //1.��������ջ������������
            if (s.find(str) != s.end())
            {
                //������
                int right = st.top();
                st.pop();
                int left = st.top();
                st.pop();
                switch (str[0])
                {
                case '+':
                    st.push(left + right);
                    break;
                case '-':
                    st.push(left - right);
                    break;
                case '*':
                    st.push(left * right);
                    break;
                case '/':
                    st.push(left / right);
                    break;

                }
            }
            else
            {
                st.push(stoi(str));
            }
        }
        return st.top();
    }
};