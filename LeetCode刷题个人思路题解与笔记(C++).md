[136. 只出现一次的数字 - 力扣（LeetCode）](https://leetcode.cn/problems/single-number/description/)
题目：

给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
说明：
你的算法应该具有线性时间复杂度。你可以不使用额外空间来实现吗？

显然，这一题是今天题目的简化版。在一堆成对的数字中找一个落单的，可以考虑使用异或运算。

理由是：

1.两个相同数字做异或运算，结果为0。这个结果可以帮我们排除掉成对的数字；
2.0和任何数字进行异或运算，都得到这个数字本身。
所以，只要对nums中的所有元素进行异或，就可以得到答案。

代码：

```C++
class Solution {
public:
    int singleNumber(vector<int>& nums) { // 异或运算，对所有进行异或运算，最终得到的就是结果。
        int res = 0;
        for (auto num: nums) 
            res ^= num;
        return res;
    }
};
```

[137. 只出现一次的数字 II - 力扣（LeetCode）](https://leetcode.cn/problems/single-number-ii/description/)
今天的题目和剑指 Offer 56 - II. 数组中数字出现的次数 II是一样的。如果大家没有《剑指offer 第二版》的电子版，可以点击这里下载。

从上面一题可以得到位运算的思路。但是如果还是仅仅使用异或运算，我们会发现寸步难行。也就是说，这道题虽然和上面的题目很像，但方法上面不能简单地进行承接。（Too Sad~o(╥﹏╥)o）

我们换个思路，或许可以考虑从每个元素都出现三次入手。如果从次数入手，我们可以想到能不能和什么东西整除3挂钩。因为除了某个元素，其他元素都是三个三个为一组的。

我们可以注意到：-2^31 <= nums[i] <= 2^31 - 1，这意味着我们处理的数据都是32位的数据。如果把每一个数字都看成二进制，那么一个十进制数nums[i]对应一个32位的二进制数。将所有nums[i]对应的二进制数的对应位求和，将每一对应位的和值与3进行取模运算，得到的余数就是答案的对应二进制位的数值。这是因为除了答案本身，其它元素都是三个三个为一组的。

上面的语言有些抽象，我们举个例子：

如果输入是：nums = [2,2,3,2]，那么它的各个元素对应的32位二进制数就是[00000000000000000000000000000010, 

 00000000000000000000000000000010, 

 00000000000000000000000000000011, 

 00000000000000000000000000000010]；
接着，对这些二进制数的对应位进行求和，得到：[00000000000000000000000000000041]；
对这个求和结果的每一位进行3的取模运算，得到：[00000000000000000000000000000011]；
把上面的结果从二进制转换为十进制，就是：3。这就是我们的答案。
代码：

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; i++) { // 因为nums[i]是32位整数，
        // 所以针对每一位的对应二进制数值求和
            int sum = 0;
            for (int num : nums) {//（num>>i）&1 提取最后一位
                sum += ((num >> i) & 1); // 提取从右往左数第i位的数值，将所有nums[i]
                // 二进制下的第i位数值进行求和
            }
            if (sum % 3 == 1) { // 如果没办法被3整除，那么说明落单的那个数的第i位是1不是0
                res |= (1 << i);//按位或等，一边为1则全为1，全为1则为0
            }
        }
        return res; // 输出结果
    }
};

