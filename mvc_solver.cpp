//
// Created by prwang on 17-5-28.
//

#include "mvc_solver.h"
#include <ext/pb_ds/priority_queue.hpp>

template<class T> using heap = __gnu_pbds::priority_queue<T>;

mvc_solver::mvc_solver(int _p_c, int _ed_c, pii *_conns) : p_c(_p_c), ed_c(_ed_c), partial(), tr(-1)
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
    construct();
    partial = ans;
    initdsc();
}


void mvc_solver::dsc_modify(int u, int v, int val)
{
    switch ((int) partial(u) << 1 | partial(v))
    {
    case 0: dsc[u] += (val); dsc[v] += (val); break;
    case 1: dsc[v] -= (val); break;
    case 2: dsc[u] -= (val); default : break;
    }
}

void mvc_solver::construct()
{
    using pip =  tuple<int, int *>;
    static int deg[maxn];
    fill(deg + 1, deg + p_c + 1, 0);
    for (int i = 0; i < ed_c; ++i) ++deg[get<0>(conns[i])], ++deg[get<1>(conns[i])];

    static heap<pii>::point_iterator inss[maxn];
    heap<pii> Q;
    for (int i = 1; i <= p_c; ++i)
        inss[i] = Q.push(make_tuple(deg[i], i));
    ans = partial;
    while (Q.size() && get<0>(Q.top()) > 0)
    {
        int d, u;
        tie(d, u) = Q.top();
        Q.pop();
        inss[u] = Q.end();
        ans.ins(u);
        for (int v : adj[u]) if (!ans(v))
                Q.modify(inss[v], make_tuple(--deg[v], v));
    }

}


void mvc_solver::ins_pans(int u)
{

    c_d[u] = timest;
    partial.ins(u); dsc[u]  = -dsc[u];
    for (int v : adj[u])
        if (!partial(v))
            uncov.del(G[u][v]), dsc[v] -= wgt[G[u][v]];
        else dsc[v] += wgt[G[u][v]];
}
void mvc_solver::del_pans(int u)
{
    //CHG(del, ins);
    c_d[u] = timest;
    partial.del(u); dsc[u]  = -dsc[u];
    for (int v : adj[u])
        if (!partial(v))
            uncov.ins(G[u][v]), dsc[v] += wgt[G[u][v]];
        else dsc[v] -= wgt[G[u][v]];
}

int mvc_solver::max_oldest()
{
    int pt = INT_MIN, pt2 = -1, i = -1;
    for (int x : partial)
        if (x != tr &&
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
        for (int y : mis) if (G[x][y] != p_c + 1) { asm("int $3"); }
}
void mvc_solver::initdsc()
{
    for (int u = 1; u <= p_c; ++u) dsc[u] = 0;
    for (int i = 0; i < ed_c; ++i)
        dsc_modify(get<0>(conns[i]), get<1>(conns[i]), wgt[i]);
}
void mvc_solver::reset(const unord<maxn>& ans0)
{
    partial = ans = ans0;
    timest = 0; tr = -1;
    for (int i = 1; i <= p_c; ++i) c_d[i] = 0;
    for (int i = 0; i < ed_c; ++i) wgt[i] = 1;
    new(&uncov) unord<maxm>();
    initdsc();
}
