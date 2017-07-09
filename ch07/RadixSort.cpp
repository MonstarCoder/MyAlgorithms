//基数排序，桶排序的扩展

#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

int getMax(int a[], int n)//获取最大值
{
    int i, max;
    max = a[0];

    for (i = 0; i < n; ++i)
        if (a[i] > max)
            max = a[i];
    return max;
}

void bucketSort(int* a, int n, int exp)//桶排序,exp是指数
{
    int output[n - 1];
    int i, j = 0, k, *buckets;

    std::memset(buckets, 0, 10 * sizeof(int));//初始化桶
    //std::memset(output, 0, (n - 1) * sizeof(int));

    for (i = 0; i < n; ++i)
    {
        ++buckets[ (a[i] / exp) % 10 ];//数据出现的次数存储在buckets中
    }
    for (i = 0; i < 10; ++i)
        cout << buckets[i] << " ";
    cout << endl;
/*
    for (i = 0; i < 10; ++i)
    {
        while (buckets[i] > 0)
        {
            for (k = 0; k < n && (((a[k] / exp) % 10) == i); ++k)
            {
                output[j] = a[k];
                ++j;
            }
            break;
        }
    }
    for (i = 0; i < n; ++i)
    {
        a[i] = output[i];
    }
//    for (i = 0; i < n; ++i)
//        cout << "output[" << i << "]:" << output[i] << " ";
//    cout << endl;*/
}
void radixSort(int* a, int n)//基数排序
{
    int exp;
    int max = getMax(a, n);
    cout << "最大值:" << max << endl;


    for (exp = 1; (max / exp) >= 1; exp *= 10)
//        exp = 1;
        bucketSort(a, n, exp);
}

int main()
{
    int i;
    int a[] = {1, 10, 34, 54, 32, 11, 90, 39};
    int ilen = sizeof(a) / sizeof(a[0]);

    cout << "before sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    radixSort(a, ilen);

    cout << "after sort:" << endl;
    for (i = 0; i < ilen; ++i)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}
