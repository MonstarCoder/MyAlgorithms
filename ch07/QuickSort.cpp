//快速排序
//核心已转储

#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;

int Median3(int* a, int left, int right)
{
    int center = (left + right) / 2;

    if (a[left] > a[center])
        std::swap(a[left], a[center]);
    if (a[left] > a[right])
        std::swap(a[left], a[right]);
    if (a[center] > a[right])
        std::swap(a[center], a[right]);

    std::swap(a[center], a[right - 1]);//将枢纽元存储在a[right - 1];

    return a[right - 1];
}

void quickSort(int* a, int left, int right)
{
    if (left < right)
    {
        int i, j, pivot;
        i = 1;
        j = right - 1;
 //       pivot = a[i];
        pivot = Median3(a, left, right);//选择三数中值作为枢纽元并调整枢纽元位置

        for (; ;)
        {
            while (a[++i] < pivot) {}
            while (a[--j] > pivot) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right -1]);//将枢纽元与最后i所指元素交换

        quickSort(a, left, i -1);//递归调用
        quickSort(a, i + 1, right);
    }
}

int main()
{
    int i;
    int a[] = {100, 200, 10, 20, 30, 99, 999, 99, 99};
    int ilen = sizeof(a) / sizeof(a[0]);
    cout << "数组大小：" << ilen << endl;

    cout << "before sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    quickSort(a, 0, ilen -1);

    cout << "after sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}
