#include <iostream>
using namespace std;
// 仅做表示，未实现
class OutOfRange
{
public:
    OutOfRange() {}
    OutOfRange(int index, int size) {}
};

template <class T>
struct Node
{
    T data;
    Node<T> *next;

    Node(T data = 0, Node<T> *next = nullptr)
        : data(data), next(next) {}
    bool operator>(Node<T> right) const { return data > right.data; }
    bool operator<(Node<T> right) const { return data < right.data; }
    bool operator==(Node<T> right) const { return data == right.data; }
    bool operator>=(Node<T> right) const { return data >= right.data; }
    bool operator<=(Node<T> right) const { return data <= right.data; }
    bool operator!=(Node<T> right) const { return data != right.data; }
};

template <class T>
class Stack
{
public:
    Stack();
    Stack(T source[], int begin, int end);
    Stack(const Stack<T> &source);
    ~Stack();
    // 属性查询
    bool Empty() const { return size_ == 0; }
    int Size() const { return size_; }
    // 查
    T &Top() const;
    // 增
    Stack<T> &Push(const T &data);
    // 删
    Stack<T> &Pop();
    Stack<T> &Clear();

private:
    Node<T> *top_;
    int size_;
};

template <class T>
Stack<T>::Stack()
{
    top_ = nullptr;
    size_ = 0;
}

template <class T>
Stack<T>::Stack(T source[], int begin, int end)
{
    size_ = end - begin;
    if (size_)
    {
        Node<T> *new_node = nullptr;

        top_ = new Node<T>(source[begin]);
        for (int i = begin + 1; i < end; i++)
        {
            new_node = new Node<T>(source[i]);
            new_node->next = top_;
            top_ = new_node;
        }
    }
    else
        top_ = nullptr;
}

template <class T>
Stack<T>::Stack(const Stack<T> &source)
{
    size_ = source.size_;
    if (size_)
    {
        Node<T> *bottom_node = nullptr, *new_node = nullptr;
        Node<T> *source_node = source.top_;

        top_ = bottom_node = new Node<T>(source_node->data);
        source_node = source_node->next;

        while (source_node)
        {
            new_node = new Node<T>(source_node->data);
            bottom_node->next = new_node;
            bottom_node = bottom_node->next;
            source_node = source_node->next;
        }
    }
    else
        top_ = nullptr;
}

template <class T>
Stack<T>::~Stack()
{
    Clear();
}

template <class T>
T &Stack<T>::Top() const
{
    if (size_ == 0)
        throw OutOfRange();

    return top_->data;
}

template <class T>
Stack<T> &Stack<T>::Push(const T &data)
{
    Node<T> *p = new Node<T>(data);
    if (size_)
    {
        p->next = top_;
        top_ = p;
    }
    else
    {
        top_ = p;
    }
    size_++;
    return *this;
}

template <class T>
Stack<T> &Stack<T>::Pop()
{
    if (size_ == 0)
        throw OutOfRange();

    Node<T> *old_node = top_;
    top_ = top_->next;
    delete old_node;
    size_--;
    return *this;
}

template <class T>
Stack<T> &Stack<T>::Clear()
{
    Node<T> *old_node = nullptr;
    while (top_)
    {
        old_node = top_;
        top_ = top_->next;
        delete old_node;
    }
    size_ = 0;
    return *this;
}

int main()
{
    int a[]={1,2,3,4,5};
    Stack<int> test(a,0,5);
    Stack<int> test2(test);
    while(!test2.Empty()){
        cout<<test2.Top()<<endl;
        test2.Pop();
    }
    return 0;
}