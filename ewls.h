//
// Created by prwang on 17-5-28.
//

#ifndef MAXCLIQUE_EWLS_H
#define MAXCLIQUE_EWLS_H


#include "mvc_solver.h"

class ewls : public mvc_solver
{
    int dlt;
public:
    ewls(int _dlt, int n, int m, pii* conn) : dlt(_dlt),  mvc_solver(n, m, conn) {}
};


#endif //MAXCLIQUE_EWLS_H