```

[260. 只出现一次的数字 III - 力扣（LeetCode）](https://leetcode.cn/problems/single-number-iii/description/)
题目：

给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。你可以按 任意顺序 返回答案。
进阶：你的算法应该具有线性时间复杂度。你能否仅使用常数空间复杂度来实现？

示例：

输入：nums = [1,2,1,3,2,5]
输出：[3,5]
解释：[5, 3] 也是有效的答案。

本题中，次数回归到一开始的两次，但是比较调皮的是，落单的元素不止一个。

已经写过的上面两道题目，对这道题可以带来什么样的启发？

启发一：应该可以尝试异或运算，因为元素出现的频次变成了2；
启发二：显然做一次异或运算不能得到结果，在一次异或运算的基础上，我们可以效仿力扣137. 只出现一次的数字 II，对异或之后的结果的二进制位进行分析处理。
我们的核心思想还是使用异或运算，但对于两个落单的元素，我们需要想到一个分类法则，让它们俩分来。对于它们俩所在的两个分组，分别进行异或运算，就可以得到答案。

下面是分类方法的设计，我们举一个例子看看：

对于
$$
nums = [1,2,1,3,2,5]
$$
，

转为二进制为：
$$
[0001, 0010, 0001, 0011, 0010, 0101];
$$
进行异或，得到结果：
$$
0110；
$$
针对上面的结果，发现从右往左数（从0开始）第1位上，两个落单的数字是不同的。我们可以把数组nums中的数值进行分组，分组依据就是各个数值nums[i]的第1位是否为0。这样一来，我们可以把两个落单的数值分到不同的组里面。在不同组里面，我们使用异或运算即可。我们可以把这个不同的位数提取出来：0010；
将[1,2,1,3,2,5]逐个和0010进行与运算，进行“分组”。之后对每一个“分组”中的元素进行异或运算即可。
**代码：**

```c++
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int group1 = 0, group2 = 0;
        int diff = 0, bit = 1;
        for (int num : nums) // 异或运算，目的是找到两个落单数值的不同，便于后面分类
            diff ^= num;
        while ((diff & bit) == 0) //  左移运算，找到二者某一位的不同，将这一位定为分类依据
            bit <<= 1;
        for (int num : nums) { // 对元素进行遍历    
            if(num & bit) group1 ^= num; // 对于num，如果对于bit为1，分类为group1，对这个
            // group进行异或，可以找到落单的数值
            else group2 ^= num; // 如果num的bit对应的是0，那么异或找到另一个落单的数值
        }
        return vector<int> {group1, group2};   // 返回结果
    }
};
```

[88. 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/)

给你两个按 **非递减顺序** 排列的整数数组 `nums1` 和 `nums2`，另有两个整数 `m` 和 `n` ，分别表示 `nums1` 和 `nums2` 中的元素数目。

请你 **合并** `nums2` 到 `nums1` 中，使合并后的数组同样按 **非递减顺序** 排列。

**注意：**最终，合并后数组不应由函数返回，而是存储在数组 `nums1` 中。为了应对这种情况，`nums1` 的初始长度为 `m + n`，其中前 `m` 个元素表示应合并的元素，后 `n` 个元素为 `0` ，应忽略。`nums2` 的长度为 `n` 

 

**示例 1：**

```
输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
```

**示例 2：**

```
输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 [] 。
合并结果是 [1] 。
```

**示例 3：**

```
输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并的数组是 [] 和 [1] 。
合并结果是 [1] 。
注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。
```

**提示：**

- `nums1.length == m + n`
- `nums2.length == n`
- `0 <= m, n <= 200`
- `1 <= m + n <= 200`
- -10^9 <= nums1[i], nums2[j] <= 10^

**进阶：**你可以设计实现一个时间复杂度为 `O(m + n)` 的算法解决此问题吗？

```c++
class Solution{
    pubilc:
    	void merge(vector<int>& nums1,int m,vector<int>& nums2,int n)
        {
            //思路：
            //本体使用双指针,p指向nums1，q指向nums2
            int p=0,q = 0;
            //创建一个临时变量方便拿到两个数组内的值
            int tmp = 0;
            //创建第三个数组拿到值
            int sorted[m+n] = 0;
            //循环，当p大于m时，表明已经遍历完nums1数组，当q大于n时，代表已经遍历完nums2
            while(p < m || q < n)
            {
                //第一个判断条件，可以假设p已经遍历完nums1了
                if(p == m)
                {
                    //由于nums1遍历完后没有值，直接让tmp拿num2内的值
                    tmp = nums2[q++];
                }//第二个判断条件，与上方相同，假设遍历完nums2
                else if(q == n)
                {
                    tmp = num1[p++];
                }//当两个极端情况判断完毕后，第三个判断条件就正常去判断大小
                else if(nums1[p]<nums2[q])
                {
                    tmp = nums1[p++];
                }
                else
                {
                    tmp = nums2[q++];
                }
                //判断完毕后从临时变量中拿到值
                //p+q-1为sorted数组的当前位置
                sorted[p+q-1] = tmp;
           		
            }
            //使用循环 让nums1拿到sorted数组的值
            for(int i = 0; i != m + n; ++i)
            {
                nums1[i] = sorted[i];
            }
            return nums1;
        }
}


