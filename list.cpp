#include <iostream>
#include <algorithm>
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
    Node<T> *prev, *next;

    Node(T data = 0, Node<T> *next = nullptr, Node<T> *prev = nullptr)
        : data(data), next(next), prev(prev) {}
    bool operator>(Node<T> right) const { return data > right.data; }
    bool operator<(Node<T> right) const { return data < right.data; }
    bool operator==(Node<T> right) const { return data == right.data; }
    bool operator>=(Node<T> right) const { return data >= right.data; }
    bool operator<=(Node<T> right) const { return data <= right.data; }
    bool operator!=(Node<T> right) const { return data != right.data; }
};

template <class T>
class List
{
private:
    Node<T> *Get(int index) const;

public:
    List();
    List(T source[], int begin, int end);
    List(const List &source);
    ~List();
    // 属性查询
    bool Empty() const { return size_ == 0; }
    int Size() const { return size_; }
    T &operator[](int index) const;
    // 查
    T &Front() const;
    T &Back() const;
    T &Find(int index) const;
    // 增
    List<T> &PushFront(const T &data);
    List<T> &PushBack(const T &data);
    List<T> &Insert(int k, const T &data);
    // 删
    List<T> &PopFront();
    List<T> &PopBack();
    List<T> &Erase(int index);
    List<T> &Remove(const T &val);
    List<T> &Unique();
    List<T> &Clear();
    // 改
    List<T> &Sort();
    List<T> &Merge(List &other);
    List<T> &Reverse();

    //转换
    T *ToArray() const;

private:
    Node<T> *front_, *rear_;
    int size_;
};

template <class T>
Node<T> *List<T>::Get(int index) const
{
    if (index < -size_ || index >= size_)
        throw OutOfRange(index, size_);
    Node<T> *p = nullptr;
    if (index >= 0)
    {
        p = front_;
        while (index)
        {
            p = p->next;
            index--;
        }
    }
    else
    {
        p = rear_;
        index++;
        while (index)
        {
            p = p->prev;
            index++;
        }
    }
    return p;
}

template <class T>
List<T>::List()
{
    front_ = rear_ = nullptr;
    size_ = 0;
}

template <class T>
List<T>::List(T source[], int begin, int end)
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
            new_node->prev = rear_;
            rear_ = rear_->next;
        }
    }
    else
        front_ = rear_ = nullptr;
}

template <class T>
List<T>::List(const List &source)
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
            new_node->prev = rear_;
            rear_ = rear_->next;
            source_node = source_node->next;
        }
    }
    else
        front_ = rear_ = nullptr;
}

template <class T>
List<T>::~List()
{
    Clear();
}

template <class T>
T &List<T>::operator[](int index) const
{
    return Get(index)->data;
}

template <class T>
T &List<T>::Front() const
{
    if (size_ == 0)
        throw OutOfRange();

    return front_->data;
}

template <class T>
T &List<T>::Back() const
{
    if (size_ == 0)
        throw OutOfRange();

    return rear_->data;
}

template <class T>
T &List<T>::Find(int index) const
{
    return Get(index)->data;
}

template <class T>
List<T> &List<T>::PushFront(const T &data)
{
    Node<T> *p = new Node<T>(data);
    if (size_)
    {
        front_->prev = p;
        p->next = front_;
        front_ = p;
    }
    else
    {
        front_ = rear_ = p;
    }
    size_++;
    return *this;
}

template <class T>
List<T> &List<T>::PushBack(const T &data)
{
    Node<T> *p = new Node<T>(data);
    if (size_)
    {
        rear_->next = p;
        p->prev = rear_;
        rear_ = p;
    }
    else
    {
        front_ = rear_ = p;
    }
    size_++;
    return *this;
}

template <class T>
List<T> &List<T>::Insert(int position, const T &data)
{
    if (position < -size_ - 1 || position > size_)
        throw OutOfRange(position, size_);

    Node<T> *new_node = new Node<T>(data);
    Node<T> *pos = nullptr;
    if (size_)
    {
        if (position == size_ || position == -1)
        {
            rear_->next = new_node;
            new_node->prev = rear_;
            rear_ = new_node;
            size_++;
            return *this;
        }
        else if (position == -size_ - 1 || position == 0)
        {
            front_->prev = new_node;
            new_node->next = front_;
            front_ = new_node;
            size_++;
            return *this;
        }
        else if (position > 0)
        {
            pos = front_->next;
            position -= 1;
            while (position)
            {
                pos = pos->next;
                position--;
            }
        }
        else
        {
            pos = rear_;
            position += 2;
            while (position)
            {
                pos = pos->prev;
                position++;
            }
        }
        new_node->next = pos;
        new_node->prev = pos->prev;
        new_node->next->prev = new_node;
        new_node->prev->next = new_node;
    }
    else
    {
        front_ = rear_ = new_node;
    }
    size_++;
    return *this;
}

template <class T>
List<T> &List<T>::PopFront()
{
    if (size_ == 0)
        throw OutOfRange();

    Node<T> *old_node = front_;
    front_ = front_->next;
    if (size_ > 1)
        front_->prev = nullptr;
    else
        rear_ = nullptr;
    delete old_node;
    size_--;
    return *this;
}

template <class T>
List<T> &List<T>::PopBack()
{
    if (size_ == 0)
        throw OutOfRange();

    Node<T> *old_node = rear_;
    rear_ = rear_->prev;
    if (size_ > 1)
        rear_->next = nullptr;
    else
        front_ = nullptr;
    delete old_node;
    size_--;
    return *this;
}

