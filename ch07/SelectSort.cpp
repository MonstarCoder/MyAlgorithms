//选择排序，思想最简单的排序

#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

void selectSort(int* a, int n)
{
    int i, j, min;

    for (i = 0; i < n; ++i)
    {
        min = i;

        for (j = i + 1; j < n; ++j)
        {
            if (a[j] < a[min])
                min = j;
        }

        if (min != i)
            std::swap(a[i], a[min]);
    }
}

int main()
{
    int i;
    int a[] = {100, 100, 30, 40, 10};
    int ilen = sizeof(a) / sizeof(a[0]);

    cout << "before sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    selectSort(a, ilen);

    cout << "after sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}