//简洁版本
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1=0,p2=0;
        int sorted[m+n];//创建另外一个数组
        int cur = 0;
        while(p1<m||p2<n)
        {
            if(p1==m)//当p1先遍历完
                cur = nums2[p2++];//cur就去先拿nums2[p2]的值，然后++
            else if(p2 == n)//如果p2先遍历完
                cur = nums1[p1++];//cur就先去拿nums1[p1]的值，然后++
            else if(nums1[p1]<nums2[p2])//当nums1[p1]的值小于nums2[p2]的值时
                cur = nums1[p1++];//cur去拿nums1[p1]的值
            else//当nums1[p1]>nums2[p2]
                cur = nums2[p2++];//cur拿到nums2[p2]的值
            sorted[p1+p2-1] = cur;//用第三个数组sorted 拿到cur内部的值，依次循环 P1+P2-1，因为p1,p2是下标，所以要-1防止越界访问
        }
        for(int i = 0;i!=m+n;++i)//通过m+n次遍历，让nums1数组拿到sorted数组内的值然后return nums1；
        {
            nums1[i] = sorted[i];
        }
    }
};
```

[27. 移除元素](https://leetcode.cn/problems/remove-element/)

给你一个数组 `nums` 和一个值 `val`，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 `val` 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 `O(1)` 额外空间并 **[原地 ](https://baike.baidu.com/item/原地算法)修改输入数组**。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

**说明:**

为什么返回数值是整数，但输出的答案是数组呢?

请注意，输入数组是以**「引用」**方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

```
// nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
int len = removeElement(nums, val);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

 

**示例 1：**

```
输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2]
解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。例如，函数返回的新长度为 2 ，而 nums = [2,2,3,3] 或 nums = [2,2,0,0]，也会被视作正确答案。
```

**示例 2：**

```
输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,3,0,4]
解释：函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。注意这五个元素可为任意顺序。你不需要考虑数组中超出新长度后面的元素。
```

 

**提示：**

- `0 <= nums.length <= 100`
- `0 <= nums[i] <= 50`
- `0 <= val <= 100`

```c++
//双指针解法
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int sz = nums.size();//拿到数组长度
        int left = 0;//设置第一个指针指向初始位置
        //设置第二个指针指向初始位置
        for(int right = 0;right<sz;++right)
        {
            //假设right指向位置的值不等于val，则让left位置拿到right的值，然后让left向后++，最后return left位置
            if(nums[right]!=val)
            {
                nums[left] = nums[right];
                left++;
            }
        }
        return left;
    }
};
//双指针优化解法
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //一个在头 一个在尾
        int left = 0, right = nums.size();
        //当左边小于右边时就进入循环，反之终止循环
        while(left<right)
        {
            //当left指向位置的值==val时，让left指向位置的值被数组最后一个值覆盖，然后让数组（--），如果！=val就让left++ ，找到下一个==val的位置，依次覆盖，最后return left
            if(nums[left] == val)
            {
                nums[left] = nums[right-1];
                right--;
            }
            else
                left++;
        }
        return left;
    }
};

//循环解法
//当nums[i]位置==val 时 利用continue的特性短暂跳出此位置的循环，直接执行下次循环，最后return n
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int sz = nums.size();
        int n = 0;
        for(int i = 0; i < sz;++i)
        {
            if(nums[i] == val)
                continue;
            nums[n] = nums[i];
            n++;
        }
        return n;
    }
};
```

