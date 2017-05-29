//
// Created by prwang on 2017/5/29.
//

#include "numvc.h"

numvc::numvc(int _p_c, int _ed_c, pii* conn) : mis_solver(_p_c, _ed_c, conn)
{
    for (int i = 1; i <= p_c; ++i) conf[i] = true;
}

void numvc::iterate()
{
    mis_solver::iterate();

    bool is_full = false;
    if (uncov.size()  == 0) curans = partial, is_full = true;
    int u = max_oldest(), v;
    del_pans(u);
    conf[u] = false;
    for (int x : adj[u]) conf[x] = true;
    if (is_full) return;

    tie(u, v) = conns[uncov.rand()];
    if (!conf[u] || (conf[v] && (dsc[v] > dsc[u] || dsc[v] == dsc[u] && c_d[v] < c_d[u]))) swap(u, v);
    ins_pans(u);
    for (int x : adj[u]) conf[x] = true;
    for (int e : uncov)  ++wgt[e];
}
