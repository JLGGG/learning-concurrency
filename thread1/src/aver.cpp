#include <thread>
#include <numeric>
#include <vector>
#include <iostream>
#include <fmt/core.h>

using namespace std;

void PartialSum(vector<double>::iterator start, vector<double>::iterator end, double *res) {
    *res = 0;
    for (auto i = start; i < end; i++) {
        *res += *i;
    }
}

int main(int argc, char **argv) {
    int num_thr = atoi(argv[1]);
    int N = atoi(argv[2]);
    int step = (int)ceil(N*1.0/num_thr);
    double res[num_thr];

    vector<double> data(N);
    iota(data.begin(), data.end(), 1);
    thread *thr[num_thr];
    vector<double>::iterator local_start = data.begin();
    vector<double>::iterator local_end;
    for (int i = 0; i < num_thr; i++) {
        local_end = local_start + step;
        if (i == num_thr - 1) local_end = data.end();
        thr[i] = new thread(PartialSum, local_start, local_end, res+i);
        local_start += step;
    }

    double total = 0;
    for (int i = 0; i < num_thr; i++) {
        thr[i]->join();
        delete thr[i];
        total += res[i];
    }

    // cout << "Average is: " << total/N << endl;
    fmt::print("Average is: {}\n", total/N);
}