[215. 数组中的第K个最大元素 - 力扣（LeetCode）](https://leetcode.cn/problems/kth-largest-element-in-an-array/)

给定整数数组 `nums` 和整数 `k`，请返回数组中第 `**k**` 个最大的元素。

请注意，你需要找的是数组排序后的第 `k` 个最大的元素，而不是第 `k` 个不同的元素。

你必须设计并实现时间复杂度为 `O(n)` 的算法解决此问题。

**示例 1:**

```
输入: [3,2,1,5,6,4], k = 2
输出: 5
```

**示例 2:**

```
输入: [3,2,3,1,2,4,5,5,6], k = 4
输出: 4
```

**提示：**

- `1 <= k <= nums.length <= 105`
- `-104 <= nums[i] <= 104`

```C++
//暴力解法，不符合题目中时间复杂度的要求
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());

        return nums[nums.size()-k];
    }
};
//堆排 时间复杂度 O(k*logN+N)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(),nums.end());//O(N)
        while(--k)//K*logN
        {
            pq.pop();
        }
        return pq.top();
    }
};
//小堆
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(),nums.begin()+k);//建小堆
        for(size_t i = k;i<nums.size();++i)
        {
            if(nums[i]>pq.top())//如果遍历到的值大于当前堆顶元素,就把当前堆的值pop掉，再把数组中的值放进来
            {
                pq.pop();
                pq.push(nums[i]);
            }
        }
        return pq.top();
        
    }
};
```

[155. 最小栈 - 力扣（LeetCode）](https://leetcode.cn/problems/min-stack/)

设计一个支持 `push` ，`pop` ，`top` 操作，并能在常数时间内检索到最小元素的栈。

实现 `MinStack` 类:

- `MinStack()` 初始化堆栈对象。
- `void push(int val)` 将元素val推入堆栈。
- `void pop()` 删除堆栈顶部的元素。
- `int top()` 获取堆栈顶部的元素。
- `int getMin()` 获取堆栈中的最小元素。

**示例 1:**

```
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
```

**提示：**

- `-231 <= val <= 231 - 1`

- `pop`、`top` 和 `getMin` 操作总是在 **非空栈** 上调用

- `push`, `pop`, `top`, and `getMin`最多被调用 `3 * 10^4 次

  思路：首先实例**st** and **minst**两个栈，**st**用来正常存放push的值，**minst**用来存放**st**的**最小值**

  当**st**拿到第一个值时，**minst**默认拿到第一个值为最小值，后续**st**拿到的值与前面push的值做对比，如果小，则push到**minst**更新，pop值时，**minst**将会与**st**同步pop

  ```C++
  class MinStack{
  	public:
  		MinStack{}
  		void push(int val)
  		{
  			_st.push(val);
  			if(_minst.empty()||val<=_minst.top())]
  			{
  				_minst.push(val);
  			}
  		}
  		void pop()
  		{
  			if(_minst.top()==_st.top())
  			{
  				_minst.pop();
  			}
  			_st.pop();
  		}
  		int top()
  		{
  			return _st.top();
  		}
  		int getMin()
  		{
  			return _minst.top();
  		}
  		stack<int> _st;
  		stack<int> _minst;
  }
  ```

[栈的压入、弹出序列_牛客题霸_牛客网 (nowcoder.com)](https://www.nowcoder.com/practice/d77d11405cc7470d82554cb392585106?tpId=13&&tqId=11174&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking)

## 描述

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。

1. 0<=pushV.length == popV.length <=1000
2. -1000<=pushV[i]<=1000

3. pushV 的所有数字均不相同

## 示例1

输入：

```
[1,2,3,4,5],[4,5,3,2,1]
```

返回值：

```
true
```

说明：

```
可以通过push(1)=>push(2)=>push(3)=>push(4)=>pop()=>push(5)=>pop()=>pop()=>pop()=>pop()
这样的顺序得到[4,5,3,2,1]这个序列，返回true      
```

## 示例2

输入：

```
[1,2,3,4,5],[4,3,5,1,2]
```

返回值：

```
false
```

说明：

```
由于是[1,2,3,4,5]的压入顺序，[4,3,5,1,2]的弹出顺序，要求4，3，5必须在1，2前压入，且1，2不能弹出，但是这样压入的顺序，1又不能在2之前弹出，所以无法形成的，返回false
```

思路：

```C++
class Solution{
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
        int pushi = 0,popi = 0;
        stack<int> st;
        while(pushi < pushV.size())
        {
            st.push(pushV[pushi++]);
            while(!st.empty()&&st.top() == popV[popi])
            {
                ++popi;
                st.pop();
            }
        }
        return st.empty();
    }
}
```

[150. 逆波兰表达式求值 - 力扣（LeetCode）](https://leetcode.cn/problems/evaluate-reverse-polish-notation/description/)

给你一个字符串数组 `tokens` ，表示一个根据 [逆波兰表示法](https://baike.baidu.com/item/逆波兰式/128437) 表示的算术表达式。

请你计算该表达式。返回一个表示表达式值的整数。

**注意：**

- 有效的算符为 `'+'`、`'-'`、`'*'` 和 `'/'` 。
- 每个操作数（运算对象）都可以是一个整数或者另一个表达式。
- 两个整数之间的除法总是 **向零截断** 。
- 表达式中不含除零运算。
- 输入是一个根据逆波兰表示法表示的算术表达式。
- 答案及所有中间计算结果可以用 **32 位** 整数表示。

**示例 1：**

```
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
```

**示例 2：**

```
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
```

**示例 3：**

```
输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
```

**提示：**

- `1 <= tokens.length <= 104`
- `tokens[i]` 是一个算符（`"+"`、`"-"`、`"*"` 或 `"/"`），或是在范围 `[-200, 200]` 内的一个整数

**逆波兰表达式：**

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

- 平常使用的算式则是一种中缀表达式，如 `( 1 + 2 ) * ( 3 + 4 )` 。
- 该算式的逆波兰表达式写法为 `( ( 1 2 + ) ( 3 4 + ) * )` 。

逆波兰表达式主要有以下两个优点：

- 去掉括号后表达式无歧义，上式即便写成 `1 2 + 3 4 + * `也可以依据次序计算出正确结果。
- 适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中

思路：。。。。。

```C++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        set<string> s = {"+","-","*","/"};
        for(auto& str : tokens)
        {
            //1.操作数入栈，操作符运算
            if(s.find(str)!=s.end())
            {
                //操作符
                int right = st.top();
                st.pop();
                int left = st.top();
                st.pop();
                switch(str[0])
                {
                    case '+':
                        st.push(left+right);
                        break;
                    case '-':
                        st.push(left-right);
                        break;
                    case '*':
                        st.push(left*right);
                        break;
                    case '/':
                        st.push(left/right);
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
```



[606. 根据二叉树创建字符串 - 力扣（LeetCode）](https://leetcode.cn/problems/construct-string-from-binary-tree/description/)

给你二叉树的根节点 `root` ，请你采用前序遍历的方式，将二叉树转化为一个由括号和整数组成的字符串，返回构造出的字符串。

空节点使用一对空括号对 `"()"` 表示，转化后需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/05/03/cons1-tree.jpg)

```
输入：root = [1,2,3,4]
输出："1(2(4))(3)"
解释：初步转化后得到 "1(2(4)())(3()())" ，但省略所有不必要的空括号对后，字符串应该是"1(2(4))(3)" 。
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/05/03/cons2-tree.jpg)

```
输入：root = [1,2,3,null,4]
输出："1(2()(4))(3)"
解释：和第一个示例类似，但是无法省略第一个空括号对，否则会破坏输入与输出一一映射的关系。
```

**提示：**

- 树中节点的数目范围是 `[1, 104]`
- `-1000 <= Node.val <= 1000`

思路：

1.左右为空可以省略括号

2.右为空省略括号

3.左为空，不能省略括号，无法跟右为空区分

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    string tree2str(TreeNode* root) {
		string str;//创建一个字符串数组拿着括号和值返回
        if(root==nullptr)
        	return str;
        str += to_string(root->val);//转类型，int->string
            
        if(root->left || root->right)
        {
            str += '(';
            str += tree2str(root->left);
            str += ')'
        }
        if(root->right)
        {
            str += '(';
            str += tree2str(root->right);
            str += ')';
        }
        return str;
    }
};
```

[102. 二叉树的层序遍历 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-level-order-traversal/description/)

给你二叉树的根节点 `root` ，返回其节点值的 **层序遍历** 。 （即逐层地，从左到右访问所有节点）。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/02/19/tree1.jpg)

```
输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]
```

**示例 2：**

```
输入：root = [1]
输出：[[1]]
```

**示例 3：**

```
输入：root = []
输出：[]
```

**提示：**

- 树中节点数目在范围 `[0, 2000]` 内
- `-1000 <= Node.val <= 1000`

解法 队列，用变量控制一层的个数，出完一层再出下一层

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {

    }
};
```

