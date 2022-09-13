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
class Queue
{
public:
    Queue();
    Queue(T source[], int begin, int end);
    Queue(const Queue<T> &source);
    ~Queue();
    // 属性查询
    bool Empty() const { return size_ == 0; }
    int Size() const { return size_; }
    // 查
    T &Front() const;
    T &Back() const;
    // 增
    Queue<T> &Push(const T &data);
    // 删
    Queue<T> &Pop();
    Queue<T> &Clear();
    // 改
    Queue<T> &Append(Queue<T> &other);

private:
    Node<T> *front_, *rear_;
    int size_;
};

template <class T>
Queue<T>::Queue()
{
    front_ = rear_ = nullptr;
    size_ = 0;
}

template <class T>
Queue<T>::Queue(T source[], int begin, int end)
{
    size_ = end - begin;
    if (size_)
    {
        Node<T> *new_node = nullptr;

        front_ = rear_ = new Node<T>(source[begin]);
        for (int i = begin + 1; i < end; i++)
        {
            new_node = new Node<T>(source[i]);
            rear_->next = new_node;
            rear_ = rear_->next;
        }
    }
    else
        front_ = rear_ = nullptr;
}

template <class T>
Queue<T>::Queue(const Queue<T> &source)
{
    size_ = source.size_;
    if (size_)
    {
        Node<T> *new_node = nullptr;
        Node<T> *source_node = source.front_;

        front_ = rear_ = new Node<T>(source_node->data);
        source_node = source_node->next;

        while (source_node)
        {
            new_node = new Node<T>(source_node->data);
            rear_->next = new_node;
            rear_ = rear_->next;
            source_node = source_node->next;
        }
    }
    else
        front_ = rear_ = nullptr;
}

template <class T>
Queue<T>::~Queue()
{
    Clear();
}

template <class T>
T &Queue<T>::Front() const
{
    if (size_ == 0)
        throw OutOfRange();

    return front_->data;
}

template <class T>
T &Queue<T>::Back() const
{
    if (size_ == 0)
        throw OutOfRange();

    return rear_->data;
}

template <class T>
Queue<T> &Queue<T>::Push(const T &data)
{
    Node<T> *p = new Node<T>(data);
    if (size_)
    {
        rear_->next = p;
        rear_ = rear_->next;
    }
    else
    {
        front_ = rear_ = p;
    }
    size_++;
    return *this;
}

template <class T>
Queue<T> &Queue<T>::Pop()
{
    if (size_ == 0)
        throw OutOfRange();

    Node<T> *old_node = front_;
    front_ = front_->next;
    if (size_ == 1)
        rear_ = nullptr;
    delete old_node;
    size_--;
    return *this;
}

template <class T>
Queue<T> &Queue<T>::Clear()
{
    Node<T> *old_node = nullptr;
    while (front_)
    {
        old_node = front_;
        front_ = front_->next;
        delete old_node;
    }
    rear_ = nullptr;
    size_ = 0;
    return *this;
}

template <class T>
Queue<T> &Queue<T>::Append(Queue<T> &other)
{
    if (this == &other)
        return *this;
    if (other.size_ == 0)
    {
        return *this;
    }
    else if (size_ == 0)
    {
        front_ = other.front_;
        rear_ = other.rear_;
        size_ = other.size_;

        other.front_ = other.rear_ = nullptr;
        other.size_ = 0;

        return *this;
    }
    
    rear_->next=other.front_;
    rear_=other.rear_;
    size_+=other.size_;

    other.front_ = other.rear_ = nullptr;
    other.size_ = 0;
    return *this;
}

int main(){
    int a[]={1,2,3,4,5};
    Queue<int> test(a,0,5);
    Queue<int> test2(test);
    test.Append(test2);
    while(!test.Empty()){
        cout<<test.Front()<<endl;
        test.Pop();
    }
    return 0;
}