//
// Created by prwang on 17-5-28.
//

#include "mis_solver.h"
mis_solver::mis_solver(int _p_c, int _ed_c, pii* _conns) : p_c(_p_c), ed_c(_ed_c)
{
    for (int i = 1; i <= _p_c; ++i)
        for (int j = 1; j <= _p_c; ++j) G[i][j] = nullptr;
    for (int i = 0; i < _ed_c; ++i)
    {
        int u, v; tie(u, v) = conns[i] = _conns[i];
        wgt[G[u][v] = G[v][u] = i] = 1;
    }
    for (int i = 1, j, k; i <= _p_c; ++i)
    {
        for (j = 1; j <= _p_c && !G[i][j]; ++j);
        first[i] = j;
        is_in_curans[i] = true; curans.push_back(i);
        for (; j <= _p_c; j = k)
        {
            for (k = j; k <= _p_c && !G[i][k]; ++k);
            nxt[i][j] = k;
        }
    }
    for (int i = 0; i < _ed_c; ++i) uncovered.push_back(i);
    init_dscore();

    construct();
}
void mis_solver::init_dscore()
{
    for (int u = 1; u <= p_c; ++u)
    {
        for (int v = first[u]; v != p_c + 1; v = nxt[u][v])
        {
            switch( (int)is_in_curans[u] << 1 | is_in_curans[v])
            {
                case 0:
                    break;
                default : break;
            }
        }
    }

}
void mis_solver::construct()
{
    using pip =  tuple<int, int*>;
    static pip cnt_sorted[maxn];
    static int  cnt[maxn];
    if (uncovered.size() == 0) return void(curans = partialans);
    for (int i = 1; i <= p_c; ++i) cnt_sorted[i] = make_tuple(i, &(cnt[i] = 0));

    for (int x : uncovered) ++cnt[get<0>(conns[x])], ++cnt[get<1>(conns[x])];
    sort(cnt_sorted + 1, cnt_sorted + p_c + 1, [](auto a, auto b) { return *get<1>(b) < *get<1>(a); });
    curans = partialans;

    for (pip* p = cnt_sorted + 1; p <= cnt_sorted + p_c; --p) if (*get<1>(*p))
        for (int u = get<0>(*p), v = first[u]; v != p_c + 1; v = nxt[u][v])
        {
             curans.push_back(G[u][v]);
            --cnt[u]; --cnt[v];
        }
}
