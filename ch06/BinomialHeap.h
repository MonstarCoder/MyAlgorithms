//二项堆的实现，每一个二项树都是最小堆

#ifndef _BINOMIAL_TREE_HPP_
#define _BINOMIAL_TREE_HPP_

#include <iostream>
#include <iomanip>

template <class T>
class BinomialNode
{
public:
    T key;//关键字
    int degree;//度数
    BinomialNode<T>* child;//左孩子
    BinomialNode<T>* parent;//父节点
    BinomialNode<T>* next;//兄弟节点

    BinomialNode(T value) : key(value), degree(0), child(nullptr), parent(nullptr), next(nullptr) {}
};

template <class T>
class BinomialHeap
{
private:
    BinomialNode<T>* mRoot;

public:
    BinomialHeap();
    ~BinomialHeap();

    void insert(T key);
    void update(T oldkey, T newkey);//更新键值
    void remove(T key);
    void extractMinimum();//删除最小节点

    void combine(BinomialHeap<T>* other);//将other合并到当前二项堆中

    T minimum();//获取最小键值
    bool contains(T key);//检测是否包含key
    void print();

private:
    void link(BinomialNode<T>* child, BinomialNode<T>* root);//合并两个二项堆，将child合并到root中
    BinomialNode<T>* merge(BinomialNode<T>* h1, BinomialNode<T>* h2);//将h1,h2中的根表合并成一个按度数递增的链表
    BinomialNode<T>* combine(BinomialNode<T>* h1, BinomialNode<T>* h2);//合并二项堆，将h1,h2合并成一个堆
    BinomialNode<T>* reverse(BinomialNode<T>* root);//反转二项堆
    BinomialNode<T>* extractMinimum(BinomialNode<T>* root);
    BinomialNode<T>* remove(BinomialNode<T> *root, T key);
    BinomialNode<T>* search(BinomialNode<T>* root, T key);

    void increaseKey(BinomialNode<T>* node, T key);//增加关键字的值
    void decreaseKey(BinomialNode<T>* node, T key);//减少关键字的值
    void updateKey(BinomialNode<T>* node, T key);//更新关键字的值

    void minimum(BinomialNode<T>* root, BinomialNode<T>* &prev_y, BinomialNode<T>* &y);//获取最小根节点
    void print(BinomialNode<T>* node, BinomialNode<T>* prev, int direction);

};

//构造函数
template <class T>
BinomialHeap<T>::BinomialHeap() : mRoot(nullptr)
{}

//析构函数
template <class T>
BinomialHeap<T>::~BinomialHeap()
{}

//获取最小根节点
template <class T>
void BinomialHeap<T>::minimum(BinomialNode<T>* root, BinomialNode<T>* &prev_y, BinomialNode<T>* &y)
{
    BinomialNode<T>* x, * prev_x;//x用来遍历当前节点

    if (root == nullptr)
        return ;

    prev_x = root;
    x = root->next;
    prev_y = nullptr;
    y = root;

    while (x != nullptr)
    {
        if (x->key < y->key)
        {
            y = x;
            prev_y = prev_x;
        }
        prev_x = x;
        x = x->next;
    }
}

//获取最小节点的键值
template <class T>
T BinomialHeap<T>::minimum()
{
    BinomialNode<T>* prev_y, *y;

    minimum(mRoot, prev_y, y);

    return y->key;
}

//合并两个二项堆，将child合并到root中
template <class T>
void BinomialHeap<T>::link(BinomialNode<T>* child, BinomialNode<T>* root)
{
    child->parent = root;
    child->next = root->child;
    root->child = child;
    ++root->degree;
}

//将h1,h2中的根合并成一个按度数递增的链表，返回合并后的根节点
template <class T>
BinomialNode<T>* BinomialHeap<T>::merge(BinomialNode<T>* h1, BinomialNode<T>* h2)
{
    BinomialNode<T>* root = nullptr;
    BinomialNode<T>** pos = &root;

    while (h1 && h2)
    {
        if (h1->degree < h2->degree)
        {
            *pos = h1;
            h1 = h1->next;
        }
        else
        {
            *pos = h2;
            h2 = h2->next;
        }
        pos = &(*pos)->next;
    }
    if (h1)
        *pos = h1;
    else
        *pos = h2;

    return root;
}

