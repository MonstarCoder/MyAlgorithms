#ifndef _SPLAY_TREE_HPP_
#define _SPLAY_TREE_HPP_

#include <iomanip>
#include <iostream>

template <class T>
class SplayTreeNode
{
public:
    T key;//关键值
    SplayTreeNode *left;
    SplayTreeNode *right;

    SplayTreeNode() : left(nullptr), right(nullptr) {}

    SplayTreeNode(T value, SplayTreeNode* l, SplayTreeNode* r) :
        key(value), left(l), right(r) {}
};

template <class T>
class SplayTree
{
private:
    SplayTreeNode<T>* mRoot;

public:
    SplayTree();
    ~SplayTree();

    //前序遍历
    void preOrder();
    //中序遍历
    void inOrder();
    //后序遍历
    void postOrder();

    //递归实现查找
    SplayTreeNode<T>* search(T key);
    //非递归实现查找
    SplayTreeNode<T>* iterativeSearch(T key);

    //查找最小节点
    T minimum();
    //查找最大节点
    T maximum();

    //旋转key对应的节点为根节点
    void splay(T key);

    //将节点插入到伸展树中
    void insert(T key);

    //删除节点
    void remove(T key);

    //销毁
    void destroy();

    //打印
    void print();
private:

    //前序遍历
    void preOrder(SplayTreeNode<T>* tree) const;
    //中序遍历
    void inOrder(SplayTreeNode<T>* tree) const;
    //后序遍历
    void postOrder(SplayTreeNode<T>* tree) const;

    //递归实现查找
    SplayTreeNode<T>* search(SplayTreeNode<T>* x, T key) const;
    //非递归实现查找
    SplayTreeNode<T>* iterativeSearch(SplayTreeNode<T>* x, T key) const;

    //查找最小节点
    SplayTreeNode<T>* minimum(SplayTreeNode<T>* tree);
    //查找最大节点
    SplayTreeNode<T>* maximum(SplayTreeNode<T>* tree);

    //旋转
    SplayTreeNode<T>* splay(SplayTreeNode<T>* tree, T key);

    //插入
    SplayTreeNode<T>* insert(SplayTreeNode<T>* &tree, SplayTreeNode<T>* z);

    //删除
    SplayTreeNode<T>* remove(SplayTreeNode<T>* &tree, T key);

    //销毁
    void destroy(SplayTreeNode<T>* &tree);

    //打印
    void print(SplayTreeNode<T>* tree, T key, int direction);
};

//构造函数
template <class T>
SplayTree<T>::SplayTree() : mRoot(nullptr)
{}

//析构函数
template <class T>
SplayTree<T>::~SplayTree()
{
    destroy(mRoot);
}