[236. 二叉树的最近公共祖先 - 力扣（LeetCode）](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/)

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

[百度百科](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

**示例 1：**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
```

**示例 3：**

```
输入：root = [1,2], p = 1, q = 2
输出：1
```

**提示：**

- 树中节点数目在范围 `[2, 105]` 内。
- `-109 <= Node.val <= 109`
- 所有 `Node.val` `互不相同` 。
- `p != q`
- `p` 和 `q` 均存在于给定的二叉树中。

**思路：**

**1.每个节点都有parent（三叉链）->链表相交**

**2.普通二叉树，规律：p和q分别在左右，当前节点就是公共祖先 or 其中一个就是当前树的根**

![image-20240420110122210](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240420110122210.png)

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isTree(TreeNode* root,TreeNode* x)
    {
        if(root == nullptr)
            return false;
        if(root == x)
            return true;
        return isTree(root->left,x)
        || isTree(root->right,x);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == p||root==q)
       		return root;
        bool pInLeft = isTree(root->left,p);//不在左边就在右边
        bool pInRight = !pInLeft;//直接复用
        
        bool pInLeft = isTree(root->left,q);//不在左边就在右边
        bool pInRight = !pInLeft;//直接复用
        
        //一个在左一个在右
        if((pInLeft&&qInRight)||(qInLeft&&pInRight))
            return root;
        //都在左
        if(pInLeft && qInLeft)
            return lowestCommonAncestor(root->left,p,q);
        //都在右
        if(pInRight && qInRight)
            return lowestCommonAncestor(root->right,p,q);
        
        return nullptr;
    }
};
```

第二种解法：

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool FindPath(TreeNode* root,TreeNode* x,stack<TreeNode*>& path)
    {
        if(root == nullptr)
            return false;
        path.push(root);
        if(root == x)
            return true;
        if(FindPath(root->left,x,path))
   		   return true;
        if(FindPath(root->right,x,path))
   		   return true;
        //没找到pop掉，然后返回给上一层false
        path.pop();
        return false;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> pPath,qPath;
        FindPath(root,p,pPath);
        FindPath(root,q,qPath);
        //类似找相交节点就是公共祖先
        while(pPath.size()!=qPath.size())
        {
            if(pPath.size()>qPath.size())
                pPath.pop();
            else
                qPath.pop();
        }
        while(pPath.top()!=qPath.top())
        {
            pPath.pop();
            qPath.pop();
        }
        
        //当top相等时返回谁都是一样的
        return pPath.top();
    }
};
```



[[NOIP2010\]数字统计_牛客题霸_牛客网 (nowcoder.com)](https://www.nowcoder.com/practice/179d9754eeaf48a1b9a49dc1d438525a?tpId=290&tqId=39941&ru=/exam/oj)

![image-20240419112315701](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240419112315701.png)

解法：枚举+数字拆分

```C++
#include <iostream>
using namespace std;

