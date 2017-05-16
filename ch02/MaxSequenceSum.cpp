#include <iostream>

int main()//寻找一个数组中按顺序相加的最大和
{
    int array1[5] = {-1, 0, 1, 2, 3};
    int ThisSum = 0, MaxSum = 0;

    for ( int i = 0; i != 5; ++i)
    {
        ThisSum += array1[i];

        if (ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if (ThisSum < 0)
            ThisSum = 0;
    }
    std::cout << MaxSum << std::endl;
}
