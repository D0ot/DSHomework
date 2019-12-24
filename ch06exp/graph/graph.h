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
    GraphDFS_Inner(G,v,visitor, pre, post);
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
    GraphBFS_Inner(G,v,visitor, pre, post);
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
int GraphEdgeInfo(Graph&G, int v, int w)
{
    auto edgeIter = G.VerList[v].firstEdge;
    while(edgeIter)
    {
        if(edgeIter->adjVer == w)
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

    EdgeNode* temp = new EdgeNode;

    temp->adjVer = w;
    temp->eInfo = info;
    temp->next = nullptr;

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
    for(int i = 1; i < G.VerNum + 1; ++i)
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
            GraphAddEdge(spanning, last, v, GraphEdgeInfo(G, last, v));// 0 is not right..., to make it right, do a search on G
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
void GraphBFSTreeSpanning(Graph&G, Graph &spanning)
{
    spanning.gKind = G.gKind;
    spanning.VerNum = G.VerNum;

    for(int i = 1; i < G.VerNum + 1; ++i)
    {
        spanning.VerList[i].data = G.VerList[i].data;
        spanning.VerList[i].firstEdge = nullptr;
    }

    std::queue<int> qu;

    GraphIterFun pre = [&qu, &spanning](Graph&G, int v)
    {
        if(qu.empty())
        {
            qu.push(v);
        }else
        {
            int last = qu.front();
            //std::cout << "Add edge " << G.VerList[last].data << " to " << G.VerList[v].data << std::endl;
            GraphAddEdge(spanning, last, v, GraphEdgeInfo(G, last, v));// 0 is not right,...
            spanning.ArcNum += 1;
            qu.push(v);
        }
    };

    GraphIterFun post = [&qu, &spanning](Graph&G, int v)
    {
        qu.pop();
    };

    GraphClearVisited();
    for(int i = 1; i < G.VerNum + 1; ++i)
    {
        GraphBFS_Inner(G, i, doNothing, pre, post);
    }


}


// PROBLEM 5

auto GraphHasEdge(Graph&G, int v, int w)
{
    auto edgeIter = G.VerList[v].firstEdge;
    while(edgeIter)
    {
        if(edgeIter->adjVer == w)
        {
        }
        edgeIter = edgeIter->next;
    }

    return 0;

}


void GraphPrim(Graph&G, Graph&spanning, int v)
{
    GraphClearVisited();
    size_t num = G.VerNum;
    int w[num+1];
    int ver[num+1]; // the related vertex of w; v[num] is the start , num is end

    int start = v;








}


// PROBLEM 6

void GraphKruskal(Graph&G, Graph&spanning)
{

}


void GraphDijkstra(Graph&G)
{

}


#endif // _GRAPH_H