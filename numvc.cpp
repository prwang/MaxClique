//
// Created by prwang on 2017/5/29.
//

#include "numvc.h"

numvc::numvc(int _p_c, int _ed_c, pii* conn, double _gamma, double _rho)
        : mvc_solver(_p_c, _ed_c, conn), tot_wgt(0), gamma(_gamma), rho(_rho)
{
    for (int i = 1; i <= p_c; ++i) conf[i] = true;
    for (int i = 0; i < ed_c; ++i) tot_wgt += wgt[i];
}

bool numvc::iterate(int _timest_)
{
    bool is_full = mvc_solver::iterate(_timest_);
    if (uncov.size()  == 0) ans = partial, is_full = true;
    int u = max_oldest(), v;
    del_pans(u);
    conf[u] = false;
    for (int x : adj[u]) conf[x] = true;
    if (is_full) return true;

    tie(u, v) = conns[uncov.rand()];
    if (!conf[u] || (conf[v] && (dsc[v] > dsc[u] || (dsc[v] == dsc[u] && c_d[v] < c_d[u])))) swap(u, v);
    ins_pans(u);
    for (int x : adj[u]) conf[x] = true;
    for (int e : uncov)
    {
        ++wgt[e]; ++tot_wgt;
        tie(u, v) = conns[e];
        dsc_modify(u, v, 1);
    }
    if (tot_wgt  >= gamma * ed_c)
        for (int e : uncov)
        {
            int de = int(rho * wgt[e]) - wgt[e];
            wgt[e] += de; tot_wgt -= de;
            tie(u, v) = conns[e];
            dsc_modify(u, v, de);
        }

    return false;
}
