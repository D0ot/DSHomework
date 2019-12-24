#ifndef _GRAPH_H
#define _GRAPH_H

#include "../libs/headers.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <queue>

#include "../libs/headers.h"

typedef std::function<void(Graph &G, int v)> GraphIterFun;

void GraphRawInitial(Graph &G)
{
    std::memset(static_cast<void *>(&G), 0, sizeof(Graph));
}

void GraphClearVisited()
{
    std::memset(static_cast<void *>(visited), 0, sizeof(visited));
}

GraphIterFun print = [](Graph &G, int v) {
    std::cout << G.VerList[v].data << ' ';
};

GraphIterFun doNothing = [](Graph, int) {
};

// PROBLEM 1

// Depth first
void GraphDFS_Inner(Graph &G, int v, const GraphIterFun &visitor, const GraphIterFun &pre = doNothing, const GraphIterFun &post = doNothing)
{
    pre(G, v);
    visited[v] = true;
    visitor(G, v);

    int w = firstAdj(G, v);

    while (w != 0)
    {
        if (visited[w] == false)
        {
            GraphDFS_Inner(G, w, visitor, pre, post);
        }
        w = nextAdj(G, v, w);
    }
    post(G, v);
}

void GraphDFS(Graph &G, int v, const GraphIterFun &visitor, const GraphIterFun &pre = doNothing, const GraphIterFun &post = doNothing)
{
    GraphClearVisited();
    GraphDFS_Inner(G, v, visitor, pre, post);
}

// breadth first
void GraphBFS_Inner(Graph &G, int v, const GraphIterFun &visitor, const GraphIterFun &pre = doNothing, const GraphIterFun &post = doNothing)
{

    int w = firstAdj(G, v);

    std::queue<int> qu;

    qu.push(v);
    visited[v] = true;
    pre(G, v);

    while (!qu.empty())
    {
        int current = qu.front();

        visitor(G, current);

        int w = firstAdj(G, current);

        while (w != 0)
        {
            if (visited[w] == false)
            {
                qu.push(w);
                visited[w] = true;
                pre(G, w);
            }
            w = nextAdj(G, current, w);
        }

        // to keep context for GraphIterFun 'post'
        qu.pop();
        post(G, current);
    }
}

void GraphBFS(Graph &G, int v, const GraphIterFun &visitor, const GraphIterFun &pre = doNothing, const GraphIterFun &post = doNothing)
{
    GraphClearVisited();
    GraphBFS_Inner(G, v, visitor, pre, post);
}

// PROBLEM 2

size_t GraphArcCount(Graph &G)
{
    size_t sum = 0;
    for (int i = 1; i < G.VerNum + 1; ++i)
    {
        int w = firstAdj(G, i);
        while (w != 0)
        {
            sum++;
            w = nextAdj(G, i, w);
        }
    }

    if (G.gKind == UDG || G.gKind == UDN)
    {
        sum = sum / 2;
    }
    return sum;
}

// PROBLEM 3
int GraphEdgeInfo(Graph &G, int v, int w)
{
    auto edgeIter = G.VerList[v].firstEdge;
    while (edgeIter)
    {
        if (edgeIter->adjVer == w)
        {
            return edgeIter->eInfo;
        }
        edgeIter = edgeIter->next;
    }

    return 0;
}

void GraphAddEdge(Graph &G, int v, int w, int info)
{
    int last = v;

    auto edgeIter = G.VerList[last].firstEdge;

    EdgeNode *temp = new EdgeNode;

    temp->adjVer = w;
    temp->eInfo = info;
    temp->next = nullptr;

    G.ArcNum++;

    if (!edgeIter)
    {
        G.VerList[last].firstEdge = temp;
    }
    else
    {
        while (edgeIter->next)
        {
            edgeIter = edgeIter->next;
        }

        edgeIter->next = temp;
    }
}

