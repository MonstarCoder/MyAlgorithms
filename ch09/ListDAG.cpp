//有向无圈图的拓扑排序
//该DAG是通过邻接表实现的

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
using std::cout;
using std::endl;

#define MAX 100

//邻接表
class ListDAG
{
 private:
     class ENode//邻接表中表对应的链表的顶点
     {
        int ivex;
        ENode *nextEdge;
        friend class ListDAG;
     };

     class VNode//邻接表中表的顶点
     {
        char data;
        ENode *firstEdge;
        friend class ListDAG;
     };

 private:
     int mVexNum;//顶点数目
     int mEdgNum;//边的数目
     VNode *mVexs;//顶点数组

 public:
     ListDAG();
     ListDAG(char vexs[], int vlen, char edges[][2], int elen);
     ~ListDAG();

     void DFS();//深度优先遍历图
     void BFS();//广度优先遍历图
     void print();

     int topologicalSort();//拓扑排序

 private:
     char readChar();
     int getPosition(char ch);
     void DFS(int i, int *visited);//深度优先搜索的递归实现
     void linkLast(ENode *list, ENode *node);
};

//创建邻接表对应的图（自己输入）
ListDAG::ListDAG()
{}

//创建邻接表对应的图（用已有的数据）
ListDAG::ListDAG(char vexs[], int vlen, char edges[][2], int elen)
{
    char c1, c2;
    int i, p1, p2;
    ENode *node1, *node2;

    mVexNum = vlen;
    mEdgNum = elen;

    mVexs = new VNode[mVexNum];
    for (i = 0; i < mVexNum; ++i)//初始化“邻接表”的顶点
    {
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = nullptr;
    }

    for (i = 0; i < mEdgNum; ++i)//初始化“邻接表”的边
    {
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = getPosition(c1);
        p2 = getPosition(c2);

        node1 = new ENode();
        node1->ivex = p2;

        if (mVexs[p1].firstEdge == nullptr)
            mVexs[p1].firstEdge == node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
    }
}

//析构函数
ListDAG::~ListDAG()
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
}

//将node节点链接到list的最后
void ListDAG::linkLast(ENode *list, ENode *node)
{
    ENode *p = list;

    while (p->nextEdge)
        p = p->nextEdge;
    p->nextEdge = node;
}

//返回ch的位置
int ListDAG::getPosition(char ch)
{
    int i;
    for (i = 0; i < mVexNum; ++i)
        if (mVexs[i].data == ch)
            return i;

    return -1;
}

//打印
void ListDAG::print()
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

//拓扑排序
//返回值: -1 -- 失败（由于内存不足导致）
//　　　　 0 -- 成功
//　　　　 1 -- 失败（该有向图是有圈的）
int ListDAG::topologicalSort()
{
    int i, j;
    int index = 0;
    int head = 0;//辅助队列的头
    int rear = 0;//辅助队列的尾
    int *queue;//辅助队列
    int *ins;//入度数组
    char *tops;//拓扑排序结果数组
    ENode *node;

    ins = new int[mVexNum];
    queue = new int[mVexNum];
    tops = new char[mVexNum];
    std::memset(ins, 0, mVexNum * sizeof(int));
    std::memset(queue, 0, mVexNum * sizeof(int));
    std::memset(tops, 0, mVexNum * sizeof(char));

    for (i = 0; i < mVexNum; ++i)//统计每个顶点的入度树
    {
        node = mVexs[i].firstEdge;
        while (node != nullptr)
        {
            ++ins[node->ivex];
            node = node->nextEdge;
        }
    }

    for (i = 0; i < mVexNum; ++i)//将所有入度为０的顶点入队列
        if (ins[i] == 0)
            queue[rear++] = i;

    while (head != rear) //队列非空
    {
        j = queue[head++];//出队列
        tops[index++] = mVexs[j].data;//将该顶点添加到tops中，即排序结果
        node = mVexs[j].firstEdge;//获取该顶点为起点的出边队列

        //将与“node”关联的节点的入度减１
        //若减１之后该节点的入度为０，则将该节点添加到队列中
        while (node != nullptr)
        {
            ins[node->ivex]--;
            if (ins[node->ivex] == 0)
                queue[rear++] = node->ivex;

            node = node->nextEdge;
        }
    }

    if (index != mVexNum)
    {
        cout << "Graph has a cyale" << endl;
        delete queue;
        delete ins;
        delete tops;

        return -1;
    }

    cout << "== topSort" << endl;
    for (i = 0; i < mVexNum; ++i)
        cout << tops[i] << " ";
    cout << endl;

    delete queue;
    delete ins;
    delete tops;

    return 0;
}

int main()
{
    char vexs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
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
    ListDAG *pG;

    pG = new ListDAG(vexs, vlen, edges, elen);

    pG->print();

    pG->topologicalSort();

    return 0;
}

