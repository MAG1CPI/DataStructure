# DataStructure

实现基本数据结构及其基本操作

## list

* 构造函数：
    * 无参构造函数：创建一个空链表
    * 有参构造函数：根据所给数组/链表创建一个具有相同元素的链表
* 析构函数：直接调用`clear()`清空链表
* 属性查询：
    * `Empty()`：判断链表是否为空
    * `Size()`：返回链表大小
    * 重载`[]`
* 查：
    * `Front()`：获得链表首个元素的引用
    * `Back()`：获得链表末尾元素的引用
    * `Find(int index)`：获得链表index位置的元素的引用
* 增：
    * `PushFront(const T &data)`：在链表开始添加一个元素
    * `PushBack(const T &data)`：在链表末尾添加一个元素
    * `Insert(int k, const T &data)`：在链表k位置处添加一个元素，k为添加后元素在链表中的位置
* 删：
    * `PopFront()`：删除链表首个元素
    * `PopBack()`：删除链表末尾元素
    * `Erase(int index)`：删除链表index位置的元素
    * `Remove(const T& val)`：删除链表中值为val的元素
    * `Unique()`：链表去重，只判断相邻元素是否相同
    * `Clear()`：清空链表
* 改：
    * `Sort()`：排序
    * `Merge(List &other)`：与另一个已排序的链表合并
    * `Reverse()`：将链表反转

## queue

* 构造函数：
    * 无参构造函数：创建一个空队列
    * 有参构造函数：根据所给数组/队列创建一个具有相同元素的队列（采用数组时即为依次向队列中添加元素）
* 析构函数：直接调用`clear()`清空队列
* 属性查询：
    * `Empty()`：判断队列是否为空
    * `Size()`：返回队列大小
* 查：
    * `Front()`：获得队列首个元素的引用
    * `Back()`：获得队列末尾元素的引用
* 增：
    * `Push(const T &data)`：在队尾添加一个元素
* 删：
    * `Pop()`：删除队首元素
    * `Clear()`：清空队列
* 改：
    * `Append(Queue<T> &other)`：在队尾添加另一个队列

## stack

* 构造函数：
    * 无参构造函数：创建一个空栈
    * 有参构造函数：根据所给数组/栈创建一个具有相同元素的栈（采用数组时即为依次向栈中添加元素）
* 析构函数：直接调用`clear()`清空栈
* 属性查询：
    * `Empty()`：判断栈是否为空
    * `Size()`：返回栈大小
* 查：
    * `Top()`：获得栈顶元素的引用
* 增：
    * `Push(const T &data)`：在栈顶添加一个元素
* 删：
    * `Pop()`：删除栈顶元素
    * `Clear()`：清空栈

