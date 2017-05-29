//
// Created by prwang on 17-5-28.
//

#ifndef MAXCLIQUE_EWLS_H
#define MAXCLIQUE_EWLS_H


#include "mis_solver.h"

class ewls : public mis_solver
{
    int dlt;
public:
    ewls(int _dlt, int n, int m, pii* conn) : dlt(_dlt),  mis_solver(n, m, conn) {}
    void iterate() override;
};


#endif //MAXCLIQUE_EWLS_H
