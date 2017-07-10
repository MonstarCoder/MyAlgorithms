//链表表示的“有向图”

#include <iostream>
#include <iomanip>
#include <vector>
using std::cout;
using std::endl;

#define MAX 100

class ListUDG
{
 private:
     class ENode//邻接表中表对应的链表的顶点
     {
     public:
         int ivex;//该边所指向的顶点的位置
         ENode* nextEdge;//指向下一条弧的指针
     };

     class VNode//邻接表中表的顶点
     {
     public:
         char data;//顶点信息
         ENode* firstEdge;//指向第一条依附该顶点的弧
     };

 private:
     int mVexNum;
     int mEdgNum;
     VNode mVexs[MAX];

 public:
     ListUDG();
     ListUDG(char vexs[], int vlen, char edges[][2], int elen);
     ~ListUDG();

     void print();

 private:
     char readChar();
     int getPosition(char ch);
     void linkLast(ENode* list, ENode* node);//将node节点链接到list的最后
};

//创建图，用已有数据
ListUDG::ListUDG(char vexs[], int vlen, char edges[][2], int elen)
{
    char c1, c2;
    int i, p1, p2;
    ENode *node1, *node2;

    mVexNum = vlen;
    mEdgNum = elen;

    for (i = 0; i < mVexNum; ++i)
    {
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = nullptr;
    }

    for (i = 0; i < mEdgNum; ++i)
    {
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = getPosition(c1);
        p2 = getPosition(c2);

        node1 = new ENode();
        node1->ivex = p2;

        if (mVexs[p1].firstEdge == nullptr)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
    }
}

//析构函数
ListUDG::~ListUDG()
{}

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

    cout << "List Graph: " << endl;
    for (i = 0; i < mVexNum; ++i)
    {
        cout << i << "(" << mVexs[i].data << "): ";
        node = mVexs[i].firstEdge;
        while (node != nullptr)
        {
            cout << node->ivex << "(" << mVexs[node->ivex].data << ")";
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

    return 0;
}
