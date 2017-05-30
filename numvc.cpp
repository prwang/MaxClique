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
    mvc_solver::iterate(_timest_);
    if (uncov.size()  == 0)
    {
        ans = partial;
        int u = max_oldest();
        del_pans(u);
        return true;
    }
    int u = max_oldest(), v;
    del_pans(u);
    conf[u] = false;
    for (int x : adj[u]) conf[x] = true;

    tie(u, v) = conns[uncov.rand()];
    if (!conf[u] || (conf[v] && (dsc[v] > dsc[u] || (dsc[v] == dsc[u] && c_d[v] < c_d[u])))) swap(u, v);

    assert(conf[u]); ins_pans(tr = u);
    for (int x : adj[u]) conf[x] = true;
    for (int e : uncov)
    {
        ++wgt[e]; ++tot_wgt;
        tie(u, v) = conns[e];
        dsc_modify(u, v, 1);
    }
    if (tot_wgt  >= gamma * ed_c)
    {
        fprintf(stderr, "forget begin...tot wgt is%d\n", tot_wgt);
        tot_wgt = 0;
        for (int e = 0; e < ed_c; ++e) tot_wgt += wgt[e] = int(rho * wgt[e]);
        initdsc();
        fprintf(stderr, "forget end...tot wgt is%d\n", tot_wgt);
    }
    return false;
}
void numvc::check()
{
    static int dsa[maxn];
    for (int i = 1; i <= p_c; ++i) dsa[i] = dsc[i], dsc[i] = 0;
    for (int i = 0; i < ed_c; ++i)
        dsc_modify(get<0>(conns[i]), get<1>(conns[i]), wgt[i]);
    for (int i = 1; i <= p_c; ++i) if (dsc[i] != dsa[i])
                asm("int $3");
}
