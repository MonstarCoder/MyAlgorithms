#include "stack.h"
#include <iostream>

//实现IsEmpty()函数
template<class T>
bool Stack<T>::IsEmpty()
{
    return cnts == 0;
}

//Push()实现
template<class T>
void Stack<T>::Push( T x )
{
    Node<T>* pnode = new Node<T>( x );//申请入栈的元素空间
    pnode->Next = head->Next;
    head->Next = pnode;
    ++cnts;
}

//Top()实现
template<class T>
T Stack<T>::Top()
{
    if ( head->Next != nullptr )
        return head->Next->Data;
    std::cerr << "Empty stack!" << std::endl;
    return 0;
}

//Pop()实现
template<class T>
T Stack<T>::Pop()
{
    if ( head->Next == nullptr )
        std::cerr << "Empty stack!" << std::endl;
    else
    {
        Node<T>* temp = head->Next;//申请临时节点
        head->Next = head->Next->Next;
        T popData = temp->Data;
        delete temp;
        return popData;
        --cnts;
    }
}

//打印函数实现
template<class T>
void Stack<T>::printStack()
{
    if ( head->Next != nullptr )
    {
        Node<T>* temp = head;
        while ( temp->Next != nullptr )
        {
            temp = temp->Next;
            std::cout << temp->Data << std::endl;
        }
    }
    else
        std::cerr << "Empty Stack!" << std::endl;
}

//计数函数实现
template<class T>
int Stack<T>::Counts()
{
    return cnts;
}
