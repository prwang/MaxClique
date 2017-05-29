#include "main.h"
#include "ewls.h"
#include "numvc.h"

mt19937 RAND((random_device()) ());


bool allow_run = true;

int main(int argc, char **argv)
{

    int n, m;
    freopen("frb30-15-1.mis", "r", stdin);
    scanf("%*s%*s%d%d", &n, &m);
    static pii conn[maxn * maxn];
    for (int i = 0; i < m; ++i) scanf("%*s%d%d", &get<0>(conn[i]), &get<1>(conn[i]));
    mvc_solver *solver(new numvc(n, m, conn));
    unique_ptr<mvc_solver> __solver__(solver);
    signal(SIGINT, [](int x)
    {
        fprintf(stderr, "intruppting...");
        allow_run = false;
    });
    for (int ts = 1; allow_run; ++ts)
        if (solver->iterate(ts))
        {
            solver->validate();
            printf("%d,, ", solver->mis.size());
            for (int x : solver->mis) printf("%d,", x);
            puts("");
        }



}