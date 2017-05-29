//
// Created by prwang on 17-5-28.
//

#include "mis_solver.h"

mis_solver::mis_solver(int _p_c, int _ed_c, pii *_conns) : p_c(_p_c), ed_c(_ed_c)
{
    for (int i = 1; i <= _p_c; ++i)
        for (int j = 1; j <= _p_c; ++j) G[i][j] = p_c + 1;
    for (int i = 0; i < _ed_c; ++i)
    {
        int u, v;
        tie(u, v) = conns[i] = _conns[i];
        wgt[G[u][v] = G[v][u] = i] = 1;
        adj[u].ins(v);
        adj[v].ins(u);

    }
    for (int i = 0; i < _ed_c; ++i)  uncov.ins(i);
    construct();
    partialans = curans;
    remove_one();
    init_dscore();
}

void mis_solver::init_dscore()
{
    for (int u = 1; u <= p_c; ++u)
        for (int v : adj[u])
        {
            int val = wgt[G[u][v]];
            switch ((int) partialans(u) << 1 | partialans(v))
            {
            case 0:dscore[u] += val;
                dscore[v] += val;
                break;
            case 1: dscore[u] -= val;
                break;
            case 2: dscore[v] -= val;
            default : break;
            }
        }
}

void mis_solver::construct()
{
    using pip =  tuple<int, int *>;
    static pip cnt_sorted[maxn];
    static int cnt[maxn];
    if (uncov.size() == 0) return void(curans = partialans);
    for (int i = 1; i <= p_c; ++i) cnt_sorted[i] = make_tuple(i, &(cnt[i] = 0));
    for (int x : uncov) ++cnt[get<0>(conns[x])], ++cnt[get<1>(conns[x])];
    sort(cnt_sorted + 1, cnt_sorted + p_c + 1, [](auto a, auto b) { return *get<1>(b) < *get<1>(a); });
    curans = partialans;  int u;
    for (pip *p = cnt_sorted + 1; p <= cnt_sorted + p_c; --p) if (u = *get<1>(*p))
            for (int v : adj[u]) { curans.ins(G[u][v]); --cnt[u]; --cnt[v]; }
}
void mis_solver::ins_pans(int u)
{
    partialans.ins(u);
    dscore[u]  = -dscore[u];
    for (int x : adj[u])
    {

    }
}
