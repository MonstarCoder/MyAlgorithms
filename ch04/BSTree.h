//二叉查找树的实现。
//注意：“声明”和“实现”都位于本头文件中，应为在二叉查找树的实现使用了模板，而
//c++编译器不支持对模板的分离式编译

#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <iostream>
#include <iomanip>

template <class T>
class BSTNode {
    public:
        T key; //关键字
        BSTNode *left;  //左儿子
        BSTNode *right;  //右儿子
        BSTNode *parent; //父节点

        BSTNode( T value, BSTNode *p, BSTNode *l, BSTNode *r ) :
            key( value ), parent( p ), left( l ), right( r ) {}
};

template <class T>
class BSTree {
    private:
        BSTNode<T> *mRoot;  //根节点

    public:
         BSTree();
         ~BSTree();

        //前序遍历
        void preOrder();
        //中序遍历
        void inOrder();
        //后序遍历
        void postOrder();

        //速归实现查找
        BSTNode<T>* search( T key );
        //非递归实现查找
        BSTNode<T>* iterativeSearch( T key );

        //查找最小节点，返回最小节点的键值
        T minimum();
        //查找最大节点
        T maximum();

        //找节点x的后继节点，即查找二叉树中大于该节点的最小节点
        BSTNode<T>* successor(BSTNode<T>* x);
        //找节点x的前驱节点，即查找二叉树中小于该节点的最大节点
        BSTNode<T>* predecessor(BSTNode<T>* x);

        //插入节点
        void insert( T key );

        //删除节点
        void remove( T key );

        //销毁二叉树
        void destroy();

        //打印二叉树
        void print();
    private:
        //前序遍历二叉树
        void preOrder( BSTNode<T>* tree ) const;
        //中序遍历二叉树
        void inOrder( BSTNode<T>* tree ) const;
        //后序遍历二叉树
        void postOrder( BSTNode<T>* tree ) const;

        //递归实现查找
        BSTNode<T>* search( BSTNode<T>* x, T key ) const;
        //非递归实现查找
        BSTNode<T>* iterativeSearch( BSTNode<T>* x, T key ) const;
        //查找最小节点，返回tree为根节点的二叉树的最小节点
        BSTNode<T>* minimum( BSTNode<T>* tree );
        //查找最大节点，返回tree为根节点的二叉树的最大节点
        BSTNode<T>* maximum( BSTNode<T>* tree );

        //将节点插入到二叉树
        void insert( BSTNode<T>* &tree, BSTNode<T>* z );

        //删除二叉树中的节点，并返回被删除的节点
        BSTNode<T>* remove( BSTNode<T>* &tree, BSTNode<T>* z );

        //销毁二叉树
        void destroy( BSTNode<T>* &tree );

        //打印二叉树
        void print( BSTNode<T>* tree, T key, int direction );
};

//构造函数
template < class T >
BSTree<T>::BSTree() : mRoot( nullptr ) {}

//析构函数
template < class T >
BSTree<T>::~BSTree()
{
    destroy();
}

