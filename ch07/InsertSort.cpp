//插入排序

#include <iostream>

void insertSort(int* a, int n)//a是待排序数组，n是数组长度
{
    int i = 0, j = 0;
    for (i = 1; i < n; ++i)
    {
        int tmp = a[i];
        for (j = i; j >0 && a[j - 1] > tmp; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

int main()
{
    int i;
    int a[] = {10, 50, 100, 20, 30, 5};
    int ilen = (sizeof(a) / sizeof(a[0]));

    std::cout << "before sort:" << std::endl;
    for (i = 0; i < ilen; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    insertSort(a, ilen);

    std::cout << "after sort:" << std::endl;
    for (i = 0; i < ilen; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    return 0;
}
