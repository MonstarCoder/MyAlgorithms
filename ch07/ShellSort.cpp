//希尔排序，一种特殊的插入排序
//增量的选择为1, 2, 4, ... N / 2
#include <iostream>

void shellSort(int* a, int n)
{
    int i, j, increment;//increment为增量

    for (increment = n / 2; increment > 0; increment /= 2)
    {
        for (i = 0; i < increment; ++i)//下面是插入排序
        {
            for (j = i + increment; j < n; j += increment)
            {
                if (a[j] < a[j - increment])//如果a[j] < a[j - increment],则后面的数据都后移
                {
                    int tmp = a[j];
                    int k = j - increment;
                    while (k >= 0 && a[k] > tmp)
                    {
                        a[k + increment] = a[k];
                        k -= increment;
                    }
                    a[k + increment] = tmp;
                }

            }
        }
    }
}

int main()
{
    int i;
    int a[] = {90, 100, 80, 70, 40, 100000, 1000};
    int ilen = sizeof(a) / sizeof(a[0]);

    std::cout << "before sort:" << std::endl;
    for (i = 0; i < ilen; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    shellSort(a, ilen);

    std::cout << "after sort:" << std::endl;
    for (i = 0; i < ilen; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    return 0;
}