//合并二项堆，将h1,h2合并成一个堆，并返回合并后的堆
template <class T>
BinomialNode<T>* BinomialHeap<T>::combine(BinomialNode<T>* h1, BinomialNode<T>* h2)
{
    BinomialNode<T>* root;
    BinomialNode<T>* prev_x, *x, *next_x;

    root = merge(h1, h2);
    if (root == nullptr)
        return nullptr;

    prev_x = nullptr;
    x = root;
    next_x = x->next;

    while (next_x != nullptr)
    {
        if ((x->degree != next_x->degree) || ((next_x->next != nullptr) && (next_x->degree == next_x->next->degree)))
        {
            prev_x = x;
            x = next_x;
        }
        else if (x->key <= next_x->key)
        {
            x->next = next_x->next;
            link(next_x, x);
        }
        else
        {
            if (prev_x = nullptr)
            {
                root = next_x;
            }
            else
            {
                prev_x->next = next_x;
            }
            link(x, next_x);
            x = next_x;
        }
        next_x = x->nextl;
    }

    return root;
}

//将二项堆other合并到当前堆中
template <class T>
void BinomialHeap<T>::insert(T key)
{
    BinomialNode<T>* node;

    //禁止插入相同的键值
    if (contains(key))
    {
        std::cout << "insert error: the key (" << key << ") is existed already!" << std::endl;
        return ;
    }

    node = new BinomialNode<T>(key);
    if (node == nullptr)
        return ;

    mRoot = combine(mRoot, node);
}

//反转二项堆root
template <class T>
BinomialNode<T>* BinomialHeap<T>::reverse(BinomialNode<T>* root)
{
    BinomialNode<T>* next;
    BinomialNode<T>* tail = nullptr;

    if (!root)
        return root;

    root->parent = nullptr;
    while (root->next)
    {
        next = root->next;
        root->next = tail;
        tail = root;
        root = next;
        root->parent = nullptr;
    }
    root->next = tail;

    return root;
}

//移除二项堆root中的最小节点
template<class T>
BinomialNode<T>* BinomialHeap<T>::extractMinimum(BinomialNode<T>* root)
{
    BinomialNode<T>* y, *prev_y;

    if (root == nullptr)
        return root;

    minimum(root, prev_y, y);

    if (prev_y == nullptr)
        root = root->next;
    else
        prev_y->next = y->next;

    BinomialNode<T>* child = reverse(y->child);
    root = combine(root, child);

    delete y;

    return root;
}

template <class T>
void BinomialHeap<T>::extractMinimum()
{
    mRoot = extractMinimum(mRoot);
}

//减少关键字的值
template <class T>
void BinomialHeap<T>::decreaseKey(BinomialNode<T>* node, T key)
{
    if (key >= node->key || contains(key))
    {
        std::cout << "decrease failed: the new key(" << key << ") is existed already, "
            << "or is no smaller than current key(" << node->key << ")" << std::endl;
        return ;
    }
        node->key = key;

        BinomialNode<T>* child, *parent;
        child = node;
        parent = node->parent;
        while (parent != nullptr && child->key < parent->key)
        {
            swap(parent->key, child->key);
            child = parent;
            parent = child->parent;
        }
}

//增加关键字的值
template <class T>
void BinomialHeap<T>::increaseKey(BinomialNode<T>* node, T key)
{
    if (key <= node->key || contains(key))
    {
        std::cout <<"increase failed: the new key(" <<key << ") is existed already, "
            << "or is no greater than current key(" << node->key << "(" << std::endl;
        return ;
    }

    node->key = key;

    BinomialNode<T> *cur, *child, *least;
    cur = node;
    child = cur->child;
    while (child != nullptr)
    {
        if (cur->key > child->key)
        {
            least = child;
            while (child->next != nullptr)
            {
                if (least->key > child->next->key)
                {
                    least = child->next;
                }
                child = child->next;
            }
            swap(least->key, cur->key);

            //调节最小节点，是其满足最小节点性质：父节点<=子节点
            cur = least;
            child = cur->child;
        }
        else
        {
            child = child->next;
        }
    }
}

