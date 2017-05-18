//用数组实现循环队列
#ifndef _QUEUE_H
#define _QUEUE_H

template<class T>
class Queue
{
public:
    Queue( int capacity, int front, int rear, int size, T* array ) :
        capacity(capacity), front(front), rear(rear), size(size), array(array) {}//构造函数
    bool IsEmpty();
    bool IsFull();
    int Succ( int Value );//实现循环
    void EnQueue(T x );
    T DeQueue();
    T GetFront() const;
    T GetRear() const;
private:
    int capacity;//数组容量
    int front;
    int rear;
    int size;//队列大小
    T* array;
};

#endif
