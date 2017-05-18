#include "LinkedList.h"
#include <iostream>

//构造函数
template<class T>
LinkedList<T>::LinkedList()
{
    node = nullptr;
    lastnode = nullptr;
    headnode = nullptr;
    length = 0;
}

//实现Add方法
template<class T>
void LinkedList<T>::Add(T x)
{
    node = new LinkedList<T>();//申请新节点
    node->Data = x;
    if ( lastnode == nullptr )
    {
        headnode = node;
        lastnode = node;
    }
    else
    {
        lastnode->Next = node;
        lastnode = node;
    }
    ++length;//元素个数加一
}

//实现traversal()函数
template<class T>
void LinkedList<T>::Traversal()
{
    node = headnode;//用临时节点指向头节点
    while ( node != nullptr )
    {
        std::cout << node->Data << std::endl;
        node = node->Next;
    }
    std::cout << std::endl;
}

//实现isEmpty()函数
template<class T>
bool LinkedList<T>::isEmpty()
{
    return length == 0;
}

//实现Find()函数
template<class T>
Node<T>* LinkedList<T>::Find(T x)
{
    node = headnode;
    while ( node != nullptr && node->Data != x )
    {
        node = node->Next;
    }
    return node;
}

//实现Delete()函数
template<class T>
void LinkedList<T>::Delete( T x )
{
    LinkedList<T>* temp = headnode;//申请一个临时节点指向头节点
    if ( temp == nullptr ) return;
    if ( temp->data == x )//如果头节点为要删除的元素，则删除头节点
    {
        headnode = temp->Next;
        if ( temp->Next == nullptr ) lastnode = nullptr;//如果链表只有一个节点，把尾节点置空
        delete( temp );
        return;
    }
    while ( temp ->Next != nullptr && temp->Next->Data != x )//遍历链表，找到第一个值与x相等的节点
    {
        temp = temp->Next;
    }
    if ( temp->Next == nullptr ) return;
    if (temp->Next = lastnode)
    {
        lastnode = temp;
        delete( temp->Next );
        temp->Next = nullptr;
    }
    else
    {
        node = temp->Next;
        temp->Next = node->Next;
        delete(node);
        node = nullptr;
    }
}

//实现Insert（）函数
template<class T>
void LinkedList<T>::Insert( T x, Node<T>* p )
{
    if ( p == nullptr ) return;
    node = new LinkedList<T>();
    node->Data = x;
    node->Next = p->Next;
    p->Next = node;
    if (node->Next == nullptr)
        lastnode = node;
}



