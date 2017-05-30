//
// Created by prwang on 2017/5/29.
//

#ifndef MAXCLIQUE_NUMVC_H
#define MAXCLIQUE_NUMVC_H


#include "mvc_solver.h"

class numvc : public mvc_solver
{
    bool conf[maxn]; int tot_wgt; //FIXME 可能溢出?
    double gamma, rho;
public:
    numvc(int _p_c, int _ed_c, pii* conn, double _gamma, double _rho);
    numvc(){}

    bool iterate(int _timest_) override;
};


#endif //MAXCLIQUE_NUMVC_H
