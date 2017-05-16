#include <iostream>

int BinarySearch( const int A[], int element, int N );
int main()
{
    int array1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << BinarySearch(array1, 5, 10) << std::endl;
}

int BinarySearch( const int A[], int element, int N)//对分查找算法
{
    int low, mid, high;
    low = 0, mid = 0, high = N - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ( element > A[mid] )
            low = mid;
        else if ( element < A[mid] )
            high = mid;
        else
            return mid;
    }
    return -1;
}
