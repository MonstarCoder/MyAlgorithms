//ch03  顺序链表的实现
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

template <class T>
class Node
{
public:
    Node() { Next = nullptr; }
    T Data;
    Node* Next;
};

template<class T>
class LinkedList
{
public:
    LinkedList();//构造函数
    unsigned int Length();//链表元素个数
    void Add( T x );//表尾添加元素
    void Traversal();//遍历打印链表
    bool isEmpty();//判断是否为空表
    Node<T>* Find( T x );//查找元素
    void Delete( T x );//删除第一个值为x的节点
    void Insert( T x, Node<T>* p );//指定节点插入元素
private:
    unsigned int length;
    Node<T>* node;//临时节点
    Node<T>* lastnode;//头节点
    Node<T>* headnode;//尾节点
};

#endif


