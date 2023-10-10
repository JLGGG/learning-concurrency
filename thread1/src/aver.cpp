#include <thread>
#include <numeric>
#include <vector>
#include <iostream>
#include <memory>
#include <fmt/core.h>

using namespace std;

struct PartialSumFunctor {
    vector<double>::iterator start;
    vector<double>::iterator end;
    double res = 0;

    void operator() ();
};

void PartialSumFunctor::operator() () {
    for (auto i = start; i < end; i++) {
        res += *i;
    }
}

int main(int argc, char **argv) {
    int num_thr = atoi(argv[1]);
    int N = atoi(argv[2]);
    int step = (int)ceil(N*1.0/num_thr);
    // double res[num_thr];

    vector<double> data(N);
    iota(data.begin(), data.end(), 1);
    // thread *thr[num_thr];
    unique_ptr<thread> thr[num_thr-1];
    PartialSumFunctor f[num_thr];
    vector<double>::iterator local_start = data.begin();
    vector<double>::iterator local_end;
    for (int i = 0; i < num_thr - 1; i++) {
        local_end = local_start + step;
        f[i].start = local_start;
        f[i].end = local_end;
        thr[i] = make_unique<thread>(ref(f[i]));
        local_start += step;
    }

    f[num_thr - 1].start = local_start;
    f[num_thr - 1].end = data.end();
    f[num_thr - 1]();

    double total = f[num_thr - 1].res;
    for (int i = 0; i < num_thr-1; i++) {
        thr[i]->join();
        total += f[i].res;
    }

    // cout << "Average is: " << total/N << endl;
    fmt::print("Average is: {}\n", total/N);
}