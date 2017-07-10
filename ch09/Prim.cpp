//Prim算法获取最小生成树（邻接表实现）
//无向图

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;

//示例类：边的结构体（用来演示）
class EData
{
 public:
     char start;
     char end;
     int weight;

     EData() {}
     EData(char s, char e, int w) : start(s), end(e), weight(w) {}
};

//邻接表
class ListUDG
{
#define MAX 100
#define INF 100//(~(0x1 << 31)) //最大值（即0x7FFFFFFF）
 private:
     class ENode//邻接表中表对应的链表的顶点
     {
        int ivex;//该边所指向的顶点的位置
        int weight;//权值
        ENode *nextEdge;
        friend class ListUDG;
     };

     class VNode//邻接表中表的顶点
     {
        char data;
        ENode *firstEdge;
        friend class ListUDG;
     };

 private:
     int mVexNum;//顶点数目
     int mEdgNum;//边的数目
     VNode mVexs[MAX];//顶点数

 public:
     ListUDG();
     ListUDG(char vexs[], int vlen, EData *edges[], int elen);
     ~ListUDG();

     void prim(int start);
     void print();

 private:
     char readChar();
     int getPosition(char ch);
     void linkLast(ENode *list, ENode *node);
     int getWeight(int start, int end);//获取图中的边
     int getEnd(int vends[], int i);//获取i的终点
};

//创建邻接表对应的图（自己输入）
ListUDG::ListUDG()
{}

//创建邻接表对应的图（用已有的数据）
ListUDG::ListUDG(char vexs[], int vlen, EData *edges[], int elen)
{
    char c1, c2;
    int i, p1, p2;
    int weight;
    ENode *node1, *node2;

    mVexNum = vlen;
    mEdgNum = elen;

    for (i = 0; i < mVexNum; ++i)//初始化“邻接表”的顶点
    {
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = nullptr;
    }

    for (i = 0; i < mEdgNum; ++i)//初始化“邻接表”的边
    {
        c1 = edges[i]->start;
        c2 = edges[i]->end;
        weight = edges[i]->weight;

        p1 = getPosition(c1);
        p2 = getPosition(c2);

        node1 = new ENode();
        node1->ivex = p2;
        node1->weight = weight;

        if (mVexs[p1].firstEdge == nullptr)
            mVexs[p1].firstEdge == node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);

        node2 = new ENode();
        node2->weight = weight;

        if (mVexs[p2].firstEdge == nullptr)
            mVexs[p2].firstEdge = node2;
        else
            linkLast(mVexs[p2].firstEdge, node2);
    }
}

/*
//析构函数
ListUDG::~ListUDG()
{
    ENode *node;

    for (int i = 0; i < mEdgNum; ++i)
    {
        node = mVexs[i].firstEdge;
        while (node != nullptr)
        {
            delete node;
            node = node->nextEdge;
        }
    }

    delete[] mVexs;
}*/

//将node节点链接到list的最后
void ListUDG::linkLast(ENode *list, ENode *node)
{
    ENode *p = list;

    while (p->nextEdge)
        p = p->nextEdge;
    p->nextEdge = node;
}

//返回ch的位置
int ListUDG::getPosition(char ch)
{
    int i;
    for (i = 0; i < mVexNum; ++i)
        if (mVexs[i].data == ch)
            return i;

    return -1;
}

//打印
void ListUDG::print()
{
    int i, j;
    ENode *node;

    cout << "== List Graph:" << endl;
    for (i = 0; i < mVexNum; ++i)
    {
        cout << i << "(" << mVexs[i].data << "): ";
        node = mVexs[i].firstEdge;
        while (node != nullptr)
        {
            cout << node->ivex << "(" << mVexs[node->ivex].data << ") ";
            node = node->nextEdge;
        }
        cout << endl;
    }
}

//获取<start, end>的权值，若start和end不是联通的，则返回无穷大
int ListUDG::getWeight(int start, int end)
{
    ENode *node;

    if (start == end)
        return 0;

    node = mVexs[start].firstEdge;
    while (node != nullptr)
    {
        if (end == node->ivex)
            return node->weight;
        node = node->nextEdge;
    }

    return INF;
}

//Prim最小生成树
//参数说明：
//start -- 从图中的第start个元素开始，生成最小树
void ListUDG::prim(int start)
{
    int i, j, k, m, n;
    int min;
    int tmp;
    int sum;
    int index = 0;
    char prims[MAX];//prim最小数的结果数组
    int weights[MAX];//顶点间边的权值

    prims[index++] = mVexs[start].data;//prim最小生成树的第一个数是“图中第start个顶点”，因为是从start开始的

    for (i = 0; i < mVexNum; ++i)//初始化
    {
        weights[i] = getWeight(start, i);
    }

    for (i = 0; i < mVexNum; ++i)
    {
        if (start == i)
            continue;

        j = 0;
        k = 0;
        min = INF;

        while (j < mVexNum)
        {
            if (weights[j] != 0 && weights[j] < min)
            {
                min = weights[j];
                k = j;
            }
            ++j;
        }

        prims[index++] = mVexs[k].data;

        weights[k] = 0;

        for (j = 0; j < mVexNum; ++j)
        {
            tmp = getWeight(k, j);
            if (weights[j] != 0 && tmp < weights[j])
                weights[j] = tmp;
        }
    }

    sum = 0;
    for (i = 1; i < index; ++i)//计算最小树的权值
    {
        min = INF;
        n = getPosition(prims[i]);

        for (j = 0; j < i; ++j)
        {
            m = getPosition(prims[j]);
            tmp = getWeight(m, n);
            if (tmp < min)
                min = tmp;
        }
        sum += min;
    }

    cout << "Prim(" << mVexs[start].data << ")= " << sum << ": ";
    for (i = 0; i < mVexNum; ++i)
        cout << prims[i] << " ";
    cout << endl;
}

int main()
{
    char vexs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    EData *edges[] = {
        new EData('a', 'b', 12),
        new EData('a', 'f', 16),
        new EData('a', 'g', 14),
        new EData('b', 'c', 10),
        new EData('b', 'f', 7),
        new EData('c', 'd', 3),
        new EData('c', 'e', 5),
        new EData('c', 'f', 6),
        new EData('d', 'e', 4),
        new EData('e', 'f', 2),
        new EData('e', 'g', 8),
        new EData('f', 'f', 9),
    };

    int vlen = sizeof(vexs) / sizeof(vexs[0]);
    int elen = sizeof(edges) / sizeof(edges[0]);
    ListUDG *pG;

    pG = new ListUDG(vexs, vlen, edges, elen);

    pG->print();

    pG->prim(0);

    return 0;
}
