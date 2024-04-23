[TOC]

# **Map and Set**

序列式容器 vector/list/deque , 单纯的存储数据

关联式容器 map/set/....,不是单纯的存储数据

# **Pair基础**

![image-20240423170202702](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240423170202702.png)

在C++中，`std::pair`是一个模板类，用于表示一对值，通常用在容器的返回类型中，如`std::map`的`equal_range`函数，或者在算法的返回值中，如`std::minmax_element`。`std::pair`可以存储两种不同类型的数据，分别称为`first`和`second`。

如果类型相同，可以是构造 or 拷贝构造

### 定义

```cpp
template<class T1, class T2> 
struct pair {
    typedef T1 first_type; // 第一个元素的类型
    typedef T2 second_type; // 第二个元素的类型

    first_type first; // 第一个元素
    second_type second; // 第二个元素

    // 构造函数
    constexpr pair(const T1& x, const T2& y) : first(x), second(y) {}

    // 其他成员函数...
};
```

### 关键特性

1. **模板类**：`std::pair`是模板化的，可以存储任意类型的两个值。
2. **两个成员变量**：`first`和`second`分别存储第一个和第二个值。
3. **默认构造函数**：可以创建一个`pair`的默认实例，其`first`和`second`都是它们各自类型的默认实例。
4. **拷贝构造函数**：可以创建一个`pair`的拷贝。
5. **赋值操作符**：可以为`pair`赋值另一个`pair`的值。

### 使用场景

- **容器的返回类型**：如`std::map`和`std::multimap`的`equal_range`函数返回`std::pair`，包含上界和下界迭代器。
- **算法的返回类型**：如`std::minmax_element`函数返回一个`pair`，包含指向最小元素和最大元素的迭代器。
- **存储两个相关值**：当需要将两个相关的值组合为一个单元时。

### 成员函数

- **构造函数**：创建一个包含两个元素的`pair`。
- **赋值操作符**：将一个`pair`的值赋给另一个`pair`。

### 示例代码

```cpp
#include <iostream>
#include <utility> // 包含 std::pair

int main() {
    std::pair<int, std::string> p(1, "one");

    // 访问pair的成员
    std::cout << "First element: " << p.first << std::endl;
    std::cout << "Second element: " << p.second << std::endl;

    // 修改pair的成员
    p.first = 2;
    p.second = "two";

    // 使用make_pair函数创建pair
    std::pair<int, std::string> p2 = std::make_pair(3, "three");

    // 使用tie函数创建pair（或tuple）
    auto p3 = std::make_pair(4, "four");

    return 0;
}
```

输出结果：

```
First element: 1
Second element: one
```

在这个示例中，我们创建了一个`std::pair`实例，包含一个整数和一个字符串。我们访问并修改了`pair`的成员，然后使用`std::make_pair`函数创建了另一个`pair`实例。

`std::pair`是C++中处理成对数据的一个非常有用的工具，它简单而灵活，可以适应多种不同的使用场景。

![image-20240423172514777](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240423172514777.png)

## **make_pair(直接构造pair)**

在C++中，`std::make_pair`是一个模板函数，用于方便地创建`std::pair`对象。这个函数特别有用，因为它允许你通过两个参数直接构造一个`pair`，而不必显式地调用`pair`的构造函数。

### 函数原型

```cpp
template<class T1, class T2> 
pair<T1, T2> make_pair(T1&& t, T2&& u);
```

### 参数

- `t`：第一个元素的值或引用，可以是任意类型。
- `u`：第二个元素的值或引用，可以是任意类型。

### 返回值

返回一个`std::pair`对象，其`first`成员是`t`的值，`second`成员是`u`的值。

### 使用场景

- 当你需要快速创建一个包含两个元素的`pair`时。
- 在多参数函数中，返回两个或多个相关值时。

### 示例代码

```cpp
#include <iostream>
#include <utility> // 包含 std::pair 和 std::make_pair

int main() {
    // 使用 make_pair 创建 pair
    auto p = std::make_pair(1, "one");

    // 访问 pair 的成员
    std::cout << "First element: " << p.first << std::endl;
    std::cout << "Second element: " << p.second << std::endl;

    // make_pair 也支持通用引用（右值引用）
    int a = 2;
    int b = 3;
    auto p2 = std::make_pair(a, b);

    // 创建包含右值的 pair
    auto p3 = std::make_pair(4, std::string("four"));

    return 0;
}
```

