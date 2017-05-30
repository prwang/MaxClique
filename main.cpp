#include "main.h"
#include "ewls.h"
#include "numvc.h"

mt19937 RAND((random_device()) ());


bool allow_run = true;

numvc solver;
int main(int argc, char **argv)
{

    int n, m;
    freopen("frb30-15-1.mis", "r", stdin);
    scanf("%*s%*s%d%d", &n, &m);
    static pii conn[maxn * maxn];
    for (int i = 0; i < m; ++i) scanf("%*s%d%d", &get<0>(conn[i]), &get<1>(conn[i]));
    sort(conn, conn + m); m = int(unique(conn, conn + m) - conn);

    new(&solver) numvc(n, m, conn, .5 * n, .3);
    signal(SIGINT, [](int x)
    {
        fprintf(stderr, "intruppting...");
        allow_run = false;
    });
    for (int ts = 1; allow_run; ++ts)
        if (solver.iterate(ts))
        {
            solver.validate();
            printf("%d,, ", solver.mis.size());
            for (int x : solver.mis) printf("%d,", x);
            puts("");
        }
}