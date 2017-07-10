//邻接矩阵表示的“无向图”

#include <iostream>
#include <iomanip>
#include <vector>

using std::cout;
using std::endl;

#define MAX 100

class MatrixUDG {
 private:
     char mVexs[MAX];//顶点集合
     int mVexNum;//顶点数
     int mEdgNum;//边数
     int mMatrix[MAX][MAX];//邻接矩阵

 public:
     MatrixUDG();//创建图（自己输入数据）
     MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);//创建图（用已提供的矩阵）

     ~MatrixUDG();

     void print();

 private:
     char readChar();
     int getPosition(char ch);
};

//创建图，自己输入数据
MatrixUDG::MatrixUDG()
{
    return ;
}

//创建图，用已有矩阵
//参数说明：
//vexs -- 顶点数组
//vlen -- 顶点数组的长度
//edges -- 边数组
//elen -- 边数组的长度
MatrixUDG::MatrixUDG(char vexs[], int vlen, char edges[][2], int elen)
{
    int i, p1, p2;

    mVexNum = vlen;
    mEdgNum = elen;

    for (i = 0; i < mVexNum; ++i)
        mVexs[i] = vexs[i];

    for (i = 0; i < mEdgNum; ++i)
    {
        p1 = getPosition(edges[i][0]);
        p2 = getPosition(edges[i][1]);

        mMatrix[p1][p2] = 1;
        mMatrix[p2][p1] = 1;
    }
}

//析构函数
MatrixUDG::~MatrixUDG()
{

}

//返回ch在mMatrix矩阵中的位置
int MatrixUDG::getPosition(char ch)
{
    int i;
    for (i = 0; i < mVexNum; ++i)
        if (mVexs[i] == ch)
            return i;

    return -1;
}

//打印
void MatrixUDG::print()
{
    int i, j;

    cout << "Matrix Graph:" << endl;
    for (i = 0; i < mVexNum; ++i)
    {
        for (j = 0; j < mVexNum; ++j)
            cout << mMatrix[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    char vexs[] = {'a', 'b', 'c', 'd', 'e', 'f','g'};
    char edges[][2] = {
        {'a', 'c'},
        {'a', 'd'},
        {'a', 'f'},
        {'b', 'c'},
        {'c', 'd'},
        {'e', 'g'},
        {'f', 'g'}
    };

    int vlen = sizeof(vexs) / sizeof(vexs[0]);
    int elen = sizeof(edges) / sizeof(edges[0]);

    MatrixUDG* pG;

    pG = new MatrixUDG(vexs, vlen, edges, elen);

    pG->print();

    return 0;
}
