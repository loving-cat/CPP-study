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

