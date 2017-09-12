#include <iostream>
using std::cout;
using std::endl;

void merge(int* a, int start, int mid, int end)//合并两个数组
{
    int* tmp = new int[end - start + 1];//汇总两个有序区的临时区域
    int i = start;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= end)
    {
        if (a[i] < a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }

    for (; i <= mid; ++i, ++k)
        tmp[k] = a[i];

    for (; j <= end; ++j, ++k)
        tmp[k] = a[j];

    for (i = 0; i < k; ++i)
        a[start + i] = tmp[i];

    delete[] tmp;
}

void mergeSortUp2Down(int* a, int start, int end)//归并排序，从上往下
{
    if (a == nullptr || start >= end)
        return ;

    int mid = (end + start) / 2;

    mergeSortUp2Down(a, start, mid);
    mergeSortUp2Down(a, mid + 1, end);

    merge(a, start, mid, end);
}

int main()
{
    int i;
    int a[] = {90, 100, 10, 200, 900, 11};
    int ilen = sizeof(a) / sizeof(a[0]);

    cout << "before sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    mergeSortUp2Down(a, 0, ilen - 1);

    cout << "after sort:" << endl;
    for (i=0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}