输出结果：

```
First element: 1
Second element: one
```

在这个示例中，我们使用`std::make_pair`创建了几个不同的`std::pair`实例。第一个`pair`包含一个整数和一个字符串字面量。第二个`pair`包含两个整数变量的引用。第三个`pair`包含一个整数和一个通过`std::string`构造函数创建的字符串对象。

`std::make_pair`是C++中一个非常实用的函数模板，它简化了`pair`对象的创建过程，特别是在需要构造包含两个不同类型元素的`pair`时。

# **Set 部分**

set原用法（排序+去重）查找在不在

拷贝和析构，代价不小

![image-20240423100451003](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240423100451003.png)

Key搜索模型（二叉搜索树）的容器，判断在不在

- 会自动排序,走升序
- 中序遍历
- 底层是一个红黑树
- 当有相同值不插入（底层会返回false）

SGI-STL中关于键值对的定义

- ![image-20240423101527458](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240423101527458.png)

![image-20240423101435628](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240423101435628.png)

![image-20240423101557400](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240423101557400.png)

**pair是一个类，可以接受布尔值，拥有两个成员遍历，一个first 一个second**

## **set基础**

在C++中，`std::set` 是一个关联容器，它存储的元素是唯一的，并且是按照元素的值进行升序排列的。`std::set` 通常是基于平衡二叉搜索树（如红黑树）实现的，这使得它能够提供高效的查找、插入和删除操作。

以下是 `std::set` 的一些关键特性和操作：

### 关键特性

1. **唯一性**：容器中的每个元素都是唯一的。
2. **排序**：元素自动按照关键字的顺序排列，可以提供自定义的比较函数。
3. **时间复杂度**：查找、插入和删除操作通常都是 O(log n)，其中 n 是容器中元素的数量。

### 构造与初始化

```cpp
std::set<int> mySet; // 默认构造
std::set<int> mySet = {1, 2, 3}; // 初始化列表构造
```

### 插入元素

```cpp
mySet.insert(4); // 插入一个元素
```

### 删除元素

```cpp
mySet.erase(2); // 删除特定元素
mySet.erase(mySet.begin()); // 删除迭代器指向的元素
mySet.clear(); // 删除所有元素
```

### 查找元素

```cpp
auto it = mySet.find(3); // 查找特定元素
if (it != mySet.end()) {
    // 元素找到
} else {
    // 元素未找到
}
```

### 遍历元素

```cpp
for (int num : mySet) {
    std::cout << num << " ";
}
```

### 获取元素数量

```cpp
size_t count = mySet.size(); // 获取元素数量
```

### 检查元素是否存在

```cpp
bool exists = (mySet.count(3) > 0); // 检查元素是否存在
```

