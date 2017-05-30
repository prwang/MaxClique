#pragma once
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <list>
#include <memory>
#include <algorithm>
#include <random>
#include <csignal>
#include <climits>
#include <chrono>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
const int maxn = 4050, maxm = maxn * maxn;
typedef tuple<int, int> pii;
