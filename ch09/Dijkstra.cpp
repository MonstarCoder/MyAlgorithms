//Dijkstra算法获取最短路径（邻接表实现）
//包括有向图和无向图

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
     VNode mVexs[MAX];//顶点数组

 public:
     ListUDG();
     ListUDG(char vexs[], int vlen, EData *edges[], int elen);
     ~ListUDG();

     void dijkstra(int vs, int vexs[], int dist[]);
     void print();

 private:
     char readChar();
     int getPosition(char ch);
     void linkLast(ENode *list, ENode *node);
     int getWeight(int start, int end);//获取图中的边
     EData* getEdges();
     void sortEdges(EData *edges, int elen);//对边按权值大小进行排序（升序）
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

//获取图中的边
EData* ListUDG::getEdges()
{
    int i, j;
    int index;
    ENode *node;
    EData *edges;

    edges = new EData[mEdgNum];
    for (i = 0; i < mVexNum; ++i)
    {
        node = mVexs[i].firstEdge;
        while (node != nullptr)
        {
            if (node->ivex > i)
            {
                edges[index].start = mVexs[i].data;
                edges[index].end = mVexs[node->ivex].data;
                edges[index].weight = node->weight;
                ++index;
            }
            node = node->nextEdge;
        }
    }
    return edges;
}

//对边按权值大小进行排序
void ListUDG::sortEdges(EData *edges, int elen)
{
    int i, j;

    for (i = 0; i < elen; ++i)
    {
        for (j = i + 1; i < elen; ++j)
        {
            if (edges[i].weight > edges[j].weight)
            {
                std::swap(edges[i], edges[j]);
            }
        }
    }
}

//获取i的终点
int ListUDG::getEnd(int vends[], int i)
{
    while (vends[i] != 0)
        i = vends[i];
    return i;
}

//Dijkstra最短路径
//参数说明：
//vs -- 起始顶点
//prev -- 前驱顶点数组
//dist -- 长度数组
void ListUDG::dijkstra(int vs, int prev[], int dist[])
{
    int i, j, k;
    int min;
    int tmp;
    int flag[MAX];//flag[i] = 1表示顶点vs到顶点i的最短路径已成功获取

    for (i = 0; i < mVexNum; ++i)//初始化
    {
        flag[i] = 0;
        prev[i] = 0;
        dist[i] = getWeight(vs, i);
    }

    flag[vs] = 1;
    dist[vs] = 0;

    for (i = 1; i < mVexNum; ++i)//遍历mVexNum-1次，每次找出一个顶点的最短路径
    {
        min = INF;
        for (j = 0; j < mVexNum; ++j)
        {
            if (flag[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }

        flag[k] = 1;

        for (j = 0; j < mVexNum; ++j)
        {
            tmp = getWeight(k, j);
            tmp = (tmp == INF ? INF : (min + tmp));//防止溢出
            if (flag[j] == 0 && (tmp < dist[j]))
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    cout << "dijkstra(" << mVexs[vs].data << "): " << endl;
    for (i = 0; i < mVexNum; ++i)
        cout << " shortest(" << mVexs[vs].data << ", " << mVexs[i].data << ")= " << dist[i] << endl;

}

int main()
{
    int prev[MAX] = {0};
    int dist[MAX] = {0};

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

    pG->dijkstra(3, prev, dist);

    return 0;
}


