//
// Created by prwang on 2017/5/29.
//

#pragma once
#ifndef SINGLEFILE
#include "mvc_solver.h"
#endif

class numvc : public mvc_solver
{
    bool conf[maxn]; int tot_wgt; //FIXME 可能溢出?
    double gamma, rho;
public:
    numvc(int _p_c, int _ed_c,  const pii* conn, double _gamma, double _rho);
    numvc(){}
    void check();

    bool iterate(int _timest_) override;
};