int main() {
   int l,r;
   cin>>l>>r;
    int ret = 0;
    for(int i = l,i<=r;++i)
    {
        int tmp = i;
        while(tmp)
        {
            if(tmp&10==2)ret++;
            tmp/=10;
        }
    }
    cout<<ret<<endl;
}

```

[两个数组的交集_牛客题霸_牛客网 (nowcoder.com)](https://www.nowcoder.com/practice/56ea71d1f4e94de2aaec10e985874cce?tpId=196&tqId=40269&ru=/exam/oj)

![image-20240419113245507](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240419113245507.png)

解法：哈希---直接用容器较难

建议使用数组模拟哈希 bool hash[1010]

![image-20240419114159246](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240419114159246.png)

```C++
class Solution {
    bool hashp[1010] = {0};//牛客内部不初始化就是随机值，leetcode是0
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums1 int整型vector 
     * @param nums2 int整型vector 
     * @return int整型vector
     */
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // write code here
        vector<int> ret;
        for(auto i:nums1)
        {
            hash[i] = true;
        }
        for(auto i:nums2)
        {
            if(hash[i])//如果在哈希表中
            {
                ret.push_back(i);//push进去ret数组
                hash[x] = false;
            }
        }
        return ret;
    }
};
```

[点击消除_牛客题霸_牛客网 (nowcoder.com)](https://www.nowcoder.com/practice/8d3643ec29654cf8908b5cf3a0479fd5)

![image-20240419114809181](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240419114809181.png)

类似于括号匹配题

解法：栈---注意：放到栈中再pop出来是一个逆序过来的

细节:用可变长的数组，来模拟栈结构

```c++
#include <iostream>
using namespace std;

