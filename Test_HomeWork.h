#pragma once
#include<iostream>
#include<assert.h>
#include<stack>
#include<queue>
#include<set>
#include<string>
//leetcode 155
//思路，使用两个stack去写，一个正常存val 一个存储最小val，实时更新
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


//牛客 JZ31 栈的压入、弹出序列
//输入两个整数序列，第一个序列表示栈的压入顺序，
// 请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。
// 例如序列1, 2, 3, 4, 5是某栈的压入顺序，
// 序列4, 5, 3, 2, 1是该压栈序列对应的一个弹出序列，
// 但4, 3, 5, 1, 2就不可能是该压栈序列的弹出序列。
//1. 0 <= pushV.length == popV.length <= 1000
//2. - 1000 <= pushV[i] <= 1000
//3. pushV 的所有数字均不相同

//思路：①.先把入栈序列入栈
//          ②.栈顶元素和出栈序列是否匹配
//             a.如果匹配，持续出数据，直到不匹配or栈为空 返回①
//             b.如果不匹配就返回 ①
//结束标志：
//1.入栈序列走完 ----栈不为空
//2.出栈序列没有到尾 --> 不匹配序列

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param pushV int整型vector
     * @param popV int整型vector
     * @return bool布尔型
     */
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        // write code here
        int pushi = 0, popi = 0;
        stack<int> st;
        while (pushi < pushV.size())
        {
            st.push(pushV[pushi++]);
            while (!st.empty() && st.top() == popV[popi])//当st栈不为空且st的栈顶元素与popV[popi]元素相等，则出栈
            {
                ++popi;
                st.pop();
            }
        }
        return st.empty();//当栈为空时，表明全部匹配，return true；
    }
};

//150. 逆波兰表达式求值
//中等
//相关标签
//相关企业
//给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。
//
//请你计算该表达式。返回一个表示表达式值的整数。
//
//注意：
//
//有效的算符为 '+'、'-'、'*' 和 '/' 。
//每个操作数（运算对象）都可以是一个整数或者另一个表达式。
//两个整数之间的除法总是 向零截断 。
//表达式中不含除零运算。
//输入是一个根据逆波兰表示法表示的算术表达式。
//答案及所有中间计算结果可以用 32 位 整数表示。
//
//
//示例 1：
//
//输入：tokens = ["2", "1", "+", "3", "*"]
//输出：9
//解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
//示例 2：
//
//输入：tokens = ["4", "13", "5", "/", "+"]
//输出：6
//解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
//示例 3：
//
//输入：tokens = ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
//输出：22
//解释：该算式转化为常见的中缀算术表达式为：
//((10 * (6 / ((9 + 3) * -11))) + 17) + 5
//= ((10 * (6 / (12 * -11))) + 17) + 5
//= ((10 * (6 / -132)) + 17) + 5
//= ((10 * 0) + 17) + 5
//= (0 + 17) + 5
//= 17 + 5
//= 22
//
//
//提示：
//
//1 <= tokens.length <= 104
//tokens[i] 是一个算符（"+"、"-"、"*" 或 "/"），或是在范围[-200, 200] 内的一个整数
//
//
//逆波兰表达式：
//
//逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。
//
//平常使用的算式则是一种中缀表达式，如(1 + 2) * (3 + 4) 。
//该算式的逆波兰表达式写法为((1 2 + ) (3 4 + )*) 。
//逆波兰表达式主要有以下两个优点：
//
//去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + *也可以依据次序计算出正确结果。
//适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        set<string> s = { "+","-","*","/" };
        for (auto& str : tokens)
        {
            //1.操作数入栈，操作符运算
            if (s.find(str) != s.end())
            {
                //操作符
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