void GraphDFSTreeSpanning(Graph &G, Graph &spanning)
{
    spanning.gKind = G.gKind;
    spanning.VerNum = G.VerNum;
    for (int i = 1; i < G.VerNum + 1; ++i)
    {
        spanning.VerList[i].data = G.VerList[i].data;
        spanning.VerList[i].firstEdge = nullptr;
    }

    std::vector<int> st;

    GraphIterFun pre = [&st, &spanning](Graph &G, int v) {
        if (st.empty())
        {
            st.push_back(v);
        }
        else
        {
            int last = st.back();
            std::cout << "Add edge " << G.VerList[last].data << " to " << G.VerList[v].data << std::endl;
            GraphAddEdge(spanning, last, v, GraphEdgeInfo(G, last, v)); // 0 is not right..., to make it right, do a search on G
            spanning.ArcNum += 1;
            st.push_back(v);
        }
    };

    GraphIterFun post = [&st, &spanning](Graph &G, int v) {
        st.pop_back();
    };

    GraphClearVisited();
    for (int i = 1; i < G.VerNum + 1; ++i)
    {
        GraphDFS_Inner(G, i, doNothing, pre, post);
    }
}

// PROBLEM 4
void GraphBFSTreeSpanning(Graph &G, Graph &spanning)
{
    spanning.gKind = G.gKind;
    spanning.VerNum = G.VerNum;

    for (int i = 1; i < G.VerNum + 1; ++i)
    {
        spanning.VerList[i].data = G.VerList[i].data;
        spanning.VerList[i].firstEdge = nullptr;
    }

    std::queue<int> qu;

    GraphIterFun pre = [&qu, &spanning](Graph &G, int v) {
        if (qu.empty())
        {
            qu.push(v);
        }
        else
        {
            int last = qu.front();
            //std::cout << "Add edge " << G.VerList[last].data << " to " << G.VerList[v].data << std::endl;
            GraphAddEdge(spanning, last, v, GraphEdgeInfo(G, last, v)); // 0 is not right,...
            spanning.ArcNum += 1;
            qu.push(v);
        }
    };

    GraphIterFun post = [&qu, &spanning](Graph &G, int v) {
        qu.pop();
    };

    GraphClearVisited();
    for (int i = 1; i < G.VerNum + 1; ++i)
    {
        GraphBFS_Inner(G, i, doNothing, pre, post);
    }
}

// PROBLEM 5

auto GraphHasEdge(Graph &G, int v, int w)
{
    auto edgeIter = G.VerList[v].firstEdge;
    while (edgeIter)
    {
        if (edgeIter->adjVer == w)
        {
            return std::make_pair(true, edgeIter->eInfo);
        }
        edgeIter = edgeIter->next;
    }

    return std::make_pair(false, 0);
}

void GraphPrim(Graph &G, Graph &spanning, int v)
{
    spanning.gKind = G.gKind;
    spanning.VerNum = G.VerNum;
    spanning.ArcNum = 0;

    for (int i = 1; i < G.VerNum + 1; ++i)
    {
        spanning.VerList[i].data = G.VerList[i].data;
        spanning.VerList[i].firstEdge = nullptr;
    }

    GraphClearVisited();
    size_t num = G.VerNum;
    int wei[num + 1];
    int ver[num + 1]; // the related vertex of w; v[num] is the start , num is end

    int p = v;

    int minVer = -1;
    int minWei = INF; // just a temp value

    // initialization
    for (int i = 1; i < num + 1; ++i)
    {
        auto ret = GraphHasEdge(G, p, i);
        if (ret.first)
        {
            wei[i] = ret.second;
            ver[i] = p;
            if (wei[i] < minWei)
            {
                minWei = wei[i];
                minVer = i;
            }
        }
        else
        {
            wei[i] = INF;
        }
    }

    visited[p] = true;

    while (minVer != -1)
    {
        visited[minVer] = true;
        GraphAddEdge(spanning, ver[minVer], minVer, wei[minVer]);
        //std::cout << "Add edge " << ver[minVer] << ' ' << minVer << std::endl;

        p = minVer;

        minVer = -1;
        minWei = INF;

        //update wei and ver by new vertex
        for (int i = 1; i < num + 1; ++i)
        {
            if (!visited[i])
            {
                auto ret = GraphHasEdge(G, p, i);
                if (ret.first)
                {
                    if (ret.second < wei[i])
                    {
                        wei[i] = ret.second;
                        ver[i] = p;
                    }
                }

                //  update minVer

                if (wei[i] < minWei)
                {
                    minWei = wei[i];
                    minVer = i;
                }
            }

        } // end of for

    } // end of while
}