int main() {
    
}
// 64 位输出请用 printf("%lld")
```

[二叉搜索树与双向链表_牛客题霸_牛客网 (nowcoder.com)](https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5?tpId=13&tqId=11179&ru=/exam/oj)

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。如下图所示

![img](https://uploadfiles.nowcoder.com/images/20210605/557336_1622886924427/E1F1270919D292C9F48F51975FD07CE2)

数据范围：输入二叉树的节点数 0≤𝑛≤10000≤*n*≤1000，二叉树中每个节点的值 0≤𝑣𝑎𝑙≤10000≤*v**a**l*≤1000
要求：空间复杂度𝑂(1)*O*(1)（即在原树上操作），时间复杂度 𝑂(𝑛)*O*(*n*)

注意:

1.要求不能创建任何新的结点，只能调整树中结点指针的指向。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继
2.返回链表中的第一个节点的指针
3.函数返回的TreeNode，有左右指针，其实可以看成一个双向链表的数据结构

4.你不用输出双向链表，程序会根据你的返回值自动打印输出

### 输入描述：

二叉树的根节点

### 返回值描述：

双向链表的其中一个头节点。

## 示例1

输入：

```
{10,6,14,4,8,12,16}
```

复制

返回值：

```
From left to right are:4,6,8,10,12,14,16;From right to left are:16,14,12,10,8,6,4;
```

复制

说明：

```
输入题面图中二叉树，输出的时候将双向链表的头节点返回即可。     
```

## 示例2

输入：

```
{5,4,#,3,#,2,#,1}
```

复制

返回值：

```
From left to right are:1,2,3,4,5;From right to left are:5,4,3,2,1;
```

复制

说明：

```
                    5
                  /
                4
              /
            3
          /
        2
      /
    1
树的形状如上图
```

```C++
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
					//prev 必须给引用，链接是在前一位处理
					//引用的是指针变量，只不过指针的值初始为null
	void InOrderConvert(TreeNode* cur,TreeNode*& prev)
	{
		if(cur == nullptr)
			return;
		InOrderConvert(cur->left, prev);
		//中序
		//当前点的左指向前一个
		cur->left = prev;
		if(prev)
			prev->right = cur;//前一个节点的右指向当前点
			
		prev = cur;
		
		InOrderConvert(cur->right, prev);
	}
    TreeNode* Convert(TreeNode* pRootOfTree) {
        TreeNode* cur = pRootOfTree,*prev = nullptr;
		InOrderConvert(cur, prev);

		TreeNode* head = pRootOfTree;
		while(head && head->left)
		{
			head=head->left;
		}
		return head;
    }
};

```

[105. 从前序与中序遍历序列构造二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/)

给定两个整数数组 `preorder` 和 `inorder` ，其中 `preorder` 是二叉树的**先序遍历**， `inorder` 是同一棵树的**中序遍历**，请构造二叉树并返回其根节点。

**示例 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/tree.jpg)

```
输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
```

**示例 2:**

```
输入: preorder = [-1], inorder = [-1]
输出: [-1]
```

**提示:**

- `1 <= preorder.length <= 3000`
- `inorder.length == preorder.length`
- `-3000 <= preorder[i], inorder[i] <= 3000`
- `preorder` 和 `inorder` 均 **无重复** 元素
- `inorder` 均出现在 `preorder`
- `preorder` **保证** 为二叉树的前序遍历序列
- `inorder` **保证** 为二叉树的中序遍历序列

思路：先确定根，分割左右子树中序区间

本质---前序确定根，中序确定左右子树 

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
TreeNode* _build(vector<int>& preorder,vector<int>& inorder,int& previ,int inbegin,int inend)
    {
        if(inbegin>inend)
            return nullptr;
    //寻找根的位置
        int rooti = inbegin;
        while(rooti <= inend)
        {
            if(preorder[previ]==inorder[rooti])
            {
                break;
            }
            ++rooti;
        }
        //前序确定根
        TreeNode* root = new TreeNode(preorder[previ++]);
        //[inbegin,rooti-1] rooti [rooti+1,inend]
        //中序分割确定左右子树
        root->left =_build(preorder,inorder,previ,inbegin,rooti-1);
        root->right = _build(preorder,inorder,previ,rooti+1,inend);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int i = 0;
        TreeNode* root = _build(preorder,inorder,i,0,inorder.size()-1);
        return root;
    }
};
```

[106. 从中序与后序遍历序列构造二叉树 - 力扣（LeetCode）](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/)

