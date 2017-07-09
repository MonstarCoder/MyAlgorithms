//桶式排序

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

void bucketSort(int* a, int n, int max)
{
    int i, j;
    int* buckets;

    if (a == nullptr || n < 1 || max < 1)
        return ;

    if ((buckets = new int[max]) == nullptr)
        return ;

    std::memset(buckets, 0, max * sizeof(int));//将buckets初始化为0

    for (i = 0; i < n; ++i)//计数
        ++buckets[a[i]];

    for (i = 0, j = 0; i < max; ++i)
        while ( (--buckets[i]) >= 0 )
        {
            a[j] = i;
            ++j;
        }

    delete[] buckets;
}

int main()
{
    int i;
    int a[] = {100, 20, 30, 1000, 30, 90, 29, 30};
    int max = 1001;
    int ilen = sizeof(a) /sizeof(a[0]);

    cout << "before sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    bucketSort(a, ilen, max);

    cout << "after sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}
