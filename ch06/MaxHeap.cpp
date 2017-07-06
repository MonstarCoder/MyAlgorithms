//二插堆（最大堆）的实现
#include <iomanip>
#include <iostream>

template <class T>
class MaxHeap
{
private:
    T* mHeap;//数据
    int mCapacity;//总的容量
    int mSize;//实际容量

private:
    void filterdown(int start, int end);//最大堆的向下调整算法
    void filterup(int start);//最大堆的向上调整算法

public:
    MaxHeap();
    MaxHeap(int capacity);
    ~MaxHeap();

    int getIndex(T data);//返回data在二插堆的索引
    int remove(T data);//删除
    int insert(T data);//插入
    void print();//打印
};

//构造函数
template <class T>
MaxHeap<T>::MaxHeap()
{
    new (this)MaxHeap(30);
}

template <class T>
MaxHeap<T>::MaxHeap(int capacity)
{
    mSize = 0;
    mCapacity = capacity;
    mHeap = new T[mCapacity];
}

//析构函数
template <class T>
MaxHeap<T>::~MaxHeap()
{
    mSize = 0;
    mCapacity = 0;
    delete[] mHeap;
}

//返回data在二插堆的索引
template <class T>
int MaxHeap<T>::getIndex(T data)
{
    for (int i = 0; i < mSize; ++i)
        if (data == mHeap[i])
            return i;

    return -1;
}

//向下调整法
//数组实现中，索引的第一个数是０，则第N个节点的左孩子的索引是(2N+1)
//右孩子的索引是(2N+2)
template <class T>
void MaxHeap<T>::filterdown(int start, int end)
{
    int c = start;//当前节点的位置
    int l = 2 * c + 1;//左孩子的位置
    T tmp = mHeap[c];//当前节点的大小

    while (l <= end)
    {
        if (l < end && mHeap[l] < mHeap[l + 1])
            ++l;//左右孩子选取大的
        if (tmp >= mHeap[l])
            break;
        else
        {
            mHeap[c] = mHeap[l];
            c = l;
            l = 2 * l + 1;
        }
    }
    mHeap[c] = tmp;
}

//删除最大堆的data
template <class T>
int MaxHeap<T>::remove(T data)
{
    int index;

    if (mSize == 0)
        return -1;

    //获取data在数组中的索引
    index = getIndex(data);
    if (index == -1)
        return -1;

    mHeap[index] = mHeap[--mSize];
    filterdown(index, mSize -1);

    return 0;
}

//最大堆的向上调整法
template <class T>
void MaxHeap<T>::filterup(int start)
{
    int c = start;//当前节点的位置
    int p = (c - 1) / 2;//父节点的位置
    T tmp = mHeap[c];//当前节点的大小

    while (c > 0)
    {
        if (mHeap[p] >= tmp)
            break;
        else
        {
            mHeap[c] = mHeap[p];
            c = p;
            p = (p - 1) / 2;
        }
    }
    mHeap[c] = tmp;
}

//插入
template <class T>
int MaxHeap<T>::insert(T data)
{
    if (mSize == mCapacity)
        return -1;

    mHeap[mSize] = data;
    filterup(mSize);
    ++mSize;

    return 0;
}

//打印
template <class T>
void MaxHeap<T>::print()
{
    for (int i = 0; i < mSize; ++i)
        std::cout << mHeap[i] << " ";
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int i, len = (sizeof(a)) / sizeof(a[0]);
    MaxHeap<int>* tree = new MaxHeap<int>();

    std::cout << "== 依次添加";
    for (i = 0; i < len; ++i)
    {
        std::cout << a[i] << " ";
        tree->insert(a[i]);
    }

    std::cout << "\n== 最大堆：　";
    tree->print();

    i = 15;
    tree->insert(i);
    std::cout << "\n== 添加元素：　" << i;
    std::cout << "\n==　最大堆：　";
    tree->print();

    i = 9;
    tree->remove(i);
    std::cout << "\n== 删除元素：　" << i;
    std::cout << "\n== 最大堆：　";
    tree->print();
    std::cout << std::endl;

    return 0;
}
