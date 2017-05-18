#ifndef _STACK_H
#define _STACK_H

//定义节点
template<class T>
class Node
{
public:
    Node() { Next = nullptr; }//构造函数
    T Data;
    Node<T>* Next;
};

//声明链表
template<class T>
class Stack
{
public:
    Stack() { cnts = 0; head = new Node<T>; };
    ~Stack();
    bool IsEmpty();
    int Counts();
    void printStack();
    void Push( T x );
    T Top();
    T Pop();
private:
    int cnts;//入栈数量
    Node<T>* head;//栈的头部
};


#endif
