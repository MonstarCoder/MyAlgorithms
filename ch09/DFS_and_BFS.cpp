//邻接表表示的无向图
//分别实现深度优先搜索(DFS)和广度优先搜索(BFS)

#include <iostream>
#include <iomanip>
#include <vector>
using std::cout;
using std::endl;

#define MAX 100

//邻接表
class ListUDG
{
 private:
     class ENode//邻接表中表对应的链表的顶点
     {
        int ivex;//该边所指向的顶点的位置
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
     ListUDG(char vexs[], int vlen, char edges[][2], int elen);
     ~ListUDG();

     void DFS();//深度优先搜索
     void BFS();//广度优先搜索
     void print();

 private:
     int readChar(char ch);
     int getPosition(char ch);
     void DFS(int i, int *visited);//深度优先搜索的递归实现
     void linkLast(ENode *list, ENode *node);
};

//创建邻接表对应的图（自己输入）
ListUDG::ListUDG()
{}

//创建邻接表对应的图（用已有的数据）
ListUDG::ListUDG(char vexs[], int vlen, char edges[][2], int elen)
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

        node2 = new ENode();
        node2->ivex = p1;

        if (mVexs[p2].firstEdge == nullptr)
            mVexs[p2].firstEdge = node2;
        else
            linkLast(mVexs[p2].firstEdge, node2);
    }
}

//析构函数
ListUDG::~ListUDG()
{
}

//返回ch的位置
int ListUDG::readChar(char ch)
{
    char i;
    for (i = 0; i < mVexNum; ++i)
        if (mVexs[i].data == ch)
            return i;
    return -1;

}

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

//深度优先搜索的递归实现
void ListUDG::DFS(int i, int *visited)
{
    ENode *node;

    visited[i] = 1;
    cout << mVexs[i].data << " ";
    node = mVexs[i].firstEdge;
    while (node != nullptr)
    {
        if (!visited[node->ivex])
            DFS(node->ivex, visited);
        node = node->nextEdge;
    }
}

//深度优先搜索遍历图
void ListUDG::DFS()
{
    int i;
    int visited[MAX];

    for (i = 0; i < mVexNum; ++i)
        visited[i] = 0;

    cout << "DFS: ";
    for (i = 0; i < mVexNum; ++i)
    {
        if (!visited[i])
            DFS(i, visited);
    }
    cout << endl;
}

//广度优先搜索
void ListUDG::BFS()
{
    int head = 0;
    int rear = 0;
    int queue[MAX];//辅助队列
    int visited[MAX];
    int i, j, k;
    ENode *node;

    for (i = 0; i < mVexNum; ++i)
        visited[i] = 0;

    cout << "BFS: ";
    for (i = 0; i < mVexNum; ++i)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            cout << mVexs[i].data << " ";
            queue[rear++] = i;
        }
        while (head != rear)
        {
            j = queue[head++];
            node = mVexs[j].firstEdge;
            while (node != nullptr)
            {
                k = node->ivex;
                if (!visited[k])
                {
                    visited[k] = 1;
                    cout << mVexs[k].data << " ";
                    queue[rear++] = k;
                }
                node = node->nextEdge;
            }
        }
    }
    cout << endl;
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
    ListUDG *pG;

    pG = new ListUDG(vexs, vlen, edges, elen);

    pG->print();
    pG->DFS();
    pG->BFS();

    return 0;
}

