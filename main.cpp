#include "main.h"
#include "ewls.h"

mt19937 RAND((random_device())());


void calcds();
void construct();
typedef tuple<int, int> pii;
pii exchange();
int main(int argc, char** argv)
{
    assert(argc == 3);
    int maxstep = atoi(argv[1]), dlt = atoi(argv[2]);
    int n, m;
    scanf("%*s%*s%d%d", &n, &m);
    static pii conn[maxn * maxn];
    for (int i = 0; i < m; ++i) scanf("%*s%d%d", &get<0>(conn[i]), &get<1>(conn[i]));
    ewls* solver (new ewls(n, m, conn)); unique_ptr<ewls> __solver__(solver);
    solver->solve(maxstep, dlt);

}