//前序遍历
template < class T >
void BSTree<T>::preOrder(BSTNode<T>* tree) const
{
    if (tree != nullptr)
    {
        std::cout << tree->left << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void BSTree<T>::preOrder()
{
    preOrder(mRoot);
}

//中序遍历二叉树
template <class T>
void BSTree<T>::inOrder(BSTNode<T>* tree) const
{
    if (tree != nullptr)
    {
        inOrder(tree->left);
        std::cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template <class T>
void BSTree<T>::inOrder()
{
    inOrder(mRoot);
}

//后序遍历二叉树
template <class T>
void BSTree<T>::postOrder(BSTNode<T>* tree) const
{
    if (tree != nullptr)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        std::cout << tree->key << " ";
    }
}

template <class T>
void BSTree<T>::postOrder()
{
    postOrder(mRoot);
}

//递归实现查找
template <class T>
BSTNode<T>* BSTree<T>::search(BSTNode<T>* x, T key) const
{
    if (x == nullptr || x->key == key)
        return x;

    if (key < x->key)
        return search(x->right, key);
    else
        return search(x->right, key);
}

template <class T>
BSTNode<T>* BSTree<T>::search(T key)
{
    return(mRoot, key);
}

//非递归实现查找
template <class T>
BSTNode<T>* BSTree<T>::iterativeSearch(BSTNode<T>* x, T key) const
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
BSTNode<T>* BSTree<T>::iterativeSearch(T key)
{
    iterativeSearch(mRoot, key);
}

//查找最下节点，返回tree为根节点的二叉树的最小节点
template <class T>
BSTNode<T>* BSTree<T>::minimum(BSTNode<T>* tree)
{
    if (tree == nullptr)
        return nullptr;

    while (tree->left != nullptr)
        tree = tree->left;

    return tree;
}

template <class T>
T BSTree<T>::minimum()
{
    BSTNode<T> *p = minimum(mRoot);
    if (p != nullptr)
        return p->key;

    return (T)nullptr;
}

//查找最大节点，返回tree为根节点的二叉树的最大节点
template <class T>
BSTNode<T>* BSTree<T>::maximum(BSTNode<T>* tree)
{
    if (tree == nullptr)
        return nullptr;
    while (tree->right != nullptr)
        tree = tree->right;
    return tree;
}

template <class T>
T BSTree<T>::maximum()
{
    BSTNode<T>* p = maximum(mRoot);
    if (p != nullptr)
        return p->key;

    return (T)nullptr;
}

//找节点x的后继节点
template <class T>
BSTNode<T>* BSTree<T>::successor(BSTNode<T>* x)
{
    if (x->right != nullptr)
        return minimum(x->right);

    BSTNode<T>* y = x->parent;
    while ((y!=nullptr) && (x == y->right))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

//找节点x的前驱节点
template <class T>
BSTNode<T>* BSTree<T>::predecessor(BSTNode<T>* x)
{
    if (x->left != nullptr)
        return maximum(x->left);

    BSTNode<T>* y = x->parent;
    while ((y != nullptr) && (x == y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

//节点插入
//说明：tree为二叉树的根节点，z为插入的节点
template <class T>
void BSTree<T>::insert(BSTNode<T>* &tree, BSTNode<T>* z)
{
    BSTNode<T>* y = nullptr;
    BSTNode<T>* x = tree;

    //查找z的插入位置
    while (x != nullptr)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
        tree = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

//将节点插入到二叉树中
template <class T>
void BSTree<T>:: insert(T key)
{
    BSTNode<T>* z = nullptr;

    //如果新建节点失败，则返回
    if ((z = new BSTNode<T>(key, nullptr, nullptr, nullptr)) == nullptr)
        return;

    insert(mRoot, z);
}

//删除节点z，并返回被删除的节点
template <class T>
BSTNode<T>* BSTree<T>::remove(BSTNode<T>* &tree, BSTNode<T>* z)
{
    BSTNode<T>* x = nullptr;
    BSTNode<T>* y = nullptr;

    if ((z->left == nullptr) || (z->right == nullptr))
        y = z;
    else
        y = successor(z);

    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;

    if (x != nullptr)
        x->parent = y->parent;

    if (y->parent == nullptr)
        tree = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z)
        z->key = y->key;

    return y;
}

//删除节点
template <class T>
void BSTree<T>::remove(T key)
{
    BSTNode<T>* z, *node;

    if ((z = search(mRoot, key)) != nullptr)
        if ((node = remove(mRoot, z)) != nullptr)
            delete node;
}

//销毁二叉树
template <class T>
void BSTree<T>::destroy(BSTNode<T>* &tree)
{
    if (tree == nullptr)
        return;

    if (tree->left != nullptr)
        return destroy(tree->left);
    if (tree->right != nullptr)
        return destroy(tree->right);

    delete tree;
    tree = nullptr;
}

template <class T>
void BSTree<T>::destroy()
{
    destroy(mRoot);
}

//打印二叉树
template <class T>
void BSTree<T>::print(BSTNode<T>* tree, T key, int direction)
{
    if (tree != nullptr)
    {
        if (direction == 0)
            std::cout << std::setw(2) << tree->key << " is root" << std::endl;
        else
            std::cout << std::setw(2) << tree->key << " is " << std::setw(2) << key << " 's"
                << std::setw(12) << (direction == 1 ? "right child" : "left child") << std::endl;

        print(tree->left, tree->key, -1);
        print(tree->right, tree->key, 1);
    }
}

template <class T>
void BSTree<T>::print()
{
    if (mRoot != nullptr)
        print(mRoot, mRoot->key, 0);
}





#endif
