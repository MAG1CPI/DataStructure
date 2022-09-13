# DataStructure

实现基本数据结构及其基本操作

## list

* 构造函数：
    * 无参构造函数：创建一个空链表
    * 有参构造函数：根据所给数组/链表创建一个具有相同元素的链表
* 析构函数：直接调用clear()清空链表
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
    * `Merge(List &other)`：对已排序的两个链表合并
    * `Reverse()`：将链表反转