给定两个整数数组 `inorder` 和 `postorder` ，其中 `inorder` 是二叉树的中序遍历， `postorder` 是同一棵树的后序遍历，请你构造并返回这颗 *二叉树* 。

**示例 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/tree.jpg)

```
输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
输出：[3,9,20,null,null,15,7]
```

**示例 2:**

```
输入：inorder = [-1], postorder = [-1]
输出：[-1]
```

**提示:**

- `1 <= inorder.length <= 3000`
- `postorder.length == inorder.length`
- `-3000 <= inorder[i], postorder[i] <= 3000`
- `inorder` 和 `postorder` 都由 **不同** 的值组成
- `postorder` 中每一个值都在 `inorder` 中
- `inorder` **保证**是树的中序遍历
- `postorder` **保证**是树的后序遍历

```C++

```

[144. 二叉树的前序遍历 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-preorder-traversal/description/)

给你二叉树的根节点 `root` ，返回它节点值的 **前序** 遍历。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_1.jpg)

```
输入：root = [1,null,2,3]
输出：[1,2,3]
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [1]
输出：[1]
```

**示例 4：**

![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_5.jpg)

```
输入：root = [1,2]
输出：[1,2]
```

**示例 5：**

![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_4.jpg)

```
输入：root = [1,null,2]
输出：[1,2]
```

**提示：**

- 树中节点数目在范围 `[0, 100]` 内
- `-100 <= Node.val <= 100`

**进阶：**递归算法很简单，你可以通过迭代算法完成吗？



```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> v;
        //左路节点
        //左路节点的右子树
        TreeNode* cur = _root;
        while(cur || !s.empty())
        {
            //先访问左路节点
            while(cur)
            {
                //左路节点访问且入栈					//栈里面的节点表示依次访问这些节点的右子树
                v.push_back(cur->val);
                s.push(cur);
                cur = cur->left;
            }
            //子问题方式访问左路节点的右子树
            TreeNode* top = s.top();
            s.pop();

            cur = top->right;
        }
        return v;
    }
};
```

![image-20240422202704565](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240422202704565.png)

[94. 二叉树的中序遍历 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-inorder-traversal/description/)

给定一个二叉树的根节点 `root` ，返回 *它的 **中序** 遍历* 。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_1.jpg)

```
输入：root = [1,null,2,3]
输出：[1,3,2]
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [1]
输出：[1]
```

**提示：**

- 树中节点数目在范围 `[0, 100]` 内
- `-100 <= Node.val <= 100`

**进阶:** 递归算法很简单，你可以通过迭代算法完成吗？

思路：

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> v;
                //左路节点
                //左路节点的右子树
                TreeNode* cur = root;
                while(cur || !s.empty())
                {
                    //先访问左路节点
                    while(cur)
                    {                        
                        s.push(cur);
                        cur = cur->left;
                    }
                    //子问题方式访问左路节点的右子树
                    TreeNode* top = s.top();
                    s.pop();
                    v.push_back(top->val);

                    cur = top->right;
                }
                return v;
    }
};
```

[145. 二叉树的后序遍历 - 力扣（LeetCode）](https://leetcode.cn/problems/binary-tree-postorder-traversal/description/)

给你一棵二叉树的根节点 `root` ，返回其节点值的 **后序遍历** 。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/08/28/pre1.jpg)

```
输入：root = [1,null,2,3]
输出：[3,2,1]
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [1]
输出：[1]
```

**提示：**

- 树中节点的数目在范围 `[0, 100]` 内
- `-100 <= Node.val <= 100`

**进阶：**递归算法很简单，你可以通过迭代算法完成吗？

后序：左子树，右子树，根

从栈中取到节点就代表访问完了

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* cur = root;
        stack<TreeNode*> s;
        vector<int> v;
        TreeNode* prev =nullptr;
        while(cur||!s.empty())
        {
            while(cur)
            {
                s.push(cur);
                cur=cur->left;
            }
            TreeNode* top = s.top();
            //top节点的右为空 或者上一个访问节点等于它的右孩子
            //那么说明(空)不用访问或者(不为空)右子树已经访问过了
            if(top->right == nullptr || top->right == prev)
            {
                s.pop();
                v.push_back(top->val);
                prev = top;
            }
            else
            {
                //右子树不为空，且没有访问，子问题访问右子树
                cur=top->right;
            }
        }
        return v;
    }
};
```

