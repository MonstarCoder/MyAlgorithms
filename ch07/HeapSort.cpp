//实现最小堆的升序排序

#include <iostream>
using std::cout;
using std::endl;

void minHeapDown(int* a, int start, int end)//最小堆的向下调整法
{
    int c = start;//当前节点的位置
    int l = 2 * c + 1;//左孩子的位置
    int tmp = a[c];

    for (; l <= end; c = 1, l = 2 * l + 1)
    {
        if (l < end && a[l] > a[l + 1])
            ++l;//选择左右孩子的较小者
        if (tmp <= a[l])
            break;
        else
        {
            a[c] = a[l];
            a[l] = tmp;
        }
    }
}

void heapSortDesc(int* a, int n)//堆排序，降序，从大到小
{
    int i, tmp;

    for (i = n / 2 -1; i >= 0; --i)//从最后一个节点开始
        minHeapDown(a, i, n-1);

    for (i = n - 1; i > 0; --i)
    {
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;

        minHeapDown(a, 0, i - 1);
    }
}

int main()
{
    int i;
    int a[] = {100, 10, 1000, 500, 90, 100000};
    int ilen = sizeof(a) /sizeof(a[0]);

    cout << "before sort:" << endl;
    for (int i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    heapSortDesc(a, ilen);

    cout << "after sort:" << endl;
    for (int i = ilen - 1; i >= 0; --i)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}

