//
// Created by prwang on 2017/5/30.
//
#ifndef SINGLEFILE
#include "main.h"
#include "ewls.h"
#include "numvc.h"
#endif

bool allow_run = true;


struct semaphore
{
    void P(int dlt = 1)
    {
        boost::unique_lock<boost::mutex> lock(mtx);
        cv.wait(lock, [=] { return count > 0; });
        count -= dlt;
    }
    void V(int dlt = 1)
    {
        boost::unique_lock<boost::mutex> lock(mtx);
        count += dlt;
        cv.notify_all();
    }
    semaphore(int dlt = 0) : count(dlt){}
private:
    boost::mutex mtx;
    boost::condition_variable cv;
    long count;
} message, perm_serve, finishslv, finishmst, perm_accept;

int hint, n, m, msg, changed, anspresent;
const int IT_NO_DISTURB = 1048576;

unord<maxn> ans_glb, mis;
void worker_thrs(numvc * solver)
{
    for (int ts = 1; allow_run; ++ts) {
        if (solver->iterate(ts)) {
            perm_serve.V();
            perm_accept.P();
            msg = 1;
            message.V();
            if (solver->ans.size() < anspresent)
            {
                solver->validate(mis);
                ans_glb = solver->ans;
                changed = true;
            } else changed = false;
            finishslv.V();
            finishmst.P();
        } else if (ts % IT_NO_DISTURB == 0)
        {
            perm_serve.V();
            perm_accept.P();
            msg = 0;
            message.V();
            if (solver->ans.size() > anspresent)
                solver->reset(ans_glb);
            finishslv.V();
            finishmst.P();
        }
    }
}
int main(int argc, char **argv)
{

    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    assert(argc >= 4);
    FILE* f = fopen(argv[1], "r");
    hint = atoi(argv[2]);
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
    int nthrs = atoi(argv[3]);
    anspresent = 0x3f3f3f3f;
    vector<boost::thread*> th_p;
    double gamma = .5, rho = .3;
    if (argc >= 5) gamma = atof(argv[4]);
    if (argc >= 6) rho = atof(argv[5]);
    for (int i = 0; i < nthrs; ++i)
        th_p.push_back(new boost::thread(boost::bind(worker_thrs, new numvc(n, m, conn,
                                                                            gamma * n, rho))));
    while (allow_run)
    {
        perm_serve.P();
        perm_accept.V();
        message.P();
        finishslv.P();
        if (msg && changed)
        {
            anspresent = ans_glb.size();

            int anssize = mis.size();
            printf("%d,, ", anssize);
            for (int x : mis) printf("%d,", x);
            puts(""); fflush(stdout);
            fprintf(stderr, "\n\tans=%d \n\t elapsed %.6f seconds\t", anssize,   duration_cast<duration<double>>((high_resolution_clock::now() - t1)).count());
            if (anssize == hint) allow_run = false;
        }
        finishmst.V();
    }
    for (auto x : th_p) x->join();
}