// PROBLEM 6

void GraphKruskal(Graph &G, Graph &spanning, int i)
{
    // for time elapsed
    GraphPrim(G, spanning, i);
}

// PROBLEM 7
void GraphDijkstra(Graph &G, int start, int end, std::vector<int> &path)
{
    //int path[G.VerNum + 1];
    path.resize(G.VerNum + 1);
    int dis[G.VerNum + 1];

    for (int i = 1; i < G.VerNum + 1; ++i)
    {
        dis[i] = INF;
    }

    auto iter = G.VerList[start].firstEdge;

    while (iter)
    {
        //std::cout << "what's up\n";
        if (iter->eInfo < dis[iter->adjVer])
        {
            dis[iter->adjVer] = iter->eInfo;
            path[iter->adjVer] = start;
            //std::cout << "start to " << iter->adjVer << " " << iter->eInfo << std::endl;
        }
        iter = iter->next;
    }

    // sequence is not concerned
    for (int i = 1; i < G.VerNum + 1; ++i)
    {
        if (i == start)
        {
            //std::cout << "skip start\n";
            continue;
        }
        //std::cout << "big for " << i << "\n";

        auto edgeIter = G.VerList[i].firstEdge;

        while (edgeIter)
        {
            if (edgeIter->eInfo + dis[i] < dis[edgeIter->adjVer])
            {
                //std::cout << "update dis to " << edgeIter->adjVer << std::endl;
                //std::cout << "dis = " << dis[edgeIter->adjVer] << std::endl;
                dis[edgeIter->adjVer] = edgeIter->eInfo + dis[i];
                path[edgeIter->adjVer] = i;
            }
            edgeIter = edgeIter->next;
        }
    }

    path.push_back(dis[end]);
}

void GraphPrintPath(const std::vector<int> &path, int start, int end)
{
    for (auto &x : path)
    {
        std::cout << x << ' ';
    }
}

void GraphFloyd(Graph &G, int dis[], int path[])
{
    int num = G.VerNum + 1;

    //sizeof them is G.VerNum^2
    auto d = [num, dis](int x, int y) -> int & {
        return dis[x * num + y];
    };

    auto p = [num, path](int x, int y) -> int & {
        return path[x * num + y];
    };

    for (int i = 1; i < num; ++i)
    {
        for (int j = 1; j < num; ++j)
        {
            for (int m = 1; m < num; ++m)
            {
                if (d(i, j) > d(i, m) + d(m, j))
                {
                    d(i, j) = d(i, m) + d(m, j);
                }
            }
        }
    }

    for (int i = 1; i < num; ++i)
    {
        for (int j = 1; j < num; ++j)
        {
            if (i == j)
            {
                d(i, j) = 0;
                continue;
            }
            std::vector<int> temp;
            GraphDijkstra(G, i, j, temp);
            d(i, j) = temp.back();
        }
    }
}

void GraphTop(Graph &G, std::vector<int> &seq)
{
    int num = G.VerNum + 1;

    seq.clear();

    int inDeg[num];

    std::memset(static_cast<void *>(inDeg), 0, sizeof(inDeg));

    std::vector<int> zeroDegVers;

    for (int i = 1; i < num; ++i)
    {
        auto edgeIter = G.VerList[i].firstEdge;
        while (edgeIter)
        {
            inDeg[edgeIter->adjVer]++;
            edgeIter = edgeIter->next;
        }

        if (inDeg[i] == 0)
        {
            zeroDegVers.push_back(i);
        }
    }

    while (!zeroDegVers.empty())
    {
        int c = zeroDegVers.back();
        zeroDegVers.pop_back();
        seq.push_back(c);

        auto edgeIter = G.VerList[c].firstEdge;

        while (edgeIter)
        {
            inDeg[edgeIter->adjVer]--;
            if (inDeg[edgeIter->adjVer] == 0)
            {
                zeroDegVers.push_back(edgeIter->adjVer);
            }
            edgeIter = edgeIter->next;
        }
    }
}

void GraphKeyPath(Graph &G)
{
}

#endif // _GRAPH_H