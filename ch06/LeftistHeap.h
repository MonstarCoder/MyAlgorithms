//左倾堆
#ifndef _LEFTIST_TREE_HPP_
#define _LEFTIST_TREE_HPP_

#include <iomanip>
#include <iostream>

template <class T>
class LeftistNode
{
public:
    T key;
    int npl;//零路径长
    LeftistNode* left;
    LeftistNode* right;

    LeftistNode(T value, LeftistNode* l, LeftistNode* r) :
        key(value), npl(0), left(l), right(r) {}
};

template <class T>
class LeftistHeap
{
private:
    LeftistNode<T>* mRoot;

public:
    LeftistHeap();
    ~LeftistHeap();

    void preOrder();
    void inOrder();
    void postOrder();

    void merge(LeftistHeap<T>* other);//将other的左倾堆合并到this中
    void insert(T key);
    void remove();

    void destroy();

    void print();

private:
    void preOrder(LeftistNode<T>* heap) const;
    void inOrder(LeftistNode<T>* heap) const;
    void postOrder(LeftistNode<T>* heap) const;

    void swapNode(LeftistNode<T>* &x, LeftistNode<T>* &y);//交换节点
    LeftistNode<T>* merge(LeftistNode<T>* &, LeftistNode<T>* &y);//合并
    LeftistNode<T>* insert(LeftistNode<T>* &heap, T key);
    LeftistNode<T>* remove(LeftistNode<T>* &heap);

    void destroy(LeftistNode<T>* &heap);

    void print(LeftistNode<T>* heap, T key, int direction);
};

//构造函数
template <class T>
LeftistHeap<T>::LeftistHeap():mRoot(nullptr)
{
}

//析构函数
template <class T>
LeftistHeap<T>::~LeftistHeap()
{
    destroy(mRoot);
}

//前序遍历
template <class T>
void LeftistHeap<T>::preOrder(LeftistNode<T>* heap) const
{
    if (heap != nullptr)
    {
        std::cout << heap->key << " ";
        preOrder(heap->left);
        preOrder(heap->right);
    }
}

template <class T>
void LeftistHeap<T>::preOrder()
{
    preOrder(mRoot);
}

//中序遍历
template <class T>
void LeftistHeap<T>::inOrder(LeftistNode<T>* heap) const
{
    if (heap != nullptr)
    {
        inOrder(heap->left);
        std::cout << heap->key;
        inOrder(heap->right);
    }
}

template <class T>
void LeftistHeap<T>::inOrder()
{
    inOrder(mRoot);
}

//后序遍历
template <class T>
void LeftistHeap<T>::postOrder(LeftistNode<T>* heap) const
{
    if (heap != nullptr)
    {
        postOrder(heap->left);
        postOrder(heap->right);
        std::cout << heap->key << " ";
    }
}

template <class T>
void LeftistHeap<T>::postOrder()
{
    postOrder(mRoot);
}

//交换节点内容
template <class T>
void LeftistHeap<T>::swapNode(LeftistNode<T>* &x, LeftistNode<T>* &y)
{
    LeftistNode<T> *tmp = x;
    x = y;
    y = tmp;
}

//合并左右倾堆
template <class T>
LeftistNode<T>* LeftistHeap<T>::merge(LeftistNode<T>* &x, LeftistNode<T>* &y)
{
    if (x == nullptr)
        return y;
    if (y == nullptr)
        return x;

    //合并x和y时，将x作为合并后的树的根
    //保证x的key<y的key
    if (x->key > y->key)
        swap(x, y);

    //将x的右孩子和y合并，合并后的树的根是x的右孩子
    x->right = merge(x->right, y);

    //如果x的左孩子为空，或者x的左孩子的npl<右孩子的npl，则交换x和y
    if (x->left == nullptr || x->left->npl < x->right->npl)
    {
        LeftistNode<T>* tmp = x->left;
        x->left = x->right;
        x->right = tmp;
    }

    //设置合并后的新树的npl
    if (x->right == nullptr || x->left == nullptr)
        x->npl = 0;
    else
        x->npl = (x->left->npl > x->right->npl) ?
            (x->right->npl + 1) : (x->left->npl + 1);

    return x;
}

//将other的左倾堆合并到this中
template <class T>
void LeftistHeap<T>::merge(LeftistHeap<T>* other)
{
    mRoot = merge(mRoot, other->mRoot);
}

//将节点插入到左倾堆，并返回根节点
template <class T>
LeftistNode<T>* LeftistHeap<T>::insert(LeftistNode<T>* &heap, T key)
{
    LeftistNode<T>* node;

    node = new LeftistNode<T>(key, nullptr, nullptr);
    if (node == nullptr)
    {
        std::cout << "ERROR: create node failed!" << std::endl;
        return heap;
    }

    return merge(mRoot, node);
}

template <class T>
void LeftistHeap<T>::insert(T key)
{
    mRoot = insert(mRoot, key);
}

//删除节点并返回根节点
template <class T>
LeftistNode<T>* LeftistHeap<T>::remove(LeftistNode<T>* &heap)
{
    if (heap == nullptr)
        return nullptr;

    LeftistNode<T>* l = heap->left;
    LeftistNode<T>* r = heap->right;

    delete heap;

    return merge(l, r);
}

template <class T>
void LeftistHeap<T>::remove()
{
    mRoot = remove(mRoot);
}

//销毁左倾堆
template <class T>
void LeftistHeap<T>::destroy(LeftistNode<T>* &heap)
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
void LeftistHeap<T>::destroy()
{
    destroy(mRoot);
}

//打印二叉树
template <class T>
void LeftistHeap<T>::print(LeftistNode<T>* heap, T key, int direction)
{
    if (heap != nullptr)
    {
        if (direction == 0)
            std::cout << heap->key << "(" << heap->npl << ") is root" << std::endl;
        else
            std::cout << std::setw(2) << heap->key << "(" << heap->npl <<
                ") is " << std::setw(2) << key << "'s" << std::setw(2) <<
                (direction == 1 ? "right child" : "left child") << std::endl;

        print(heap->left, heap->key, -1);
        print(heap->right, heap->key, 1);
    }
}

template <class T>
void LeftistHeap<T>::print()
{
    if (mRoot != nullptr)
        print(mRoot, mRoot->key, 0);
}

#endif
