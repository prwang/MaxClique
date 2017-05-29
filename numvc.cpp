//
// Created by prwang on 2017/5/29.
//

#include "numvc.h"

numvc::numvc(int _p_c, int _ed_c, pii* conn) : mis_solver(_p_c, _ed_c, conn)
{
    for (int i = 1; i <= p_c; ++i)
        conf[i] = true;
}