template <class T>
List<T> &List<T>::Erase(int index)
{
    Node<T> *old_node = Get(index);
    if (index == 0 || index == -size_)
    {
        front_ = front_->next;
        if (size_ > 1)
            front_->prev = nullptr;
        else
            rear_ = nullptr;
    }
    else if (index == size_ - 1 || index == -1)
    {
        rear_ = rear_->prev;
        if (size_ > 1)
            rear_->next = nullptr;
        else
            front_ = nullptr;
    }
    else
    {
        old_node->prev->next = old_node->next;
        old_node->next->prev = old_node->prev;
    }
    delete old_node;
    size_--;
    return *this;
}

template <class T>
List<T> &List<T>::Remove(const T &val)
{
    Node<T> *old_node = nullptr;
    //删除开始时相同
    while (front_ && front_->data == val)
    {
        old_node = front_;
        front_ = front_->next;
        delete old_node;
        size_--;
    }
    //删除后续相同
    if (size_)
    {
        front_->prev = nullptr;

        Node<T> *pos = front_->next;
        Node<T> *temp = nullptr;
        while (pos)
        {
            if (pos->data == val)
            {
                temp = pos->prev;
                do
                {
                    old_node = pos;
                    pos = pos->next;
                    delete old_node;
                    size_--;
                } while (pos && pos->data == val);
                temp->next = pos;
                if (pos)
                    pos->prev = temp;
                else
                    rear_ = temp;
            }
            else
                pos = pos->next;
        }
    }
    else
        rear_ = nullptr;
    return *this;
}

template <class T>
List<T> &List<T>::Unique()
{
    if (size_ == 0)
        return *this;
    T *val = &(front_->data);
    Node<T> *pos = front_->next;
    Node<T> *old_node = nullptr;
    Node<T> *temp = nullptr;
    while (pos)
    {
        if (pos->data == *val)
        {
            temp = pos->prev;
            do
            {
                old_node = pos;
                pos = pos->next;
                delete old_node;
                size_--;
            } while (pos && pos->data == *val);
            temp->next = pos;
            if (pos)
            {
                pos->prev = temp;
                val = &(pos->data);
                pos = pos->next;
            }
            else
                rear_ = temp;
        }
        else
        {
            val = &(pos->data);
            pos = pos->next;
        }
    }
    return *this;
}

template <class T>
List<T> &List<T>::Clear()
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
List<T> &List<T>::Sort()
{
    if (size_)
    {
        T *arr = ToArray();
        sort(arr, arr + size_);
        Node<T> *p = front_;
        do
        {
            p->data = *(arr++);
            p = p->next;
        } while (p);
        arr -= size_;
        delete[] arr;
    }

    return *this;
}

template <class T>
List<T> &List<T>::Merge(List &other)
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
    Node<T> *p = front_, *q = other.front_;
    if (p->data <= q->data)
    {
        p = p->next;
    }
    else
    {
        front_ = q;
        q = q->next;
    }
    Node<T> *temp_rear = front_;
    while (p && q)
    {
        if (p->data <= q->data)
        {
            temp_rear->next = p;
            p->prev = temp_rear;
            temp_rear = temp_rear->next;
            p = p->next;
        }
        else
        {
            temp_rear->next = q;
            q->prev = temp_rear;
            temp_rear = temp_rear->next;
            q = q->next;
        }
    }
    if (p)
    {
        temp_rear->next = p;
        p->prev = temp_rear;
    }
    else
    {
        temp_rear->next = q;
        q->prev = temp_rear;
        rear_ = other.rear_;
    }
    size_ += other.size_;
    other.front_ = other.rear_ = nullptr;
    other.size_ = 0;
    return *this;
}

template <class T>
List<T> &List<T>::Reverse()
{
    if (size_)
    {
        Node<T> *prev_node = rear_->prev;
        front_ = rear_;
        while (prev_node)
        {
            rear_->prev = rear_->next;
            rear_->next = prev_node;
            rear_ = rear_->next;
            prev_node = rear_->prev;
        }
        rear_->prev = rear_->next;
        rear_->next = nullptr;
    }
    return *this;
}

template <class T>
T *List<T>::ToArray() const
{
    if (size_ == 0)
        return nullptr;
    T *result = new T[size_];
    Node<T> *p = front_;
    while (p)
    {
        *(result++) = p->data;
        p = p->next;
    }
    return result - size_;
}

int main()
{
    int a[5] = {1, 5, 8, 4, 7};
    int b[5] = {9, 6, 3, 2, 0};
    List<int> test(a, 0, 5);
    List<int> test2(b, 0, 5);
    // test.PushBack(1).PushBack(1).PushBack(2).PushBack(1).PushBack(1).PushBack(3).PushBack(1).PushBack(1).PushBack(1).PushBack(4).PushBack(1).PushBack(1);
    // test.Unique();
    // test.Erase(2).Erase(-1).Erase(-2);
    // cout << test.Front() << " " << test.Back() << endl;
    test.Sort();
    test2.Sort();
    test.Merge(test2);
    test.Insert(0, -1).Insert(-1, -1).Insert(2, -1).Insert(-3, -1);
    for (int i = 0, n = test.Size(); i < n; i++)
    {
        cout << test[i] << endl;
    }
    return 0;
}