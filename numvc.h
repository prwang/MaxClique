//
// Created by prwang on 2017/5/29.
//

#ifndef MAXCLIQUE_NUMVC_H
#define MAXCLIQUE_NUMVC_H


#include "mis_solver.h"

class numvc : protected mis_solver
{
    bool conf[maxn];

public:
    numvc(int _p_c, int _ed_c, pii* conn);

    void iterate() override;
};


#endif //MAXCLIQUE_NUMVC_H
