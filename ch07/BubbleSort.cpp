//冒泡排序

#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

void bubbleSort(int* a, int n)
{
    int i, j;
    int flag;//标记，当标记没有发生变化时，则表明已经排好序，后面的工作无需进行

    for (i = n - 1; i > 0; --i)
    {
        flag = 0;

        for (j = 0; j < i; ++j)
        {
            if (a[j] > a[j + 1])
            {
                std::swap(a[j], a[j + 1]);
                flag = 1;
            }
        }

        if (flag == 0)
            break;
    }
}

int main()
{
    int i;
    int a[] = {100, 10, 30, 10, 30, 90, 1};
    int ilen = (sizeof(a)) / (sizeof(a[0]));

    cout << "before sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    bubbleSort(a, ilen);

    cout << "after sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}