//前序遍历
template <class T>
void SplayTree<T>::preOrder(SplayTreeNode<T>* tree) const
{
    if (tree != nullptr)
    {
        std::cout << tree->key << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void SplayTree<T>::preOrder()
{
    preOrder(mRoot);
}

//中序遍历
template <class T>
void SplayTree<T>::inOrder(SplayTreeNode<T>* tree) const
{
    if (tree != nullptr)
    {
        inOrder(tree->left);
        std::cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template <class T>
void SplayTree<T>::inOrder()
{
    inOrder(mRoot);
}

//后序遍历
template <class T>
void SplayTree<T>::postOrder(SplayTreeNode<T>* tree) const
{
    if (tree != nullptr)
    {
        postOrder(tree->left);
        postPrder(tree->right);
        std::cout << tree->key << " ";
    }
}

template <class T>
void SplayTree<T>::postOrder()
{
    postOrder(mRoot);
}

//递归实现查找
template <class T>
SplayTreeNode<T>* SplayTree<T>::search(SplayTreeNode<T>* x, T key) const
{
    if (x == nullptr || x->key == key)
        return x;

    if (key < x->key)
        return search(x->left, key);

    if (key > x->key)
        return search(x->right, key);
}

template <class T>
SplayTreeNode<T>* SplayTree<T>::search(T key)
{
    return search(mRoot, key);
}

//非递归实现查找
template <class T>
SplayTreeNode<T>* SplayTree<T>::iterativeSearch(SplayTreeNode<T>* x, T key) const
{
    while ((x != nullptr) && (x->key != key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template <class T>
SplayTreeNode<T>* SplayTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(mRoot, key);
}

//查找最小节点
template <class T>
SplayTreeNode<T>* SplayTree<T>::minimum(SplayTreeNode<T>* tree)
{
    if (tree == nullptr)
        return nullptr;

    while (tree->left != nullptr)
        tree = tree->left;

    return tree;
}

template <class T>
T SplayTree<T>::minimum()
{
    SplayTreeNode<T>* p = minimum(mRoot);
    if (p != nullptr)
        return p->key;

    return (T)nullptr;
}

//查找最大节点
template <class T>
SplayTreeNode<T>* SplayTree<T>::maximum(SplayTreeNode<T>* tree)
{
    if (tree == nullptr)
        return nullptr;

    while (tree->right != nullptr)
        tree = tree->right;

    return tree;
}

template <class T>
T SplayTree<T>::maximum()
{
    SplayTreeNode<T>* p = maximum(mRoot);
    if (p != nullptr)
        return p->key;

    return (T)nullptr;
}

//旋转key对应的节点为根节点，并返回值为根节点
//(1),伸展树存在键值为key的节点
//将键值为key的节点旋转为根节点
//(2),伸展树中不存在键值为key的节点，并且key < tree->key
//(a)，键值为key的节点的前驱节点存在的话，将键值为key的节点的前驱节点旋转为根节点
//(b),键值为key的节点的前驱节点不存在的话，则意味着key比树中的任意键值都小，此时将最小
//节点旋转为根节点
//(3),伸展树中不存在键值为key的节点，并且key > tree->key
//(a), 键值为key的节点的后继节点存在的话，将键值为key的节点的后继节点旋转为根节点
//(b),兼职为key的节点的后继节点不存在的话，意味着key比树中的任意键值都大，此时
//将最大节点旋转为根节点
template <class T>
SplayTreeNode<T>* SplayTree<T>::splay(SplayTreeNode<T>* tree, T key)
{
    SplayTreeNode<T> N, *l, *r, *c;

    if (tree == nullptr)
        return tree;

    N.left = N.right = nullptr;
    l = r = &N;

    for (; ;)
    {
        if (key < tree->key)
        {
            if (tree->left == nullptr)
                break;
            if (key < tree->left->key)
            {
                c = tree->left;//右旋
                tree->left = c->right;
                c->right = tree;
                tree = c;
                if (tree->left == nullptr)
                    break;
            }
            r->left = tree;//右链接
            r = tree;
            tree = tree->left;
        }
        else if (key > tree->key)
        {
            if (tree->right == nullptr)
                break;
            if (key > tree->right->key)
            {
                c = tree->right;//左旋
                tree->right = c->left;
                c->left = tree;
                tree = c;
                if (tree->right == nullptr)
                    break;
            }
            l->right = tree;//左链接
            l= tree;
            tree = tree->right;
        }
        else
        {
            break;
        }
    }

    l->right = tree->left;//组合
    r->left = tree->right;
    tree->left = N.right;
    tree->right = N.left;

    return tree;
}

template <class T>
void SplayTree<T>::splay(T key)
{
    mRoot = splay(mRoot, key);
}

//插入节点
template <class T>
SplayTreeNode<T>* SplayTree<T>::insert(SplayTreeNode<T>* &tree, SplayTreeNode<T>* z)
{
    SplayTreeNode<T>* y = nullptr;
    SplayTreeNode<T>* x = tree;

    //查找z插入的位置
    while (x != nullptr)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else if (z->key > x->key)
            x = x->right;
        else
        {
            std::cout << "不允许插入相同节点(" << z->Key << ")!" << std::endl;
            delete z;
            return tree;
        }
    }

    if (y == nullptr)
        tree = z;
    else if (z->key < y->key)
        y->key = z;
    else
        y->right = z;

    return tree;
}

template <class T>
void SplayTree<T>::insert(T key)
{
    SplayTreeNode<T>* z = nullptr;

    //如果创建失败，则返回
    if ((z = new SplayTreeNode<T>(key, nullptr, nullptr)) == nullptr)
        return;

    //插入节点
    mRoot = insert(mRoot, z);
    //将节点key旋转为根节点
    mRoot = splay(mRoot, key);
}

//删除节点
template <class T>
SplayTreeNode<T>* SplayTree<T>::remove(SplayTreeNode<T>* &tree, T key)
{
    SplayTreeNode<T>* x;

    if (tree == nullptr)
        return nullptr;

    if (search(tree, key) == nullptr)
        return tree;

    tree = splay(tree, key);

    if (tree->left != nullptr)
    {
        x = splay(tree->left, key);//将tree的前驱节点旋转为根节点
        x->right = tree->right;//移除tree节点
    }
    else
        x = tree->right;

    delete tree;

    return x;
}

template <class T>
void SplayTree<T>::remove(T key)
{
    mRoot = remove(mRoot, key);
}

//销毁伸展树
template <class T>
void SplayTree<T>::destroy(SplayTreeNode<T>* &tree)
{
    if (tree == nullptr)
        return;

    if (tree->left != nullptr)
        destroy(tree->left);
    if (tree->right != nullptr)
        destroy(tree->right);

    delete tree;
}

template <class T>
void SplayTree<T>::destroy()
{
    destroy(mRoot);
}

//打印伸展树
template <class T>
void SplayTree<T>::print(SplayTreeNode<T>* tree, T key, int direction)
{
    if (tree != nullptr)
    {
        if (direction == 0)
            std::cout << std::setw(2) << tree->key << " is not" << std::endl;
        else
            std::cout << std::setw(2) << tree->key << " is " << std::setw(2)
                << key << "'s " << std::setw(12) <<
                (direction == 1 ? "right child" : "left child") << std::endl;

        print(tree->left, tree->key, -1);
        print(tree->right, tree->key, 1);
    }
}

template <class T>
void SplayTree<T>::print()
{
    if (mRoot != nullptr)
        print(mRoot, mRoot->key, 0);
}

#endif
