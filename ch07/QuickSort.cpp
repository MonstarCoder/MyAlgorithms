//快速排序

#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;

void quickSort(int* a, int begin, int end)
{
    if (a == NULL || begin >= end)
        return;

    int center = (begin + end) / 2;

    if (a[begin] > a[center])
        std::swap(a[begin], a[center]);
    if (a[begin] > a[end])
        std::swap(a[begin], a[end]);
    if (a[center] > a[end]) 
        std::swap(a[center], a[end]);
    
    std::swap(a[end - 1], a[center]);
    
    int left = begin;
    int right = end - 1;
    while (left < right)
    {
        while (a[++left] < a[end]);
        while (a[--right] > a[end]);

        if (left < right)
            std::swap(a[left], a[right]);
    }

    std::swap(a[left], a[end - 1]);

    quickSort(a, begin, left - 1);
    quickSort(a, left + 1, end);
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

    quickSort(a, 0, ilen - 1);

    cout << "after sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}
