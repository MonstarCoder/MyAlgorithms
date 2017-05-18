#include "queue.h"
#include <iostream>

//检验队列是否为空
template<class T>
bool Queue<T>::IsEmpty()
{
    return ( size == 0 );
}

//检验队列是否为满
template<class T>
bool Queue<T>::IsFull()
{
    return ( size == capacity );
}

//循环函数实现
template<class T>
int Queue<T>::Succ( int Value )
{
    if ( ++Value == capacity )
        Value = 0;
    else
        ++rear;
    return Value;
}

//入队实现
template<class T>
void Queue<T>::EnQueue( T x )
{
    if ( IsFull() )
        std::cerr << "Full Queue!" << std::endl;
    else
    {
        ++size;//队列大小加一
        rear = Succ( rear );
        array[ rear ] = x;
    }
}

//出队实现
template<class T>
T Queue<T>::DeQueue()
{
    if ( IsEmpty() )
        std::cerr << "Empty Queue!" << std::endl;
    else
    {
        --size;
        --front;
        return array[ front ];
    }
}
