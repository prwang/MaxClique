//
// Created by prwang on 17-5-28.
//

#include "main.h"
#ifndef MAXCLIQUE_GRAPH_H
#define MAXCLIQUE_GRAPH_H


class mis_solver
{
protected:
    int G[maxn][maxn], nxt[maxn][maxn], first[maxn]; // null if no edge; else ref to ele in edge weight
    int wgt[maxn * maxn]; pii conns[maxn];
    int dscore[maxn], p_c, ed_c;

    list<int> uncovered, curans, partialans;
    bool is_in_curans[maxn];

public:
    mis_solver(int _p_c, int _ed_c, pii* _conns);
    void init_dscore();
    void construct();

    virtual void iterate() = 0;
};


#endif //MAXCLIQUE_GRAPH_H
