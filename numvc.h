//
// Created by prwang on 2017/5/29.
//

#ifndef MAXCLIQUE_NUMVC_H
#define MAXCLIQUE_NUMVC_H


#include "mvc_solver.h"

class numvc : public mvc_solver
{
    bool conf[maxn];

public:
    numvc(int _p_c, int _ed_c, pii* conn);

    bool iterate(int _timest_) override;
};


#endif //MAXCLIQUE_NUMVC_H
