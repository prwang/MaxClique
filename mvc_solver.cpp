//
// Created by prwang on 17-5-28.
//

#include "mvc_solver.h"

mvc_solver::mvc_solver(int _p_c, int _ed_c, pii *_conns) : p_c(_p_c), ed_c(_ed_c)
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
    for (int i = 0; i < _ed_c; ++i) uncov.ins(i);
    construct();
    partial = ans;
    init_dscore();
}

void mvc_solver::init_dscore()
{
    for (int u = 1; u <= p_c; ++u)
        for (int v : adj[u])
        {
            int val = wgt[G[u][v]];
            switch ((int) partial(u) << 1 | partial(v))
            {
            case 0:dsc[u] += val;
                dsc[v] += val;
                break;
            case 1: dsc[u] -= val;
                break;
            case 2: dsc[v] -= val;
            default : break;
            }
        }
}


void mvc_solver::construct()
{
    using pip =  tuple<int, int *>;
    static pip cnt_sorted[maxn];
    static int cnt[maxn];
    if (uncov.size() == 0) return void(ans = partial);
    for (int i = 1; i <= p_c; ++i) cnt_sorted[i] = make_tuple(i, &(cnt[i] = 0));
    for (int x : uncov) ++cnt[get<0>(conns[x])], ++cnt[get<1>(conns[x])];
    sort(cnt_sorted + 1, cnt_sorted + p_c + 1, [](auto a, auto b) { return *get<1>(b) < *get<1>(a); });
    ans = partial;
    int u;
    for (pip *p = cnt_sorted + 1; p <= cnt_sorted + p_c; --p)
        if (u = *get<1>(*p))
            for (int v : adj[u])
            {
                ans.ins(G[u][v]);
                --cnt[u];
                --cnt[v];
            }
}

#define CHG(op1, op2)    c_d[u] = timest; partial.op1(u); dsc[u]  = -dsc[u]; for (int v : adj[u]) if (!partial(v)) uncov.op2(G[u][v]);

void mvc_solver::ins_pans(int u) { CHG(ins, del); }

void mvc_solver::del_pans(int u) { CHG(del, ins); }

int mvc_solver::max_oldest()
{
    int pt = INT_MIN, pt2 = -1, i = -1;
    for (int x : partial)
        if (c_d[x] < timest - 1 &&
            (dsc[x] > pt || (dsc[x] == pt && pt2 > c_d[x])))
            pt = dsc[i = x], pt2 = c_d[i];
    return i;
}

void mvc_solver::validate()
{
    mis = unord<maxn>();
    for (int i = 1; i <= p_c; ++i)
        if (!ans(i)) mis.ins(i);
    for (int x : mis)
        for (int y : mis)
            if (G[x][y]) throw 233;
}
