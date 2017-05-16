#include <iostream>

long int Pow ( long int x, unsigned int N )//利用递归方法求幂的快速算法
{
    if ( N == 0 )
        return 1;
    if ( N == 1 )
        return x;
    if ( N % 2 == 0 )
        return Pow( x * x, N / 2 );
    else
        return Pow( x * x, N / 2 ) * x;
}

int main ()
{
    int element = 2, n = 5;
    std::cout << Pow( element, n ) << std::endl;
}