//更新二项堆的节点node的键值为key
template <class T>
void BinomialHeap<T>::updateKey(BinomialNode<T>* node, T key)
{
    if (node == nullptr)
        return ;

    if (key < node->key)
        decreaseKey(node, key);
    else if (key > node->key)
        increaseKey(node, key);
    else
        std::cout << "No need to update!" << std::endl;
}

//将二项堆中键值oldkey更新为newkey
template <class T>
void BinomialHeap<T>::update(T oldkey, T newkey)
{
    BinomialNode<T>* node;

    node = search(mRoot, oldkey);
    if (node != nullptr)
        updateKey(node, newkey);
}

//查找
template <class T>
BinomialNode<T>* BinomialHeap<T>::search(BinomialNode<T>* root, T key)
{
    BinomialNode<T>* child;
    BinomialNode<T>* parent = root;

    parent = root;
    while ( parent != nullptr )
    {
        if (parent->key == key)
            return parent;
        else
        {
            if ((child = search(parent->child, key)) != nullptr)
                return child;
            parent = parent->next;
        }
    }
    return nullptr;
}

//是否包含
template <class T>
bool BinomialHeap<T>::contains(T key)
{
    return search(mRoot, key) != nullptr ? true : false;
}

//删除节点
template <class T>
BinomialNode<T>* BinomialHeap<T>::remove(BinomialNode<T>* root, T key)
{
    BinomialNode<T>* node;
    BinomialNode<T>* parent, *prev, *pos;

    if (root == nullptr)
        return root;

    if ((node = search(root, key)) == nullptr)
        return root;

    parent = node->parent;
    while (parent != nullptr)
    {
        swap(node->key, parent->key);

        node = parent;
        parent = node->parent;
    }

    prev = nullptr;
    pos = root;
    while (pos != node)
    {
        prev = pos;
        pos = pos->next;
    }

    if (prev)
        prev->next = node->next;
    else
        root = node->next;

    root = combine(root, reverse(node->child));

    delete node;

    return root;
}

template <class T>
void BinomialHeap<T>::remove(T key)
{
    mRoot = remove(mRoot, key);
}

//打印
template <class T>
void BinomialHeap<T>::print(BinomialNode<T>* node, BinomialNode<T>* prev, int direction)
{
    while (node != nullptr)
    {
        if (direction == 1)
            std::cout << "\t" << std::setw(2) << node->key << "(" << node->degree <<
                ") is " << std::setw(2) << prev->key << "'s child" << std::endl;
        else
            std::cout << "\t" << std::setw(2) << node->key << "(" << node->degree <<
                ") is " << std::setw(2) << prev->key << "'s next" << std::endl;

        if (node->child != nullptr)
            print (node->child, node, 1);

        prev = node;
        node = node->next;
        direction = 2;
    }
}

template <class T>
void BinomialHeap<T>::print()
{
    BinomialNode<T> *p;
    if (mRoot == nullptr)
        return ;

    std::cout << "== 二项堆( ";
    p = mRoot;
    while (p != nullptr)
    {
        std::cout << "B" << p->degree << " ";
        p = p->next;
    }
    std::cout << ")的详细信息：　" << std::endl;

    int i = 0;
    p = mRoot;
    while (p != nullptr)
    {
        ++i;
        std::cout << i << "/ 二项树B" << p->degree << ":" <<std::endl;
        std::cout << "\t" << std::setw(2) << p->key << "(" << p->degree <<
            ") is root" << std::endl;

        print (p->child, p, 1);
        p = p->next;
    }
    std::cout << std::endl;
}

#endif