### 示例代码

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> mySet = {1, 2, 3, 3}; // 重复的元素3只会被存储一次

    // 插入新元素
    mySet.insert(4);

    // 查找元素
    auto it = mySet.find(3);
    if (it != mySet.end()) {
        std::cout << "Found: " << *it << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    // 删除元素
    mySet.erase(3);

    // 遍历并打印所有元素
    for (int num : mySet) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果：

```
Found: 3
1 2 4 
```

`std::set` 是C++标准模板库中非常有用的容器之一，它在需要保持唯一性且有序的元素集合时提供了高效的操作。

## **equal_range()**

在C++中，`std::set`的成员函数`equal_range`**用于查找给定值的所在范围**。这个函数返回一个`std::pair`，包含两个迭代器，分别指向与给定值相等的元素（如果存在）的上下界。如果找不到相等的元素，那么返回的下界迭代器将指向大于给定值的第一个元素。

### 函数原型

```cpp
std::pair<iterator, iterator> equal_range(const key_type& key);
```

### 参数

- `key`：要查找的元素的键。

### 返回值

返回一个`std::pair`，包含两个迭代器：
- 第一个迭代器指向等于给定键的元素（如果存在）。
- 第二个迭代器指向大于给定键的第一个元素。

### 时间复杂度

`equal_range`函数的时间复杂度为O(log n)，其中n是`std::set`中元素的数量。

### 使用场景

`equal_range`通常用于以下场景：

1. **查找一个范围内的元素**：可以找到等于某个键的所有元素的上下界。
2. **统计某个键的重复次数**：如果`std::set`中的元素是唯一的，那么`equal_range`的第一个和第二个迭代器之间的距离可以告诉你给定键的重复次数。

### 示例代码

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> mySet = {1, 2, 4, 4, 5, 7};

    auto range = mySet.equal_range(4);
    std::cout << "Elements equal to 4: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    range = mySet.equal_range(3);
    std::cout << "Elements equal to 3: ";
    if (range.first == range.second) {
        std::cout << "None" << std::endl;
    } else {
        for (auto it = range.first; it != range.second; ++it) {
            std::cout << *it << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果：

```
Elements equal to 4: 4 4 
Elements equal to 3: None
```

在这个例子中，我们首先查找值为4的元素的范围，然后查找值为3的元素的范围。由于3不在`std::set`中，`equal_range`返回的迭代器`range.first`和`range.second`相等，表示没有找到等于3的元素。

## **count()**

在C++中，`std::set`和`std::map`的`count`函数用于确定一个元素在容器中出现的次数。由于`std::set`保证元素是唯一的，`count`函数对于`std::set`来说总是返回0或1。

### 函数原型

```cpp
size_type count(const key_type& key) const;
```

### 参数

- `key`：要计数的元素的键。

### 返回值

返回一个`size_type`类型的值，表示给定键在容器中的出现次数。对于`std::set`，这个值将是0（如果元素不存在）或1（如果元素存在）。

### 时间复杂度

`count`函数的时间复杂度为O(log n)，其中n是`std::set`中元素的数量。

### 使用场景

`count`函数通常用于以下场景：

1. **检查元素是否存在**：通过检查`count`函数的返回值是否为1，可以快速判断一个元素是否存在于`std::set`中。
2. **统计唯一元素的数量**：由于`std::set`中的元素是唯一的，`count`函数可以用来统计容器中唯一元素的数量。

### 示例代码

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> mySet = {1, 2, 3, 4, 4, 5};

    int key = 4;
    if (mySet.count(key) == 1) {
        std::cout << "Element " << key << " exists in the set." << std::endl;
    } else {
        std::cout << "Element " << key << " does not exist in the set." << std::endl;
    }

    key = 6;
    if (mySet.count(key) == 1) {
        std::cout << "Element " << key << " exists in the set." << std::endl;
    } else {
        std::cout << "Element " << key << " does not exist in the set." << std::endl;
    }

    return 0;
}
```

输出结果：

```
Element 4 exists in the set.
Element 6 does not exist in the set.
```

在这个例子中，我们使用`count`函数检查元素4和6是否存在于`std::set`中。由于`std::set`中的元素是唯一的，对于元素4，`count`返回1，表示它存在于`std::set`中；而对于元素6，`count`返回0，表示它不存在于`std::set`中。



## **multiset()---multi 多个，许多**

排序，无去重，有相同值，在树内插入左右边都行

在C++标准模板库（STL）中，`std::multiset`是`std::set`的一个变体，它允许存储相同元素的多个副本。与`std::set`不同，`std::multiset`不保证元素的唯一性。以下是`std::multiset`的一些关键特性和使用情况：

### 关键特性

1. **元素唯一性**：与`std::set`不同，`std::multiset`允许容器中有重复的元素。
2. **排序**：`std::multiset`中的元素仍然会自动按照键值进行排序，排序方式可以根据提供的比较函数来确定。
3. **时间复杂度**：与`std::set`相同，查找、插入和删除操作的时间复杂度为O(log n)，其中n是容器中元素的数量。
4. **迭代器**：提供双向迭代器，可以用于遍历容器中的元素。

### 成员函数

`std::multiset`提供了与`std::set`相似的成员函数，包括：

- `insert`：插入元素。
- `erase`：删除元素。
- `find`：查找特定元素。
- `count`：返回特定元素在容器中出现的次数，对于`std::multiset`来说，这个数可以是多于1的。
- `equal_range`：返回一个范围，包含所有与给定值相等的元素。
- `clear`：清空容器中的所有元素。

### 使用场景

- 当你需要存储一个元素的多个副本时，使用`std::multiset`。
- 当元素的重复出现不会影响你的数据结构或算法时。

### 示例代码

```cpp
#include <iostream>
#include <set>

int main() {
    std::multiset<int> myMultiSet = {{1}, {2}, {3}, {3}, {4}};

    // 插入重复元素
    myMultiSet.insert(3);

    // 使用count函数，返回值为元素出现的次数
    std::cout << "Count of 3 in multiset: " << myMultiSet.count(3) << std::endl;

    // 使用equal_range查找元素3的所有副本
    auto range = myMultiSet.equal_range(3);
    std::cout << "Elements equal to 3: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果：

```
Count of 3 in multiset: 3
Elements equal to 3: 3 3 3 
```

在这个示例中，我们创建了一个`std::multiset`，并且插入了重复的元素3。使用`count`函数，我们得知元素3在`multiset`中出现了三次。使用`equal_range`函数，我们可以找到并打印出所有值为3的元素。

# **Map 部分**

## **Map基础**

![image-20240423165134290](C:\Users\XL\AppData\Roaming\Typora\typora-user-images\image-20240423165134290.png)

Map给的value_type 内的pair 不想key被修改，set是不允许修改

当你的数据类型是自定义类型的时候可以使用箭头指向

```C++
cout << it->first << ":" << (*it).second << endl;
cout << it.operator->()->first << ":" << it.operator->()->second << endl;
```



在C++中，`std::map`是一个关联容器，它存储键值对（key-value pairs），并且按照键的顺序进行排序。以下是`std::map`的一些关键特性和操作：

### 关键特性

1. **基于平衡二叉搜索树**：`std::map`通常是基于红黑树实现的，这保证了操作的效率。
2. **键的唯一性**：每个键在`map`中都是唯一的，不允许重复。
3. **自动排序**：`map`中的元素按照键的顺序自动排序，可以根据需要提供自定义比较函数。
4. **时间复杂度**：大多数操作（如查找、插入、删除）的时间复杂度为O(log n)，其中n是`map`中元素的数量。

### 构造与初始化

```cpp
std::map<int, std::string> myMap;
// 或者使用初始化列表
std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};
```

### 访问元素

- **通过下标**：使用`operator[]`可以访问或添加元素，如果键不存在，则会插入一个键值对。
- **通过迭代器**：使用`begin()`和`end()`迭代器可以遍历所有元素。

### 修改元素

- **插入元素**：使用`insert()`函数可以插入新的键值对。
- **修改元素**：通过下标操作符`[]`可以修改已存在的键对应的值。
- **删除元素**：使用`erase()`函数可以删除一个或多个元素。

### 查找元素

- **find**：通过键查找元素，返回一个迭代器指向找到的元素，如果未找到则返回`end()`。
- **count**：返回键在`map`中出现的次数，由于键的唯一性，返回值总是0或1。

### 示例代码

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap;

    // 插入元素
    myMap.insert({3, "three"});
    myMap[4] = "four"; // 使用下标操作符

    // 修改元素
    myMap[3] = "three updated";

    // 删除元素
    myMap.erase(4);

    // 查找元素
    auto it = myMap.find(3);
    if (it != myMap.end()) {
        std::cout << it->second << std::endl; // 输出 "three updated"
    }

    // 遍历map
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
```

输出结果：

```
three updated
3: three updated
```

`std::map`是C++中处理有序键值对数据的一个非常有用的容器，它在需要保持数据有序性时提供了高效的操作。

## **operator[]**

在C++的`std::map`容器中，`operator[]`是一个关键的成员函数，它用于访问或修改与特定键关联的元素。这个操作符重载了下标运算符，使得`std::map`的使用类似于数组。

### 函数原型

```cpp
mapped_type& operator[](const key_type& key);
mapped_type& operator[](key_type&& key);
```

### 参数

- `key`：要访问的键的值。可以是键类型的一个对象（`const key_type&`），或者是一个右值引用（`key_type&&`），这允许使用临时对象或避免不必要的拷贝。

### 返回值

`operator[]`返回与给定键关联的元素的引用。返回的类型是`mapped_type&`，即`std::map`中存储的值的类型对应的引用。

### 行为

1. **如果键存在**：如果`map`中已经存在一个与所查询键相等的元素，`operator[]`返回该元素值的引用，允许你直接修改它。

2. **如果键不存在**：如果`map`中不存在与所查询键相等的元素，`operator[]`将插入一个新的键/值对。键是传递给`operator[]`的键，而值是使用值类型的默认构造函数创建的默认值。

3. **复杂度**：`operator[]`的平摊时间复杂度是常数，但最坏情况下，如果需要重新平衡树，可能会退化到O(log n)。

### 示例代码

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap;

    // 使用 operator[] 访问或创建元素
    myMap[1] = "one"; // 插入键1和值 "one"
    myMap[2] = "two"; // 插入键2和值 "two"

    // 修改已存在的元素
    myMap[1] = "ONE"; // 修改键1对应的值

    // 访问元素
    std::cout << myMap[2] << std::endl; // 输出 "two"

    return 0;
}
```

### 注意事项

- 使用`operator[]`时，如果键不存在于`map`中，插入操作不会改变`map`中原有的元素。
- 如果使用`operator[]`的键参数是一个临时对象，那么重载的接受右值引用的版本将被调用，这可以提高性能，因为它避免了不必要的拷贝。
- 在多线程环境中，使用`operator[]`需要小心，因为它可能会插入新元素。如果多个线程尝试插入相同键的不同值，可能会导致未定义行为。

`operator[]`是`std::map`中用于便捷访问和修改元素的重要工具，它使得对映射的元素进行赋值和初始化变得非常简单。

### 板书绘制：

![](C:\Users\XL\Pictures\Saved Pictures\map_operator[]解释板书.png)

## **Insert()**

无论成功还是失败都会返回一个迭代器和布尔值

返回-->

-->如果插入成功 pair<新插入key所在节点的iterator,true>

-->如果插入失败 pair<已经存在的key所在节点的iterator,false>

在C++中，`std::map`的`insert()`成员函数用于向映射中添加元素。`std::map`保持键的唯一性，并且按照键的顺序对元素进行排序。以下是`insert()`函数的详细说明：

### 函数原型

对于`std::map`，`insert()`有两个主要的重载版本：

1. 通过键值对（`std::pair`）进行插入：
   ```cpp
   std::pair<iterator, bool> insert(const value_type& value);
   ```

2. 通过迭代器范围进行范围插入（通常与标准库算法一起使用）：
   ```cpp
   template<class InputIt>
   void insert(InputIt first, InputIt last);
   ```

### 参数

1. `value`：要插入的键值对，类型为`value_type`，对于`std::map`，`value_type`通常是`std::pair<const Key, T>`。

2. `first` 和 `last`：两个迭代器，表示要插入的元素范围。

### 返回值

对于单个元素的插入，`insert()`返回一个`std::pair`，包含：
- `iterator`：指向新插入元素的迭代器。
- `bool`：一个布尔值，如果插入导致容器中增加了一个新的键/值对，则为`true`；如果键已存在，插入操作不会插入新元素，布尔值将为`false`。

### 行为

- 如果插入的键已经存在于`map`中，那么`insert()`不会执行任何操作（不插入重复的键），返回的迭代器指向原有的元素，布尔标志为`false`。
- 如果键不存在于`map`中，`insert()`将插入一个新的键值对，返回的迭代器指向新插入的元素，布尔标志为`true`。

### 示例代码

#### 单个元素插入

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap;
    
    // 插入一个元素
    auto result = myMap.insert(std::make_pair(1, "one"));
    if (result.second) {
        std::cout << "Element inserted." << std::endl;
    } else {
        std::cout << "Element not inserted, key already exists." << std::endl;
    }
    
    // 尝试插入一个已存在的键
    result = myMap.insert(std::make_pair(1, "un"));
    if (result.second) {
        std::cout << "Element inserted." << std::endl;
    } else {
        std::cout << "Element not inserted, key already exists." << std::endl;
    }
    
    return 0;
}
```

#### 范围插入

```cpp
#include <iostream>
#include <map>
#include <vector>

int main() {
    std::map<int, std::string> myMap;
    std::vector<std::pair<int, std::string>> data = {{1, "one"}, {2, "two"}, {3, "three"}};
    
    // 范围插入
    myMap.insert(data.begin(), data.end());
    
    // 打印map中的所有元素
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    return 0;
}
```

`insert()`函数是`std::map`中用于添加新元素的主要方法，它保持了键的唯一性，并且能够高效地处理插入操作。

## **multimap()**

**---不支持map版本的operator[]**

如果有多个key的时候，[]该返回谁？无法返回

在C++标准模板库（STL）中，`std::multimap`是一种关联容器，类似于`std::map`，但与`std::map`不同的是，它允许多个元素具有相同的键。`std::multimap`中的元素是成对的键值（`key-value`）对，其中键不需要是唯一的，而`std::map`要求每个键都是唯一的。

以下是`std::multimap`的一些关键特性：

### 关键特性

1. **键的唯一性**：与`std::map`不同，`std::multimap`允许具有相同键的多个元素存在。
2. **排序**：`std::multimap`中的元素按照键的顺序自动排序，也可以提供自定义的比较函数。
3. **时间复杂度**：查找、插入和删除操作的时间复杂度通常为O(log n)，其中n是容器中元素的数量。

### 构造与初始化

```cpp
std::multimap<int, std::string> myMultimap;
// 或者使用初始化列表
std::multimap<int, std::string> myMultimap = {{1, "one"}, {1, "uno"}};
```

### 插入元素

```cpp
myMultimap.insert({2, "two"});
myMultimap.insert(std::make_pair(3, "three"));
```

### 删除元素

```cpp
myMultimap.erase(2); // 删除键为2的所有元素
auto it = myMultimap.find(3);
if (it != myMultimap.end()) {
    myMultimap.erase(it); // 删除键为3的一个元素
}
```

### 查找元素

```cpp
auto range = myMultimap.equal_range(3); // 获取键为3的元素范围
for (auto it = range.first; it != range.second; ++it) {
    std::cout << it->second << " ";
}
```

### 遍历元素

```cpp
for (const auto& pair : myMultimap) {
    std::cout << pair.first << ": " << pair.second << std::endl;
}
```

### 示例代码

```cpp
#include <iostream>
#include <map>

int main() {
    std::multimap<int, std::string> myMultimap = {{1, "one"}, {1, "uno"}};

    // 插入具有相同键的新元素
    myMultimap.insert({1, "eins"});

    // 查找键为1的所有元素
    auto range = myMultimap.equal_range(1);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->second << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果：

```
one uno eins 
```

`std::multimap`适合于需要存储具有相同键的多个元素的情况。例如，在存储分类数据时，同一类别下可能有多个项目，这时就可以使用`std::multimap`。





## 在各类map，set容器中，为什么迭代器找不到指定内容就返回end（）？

在C++标准库中的容器（如`std::map`、`std::set`、`std::unordered_map`等）的查找操作通常返回一个迭代器。如果元素不存在，这些容器的查找操作（如`find`）会返回指向`end()`的迭代器。这里的`end()`指的是容器中最后一个元素的下一个位置，即容器的末尾。

选择返回`end()`而不是其他特殊值的原因包括：

1. **一致性**：返回`end()`提供了一种一致的方式来表示“未找到”的情况，使得用户可以通过检查迭代器是否等于`end()`来确定元素是否存在。

   ```cpp
   if (it != myContainer.end()) {
       // 元素存在，it指向该元素
   } else {
       // 元素不存在
   }
   ```

2. **效率**：对于基于平衡二叉搜索树的容器（如`std::map`和`std::set`），查找操作的时间复杂度为O(log n)。在未找到元素的情况下，返回`end()`迭代器不需要额外的时间来构造一个特殊的“未找到”标记，因为迭代器已经存在于容器的末尾。

3. **范围操作**：返回`end()`允许开发者直接使用迭代器范围来进行操作，例如，从开始到末尾的所有元素。

4. **避免特殊值**：不使用特殊的“未找到”值可以避免与容器中的有效值发生冲突。

5. **STL兼容性**：STL算法通常使用迭代器范围来操作，返回`end()`使得容器的查找操作与STL算法保持一致。

6. **语义清晰**：`end()`是一个清晰且明确的概念，表示容器中没有更多元素的迭代器位置。

7. **错误处理**：返回`end()`使得错误处理更加直观，因为开发者可以很容易地识别出查找失败的情况。

总的来说，返回`end()`是一种简单、高效且符合STL习惯的方式来表示查找操作未能找到元素的情况。