#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_

#include <iomanip>
#include <iostream>

template <class T>
class AVLTreeNode
{
public:
    T key;//关键字
    int height;//高度
    AVLTreeNode *left;//左孩子
    AVLTreeNode *right;//右孩子

    AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r) :
        key(value), height(0), left(l), right(r) {}
};

template <class T>
class AVLTree
{
private:
    AVLTreeNode<T>* mRoot;//根节点

public:
    AVLTree();
    ~AVLTree();

    //获取树的高度
    int height();
    //获取树的高度
    int max(int a, int b);

    //前序遍历
    void preOrder();
    //中序遍历
    void inOrder();
    //后序遍历
    void postOrder();

    //递归实现查找关键值
    AVLTreeNode<T>* search(T key);
    //非递归实现查找
    AVLTreeNode<T>* iterativeSearch(T key);

    //查找最小节点，返回键值
    T minimum();
    //查找最大节点
    T maximum();

    //插入
    void insert(T key);

    //删除
    void remove(T key);

    //销毁树
    void destroy();

    //打印
    void print();

private:
    //获取树的高度
    int height(AVLTreeNode<T>* tree);

    //前序遍历
    void preOrder(AVLTreeNode<T>* tree) const;
    //中序遍历
    void inOrder(AVLTreeNode<T>* tree) const;
    //后序遍历
    void postOrder(AVLTreeNode<T>* tree) const;

    //递归实现查找
    AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;
    //非递归实现查找
    AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;

    //查找最小节点
    AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
    //查找最大节点
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

    //LL:左单旋转
    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);

    //RR:右单旋转
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);

    //LR:左双旋转
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);

    //RL:右双旋转
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);

    //将节点插入到树中
    AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);

    //删除节点并返回节点
    AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);

    //销毁树
    void destroy(AVLTreeNode<T>* &tree);

    //打印
    void print(AVLTreeNode<T>* tree, T key, int direction);
};

//构造函数
template <class T>
AVLTree<T>::AVLTree() : mRoot(nullptr)
{}

//析构函数
template <class T>
AVLTree<T>::~AVLTree()
{
    destroy(mRoot);
}

//获取树的高度
template <class T>
int AVLTree<T>::height()
{
    return height(mRoot);
}

//比较两个值的大小
template <class T>
int AVLTree<T>::max(int a, int b)
{
    return a > b ? a : b;
}

//前序遍历
template <class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
    if (tree != nullptr)
    {
        std::cout << tree->key << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void AVLTree<T>::preOrder()
{
    preOrder(mRoot);
}

//中序遍历
template <class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const
{
    if (tree != nullptr)
    {
        inOrder(tree->left);
        std::cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template <class T>
void AVLTree<T>::inOrder()
{
    inOrder(mRoot);
}

//后序遍历
template <class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* tree) const
{
    if (tree != nullptr)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        std::cout << tree->key <<" ";
    }
}

template <class T>
void AVLTree<T>:: postOrder()
{
    postOrder(mRoot);
}

//递归实现查找
template<class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* x, T key) const
{
    if (x == nullptr || x->key == key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
    return search(mRoot, key);
}

//非递归实现查找
template <class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const
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
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(mRoot, key);
}

//查找最小节点
template <class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
    if (tree == nullptr)
        return nullptr;

    while (tree->left != nullptr)
        tree = tree->left;
    return tree;
}

template <class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T>* p = minimum(mRoot);
    if (p != nullptr)
        return p->key;
    return (T)nullptr;
}

//查找最大节点
template <class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
    if (tree ==nullptr)
        return nullptr;

    while (tree->right != nullptr)
        tree = tree->right;
    return tree;
}

template <class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T>* p = maximum(mRoot);
    if (p != nullptr)
        return p->key;

    return (T)nullptr;
}

//LL:左单旋转
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
    AVLTreeNode<T>* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) +1;

    return k1;
}

//RR:右右旋转
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
    AVLTreeNode<T>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) +1;

    return k2;
}

//LR:左双旋转
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);//先在k3的左儿子和孙子之间旋转

    return leftLeftRotation(k3);//然后在k3单旋转
}

//RL:右双旋转
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

//节点插入
template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
    if (tree == nullptr)
    {
        tree = new AVLTreeNode<T>(key, nullptr, nullptr);//新建节点
        if (tree == nullptr)
        {
            std::cout << "ERROT: create avltree node failed!" << std::endl;
            return nullptr;
        }
    }
    else if (key < tree-key)//插入到左子树的情形
    {
        tree->left = insert(tree->left, key);
        //插入节点后，若失去平衡，则进行相应调节
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);

        }
    }
    else if (key > tree->key)//插入到右子树的情形
    {
        tree->right = insert(tree->right, key);
        //调节
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    else
    {
        std::cout << "添加失败：不允许添加相同的节点！" << std::endl;
    }

    tree->height = max(height(tree->left), height(tree->right)) +1;

    return tree;
}

template <class T>
void AVLTree<T>::insert(T key)
{
    insert(mRoot, key);
}

//删除节点
template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
    if (tree == nullptr || z = nullptr)
        return nullptr;

    if (z->key < tree->key)
    {
        tree->left = remove(tree->left, z);
        //删除节点后，若失去平衡则进行调节
        if (height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode<T> *r = tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)
    {
        tree->right = remove(tree->right, z);
        //失去平衡后进行调节
        if (height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode<T>* l = tree->left;
            if (height(l->right) > height(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else//tree是对应要删除的节点
    {
        if ((tree->left != nullptr) && (tree->right != nullptr))//左右孩子都非空
            if (height(tree->left) > height(tree->right))
            {
                //如果左子树比右子树高，则找出左子树的最大节点，将该最大节点赋予tree
                //并删除该节点，删除后tree仍是平衡的
                AVLTreeNode<T>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                //如果tree的左子树不比右子树高，则找出右子树的最小节点，
                //将最小节点的值赋予tree，删除该最小节点。
                AVLTreeNode<T>* min = maximum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        else
        {
            AVLTreeNode<T>* tmp = tree;
            tree = (tree->left != nullptr) ? tree->left : tree->right;
            delete tmp;
        }
    }
    return tree;
}

template <class T>
void AVLTree<T>::remove(T key)
{
    AVLTreeNode<T>* z;
    if ((z = search(mRoot, key)) != nullptr)
        mRoot = remove(mRoot, z);
}

//销毁AVL树
template <class T>
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree)
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
void AVLTree<T>::destroy()
{
    destroy(mRoot);
}

//打印
template <class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)
{
    if (tree != nullptr)
    {
        if (direction == 0)
            std::cout << std::setw(2) << tree-key << " is root" << std::endl;
        else
            std::cout < std::setw(2) << tree-key << " is " << key << "'s " << std::setw(12)
                << (direction == 1 ? "right child" : "left child") << std::endl;

    print(tree->left, tree->key, -1);
    print(tree->right, tree->key, 1);
    }
}

template <class T>
void AVLTree<T>::print()
{
    if (mRoot != nullptr)
        print(mRoot, mRoot->key, 0);
}




#endif
