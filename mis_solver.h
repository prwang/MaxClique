//
// Created by prwang on 17-5-28.
//

#include "main.h"
#ifndef MAXCLIQUE_GRAPH_H
#define MAXCLIQUE_GRAPH_H


template<int N, int RG = N>struct unord
{
    int ary[N], rev[RG], realsize;
    int size() { return realsize; }
    int* begin() { return ary; }
    int* end() { return ary + realsize; }
    void ins(int u) { ary[rev[u] = realsize++] = u; }
    void del(int u)
    {
        int pos = rev[u]; rev[u] = -1;
        --realsize;
        if (realsize != pos)
            rev[ary[pos] = ary[realsize]] = pos;
    }
    unord()
    {
        realsize = 0;
        fill(rev, rev + RG, -1);
    }

    bool operator()(int u) { return -1 != rev[u]; } //probe if exists
};
class mis_solver
{
protected:
    int G[maxn][maxn]; //FIXME init
    int wgt[maxm]; pii conns[maxn];
    int dscore[maxn], p_c, ed_c;

    unord<maxn> adj[maxn], curans, partialans;
    unord<maxm> uncov;

    list<int>::iterator uncovered_idx[maxm];

public:
    mis_solver(int _p_c, int _ed_c, pii* _conns);
    void init_dscore();
    void construct();
    void ins_pans(int u);
    void del_pans(int v);

    virtual void iterate() = 0;
};


#endif //MAXCLIQUE_GRAPH_H
