#include "main.h"
#include "ewls.h"
#include "numvc.h"

mt19937 RAND((random_device()) ());


bool allow_run = true;

numvc solver;
int main(int argc, char **argv)
{
    using namespace std::chrono;
    time_point t1 = high_resolution_clock::now();
    int n, m;
    assert(argc == 2);
    FILE* f = fopen(argv[1], "r");
    int hint = atoi(argv[2]);
    fscanf(f, "%*s%*s%d%d", &n, &m);
    static pii conn[maxn * maxn];
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        fscanf(f, "%*s%d%d",  &x, &y);
        if (x == y) --i;
        else conn[i] = make_tuple(x, y);
    }
    sort(conn, conn + m); m = int(unique(conn, conn + m) - conn);
    random_shuffle(conn, conn + m, [](int range) { return (uniform_int_distribution<int>(0, range - 1))(RAND); });

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
            int anssize = solver.mis.size();
            printf("%d,, ", anssize);
            for (int x : solver.mis) printf("%d,", x);
            puts(""); fflush(stdout);
            fprintf(stderr, "\nans=%d ts = %d elapsed %.6f seconds", anssize,  ts, duration_cast<duration<double>>((high_resolution_clock::now() - t1)).count());
            if (anssize == hint) allow_run = false;
        }
}