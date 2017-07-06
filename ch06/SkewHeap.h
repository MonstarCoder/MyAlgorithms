//斜堆
#ifndef _SKEW_HEAP_HPP_
#define _SKEW_HEAP_HPP_

#include <iostream>
#include <iomanip>

template <class T>
class SkewNode
{
public:
    T key;
    SkewNode* left;
    SkewNode* right;

    SkewNode(T value, SkewNode* l, SkewNode* r) :
        key(value), left(l), right(r) {}
};

template <class T>
class SkewHeap
{
private:
    SkewNode<T>* mRoot;

public:
    SkewHeap();
    ~SkewHeap();

    void preOrder();
    void inOrder();
    void postOrder();

    void merge(SkewHeap<T>* other);
    void insert(T key);
    void remove();

    void destroy();

    void print();

private:
    void preOrder(SkewNode<T>* heap) const;
    void inOrder(SkewNode<T>* heap) const;
    void postOrder(SkewNode<T>* heap) const;

    void swapNode(SkewNode<T>* &x, SkewNode<T>* &y);
    SkewNode<T>* merge(SkewNode<T>* &x, SkewNode<T>* &y);

    void destroy(SkewNode<T>* &heap);

    void print(SkewNode<T>* heap, T key, int direction);
};

//构造函数
template <class T>
SkewHeap<T>::SkewHeap() : mRoot(nullptr)
{}

//析构函数
template <class T>
SkewHeap<T>::~SkewHeap()
{
    destroy(mRoot);
}

//前序遍历
template <class T>
void SkewHeap<T>::preOrder(SkewNode<T>* heap) const
{
    if (heap != nullptr)
    {
        std::cout << heap->key << " ";
        preOrder(heap->left);
        preOrder(heap->right);
    }
}

template <class T>
void SkewHeap<T>::preOrder()
{
    preOrder(mRoot);
}

//中序遍历
template <class T>
void SkewHeap<T>::inOrder(SkewNode<T>* heap) const
{
    if (heap != nullptr)
    {
        inOrder(heap->left);
        std::cout << heap->key << " ";
        inOrder(heap->rihgt);
    }
}

template <class T>
void SkewHeap<T>::inOrder()
{
    inOrder(mRoot);
}

//后序遍历
template <class T>
void SkewHeap<T>::postOrder(SkewNode<T>* heap) const
{
    if (heap != nullptr)
    {
        postOrder(heap->left);
        postOrder(heap->right);
        std::cout << heap->key << " ";
    }
}

template <class T>
void SkewHeap<T>::postOrder()
{
    postOrder(mRoot);
}

//交换节点的内容
template <class T>
void SkewHeap<T>::swapNode(SkewNode<T>* &x, SkewNode<T>* &y)
{
    SkewNode<T>* tmp = x;
    x = y;
    y = tmp;
}

//合并
template <class T>
SkewNode<T>* SkewHeap<T>::merge(SkewNode<T>* &x, SkewNode<T>* &y)
{
    if (x == nullptr)
        return y;
    if (y == nullptr)
        return x;

    //合并x和y时，将x作为合并后的树的根
    if (x->key > y->key)
        swapNode(x, y);

    //将x的右孩子和y合并
    //合并后直接交换x的左右孩子，而不需要考虑npl
    SkewNode<T>* tmp = merge(x->right, y);
    x->right = x->left;
    x->left = tmp;

    return x;
}

//将other的斜堆合并到this中
template <class T>
void SkewHeap<T>::merge(SkewHeap<T>* other)
{
    mRoot = merge(mRoot, other->mRoot);
}

//插入
template <class T>
void SkewHeap<T>::insert(T key)
{
    SkewNode<T>* node;

    node = new SkewNode<T>(key, nullptr, nullptr);
    if (node == nullptr)
    {
        std::cout << "ERROR: create node failed!" << std::endl;
        return ;
    }

    mRoot = merge(mRoot, node);
}

//删除节点
template <class T>
void SkewHeap<T>::remove()
{
    if (mRoot == nullptr)
        return nullptr;

    SkewNode<T>* l = mRoot->left;
    SkewNode<T>* r = mRoot->right;

    delete mRoot;

    mRoot = merge(l, r);
}

//销毁斜堆
template <class T>
void SkewHeap<T>::destroy(SkewNode<T>* &heap)
{
    if (heap == nullptr)
        return ;

    if (heap->left != nullptr)
        destroy(heap->left);
    if (heap->right != nullptr)
        destroy(heap->right);

    delete heap;
}

template <class T>
void SkewHeap<T>::destroy()
{
    destroy(mRoot);
}

//打印
template <class T>
void SkewHeap<T>::print(SkewNode<T>* heap, T key, int direction)
{
    if (heap != nullptr)
    {
        if (direction == 0)
            std::cout << std::setw(2) << heap->key << " is root" << std::endl;
        else
            std::cout << std::setw(2) << heap->key << " is " << std::setw(2) <<
                heap->key << "'s" << std::setw(2) << (direction == 1 ? "right child" : "left child") << std::endl;

        print(heap->left, heap->key, -1);
        print(heap->right, heap->key, 1);
    }
}

template <class T>
void SkewHeap<T>::print()
{
    if (mRoot != nullptr)
        print(mRoot, mRoot->key, 0);
}

#endif
