#include <iostream>

#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include "data_load.cpp"

#define rep(i, a, b) for (int i = (a); i < (int) (b); ++i)
#define trav(it, v) for (auto& it : v)

typedef unsigned long long ull;

using namespace std;

const string file_name("../data/d.txt");
ull sol = 2999434ULL;

static void BM_vector_solution(benchmark::State &state) {

    volatile ull tot = 0;
    auto input = load_as_vector(file_name);
    int q = input.first; // number of users
    vector<vector<bool>> &input_data = input.second;

    for (auto _ : state) {
        bool not_friend;
        ull cnt = 0; // email to send
        rep(i, 0, q) { // from these friends
            rep(j, i + 1, q) { // to these friends
                not_friend = !input_data[i][j];
                if (not_friend) {
                    bool flag = false;
                    rep(c, 0, q) {
                        flag = input_data[i][c] & input_data[j][c];
                        if (flag) {
                            cnt++;
                            break;
                        }
                    }
                }
            }
        }
        assert((cnt << 1) == sol);
        tot += (cnt << 1);
    }


}

BENCHMARK(BM_vector_solution);


static void BM_bitset_solution(benchmark::State &state) {
    volatile ull tot = 0;
    auto input = load_as_bitset(file_name);
    int q = input.first;
    auto &input_data = input.second;

    for (auto _ : state) {
        bool not_friend = false;
        ull cnt = 0;

        rep(i, 0, q) { // from these friends
            rep(j, i + 1, q) { // to these friends
                not_friend = !input_data[i][j];
                if (not_friend) {
                    bitset<2000> common_friends = input_data[i] & input_data[j];
                    if (common_friends.any())
                        cnt += 1;
                }
            }
        }
        assert((cnt << 1) == sol);
        tot += (cnt << 1);
    }

}

BENCHMARK(BM_bitset_solution);


static void BM_packed_ull_solution(benchmark::State &state) {
    volatile ull tot = 0;
    auto input = load_as_packed_ull(file_name);
    int q = input.first;
    auto &input_data = input.second;

    for (auto _ : state) {
        bool not_friend = false;
        ull cnt = 0;
        int size_arr = (int) input_data[0].size();

        rep(i, 0, q) { // from these friends
            rep(j, i + 1, q) { // to these friends
                int step = j >> 6; // same as j / 64
                int remainder = j % 64;

                not_friend = (input_data[i].at(step) >> remainder) % 2 == 0;
                if (not_friend) {
                    ull counter = 0;

                    vector<ull> &v1 = input_data[i];
                    vector<ull> &v2 = input_data[j];

                    for (int c = 0; c < size_arr; ++c) {
                        counter |= v1[c] & v2[c];
                    }

                    if (counter != 0)
                        cnt++;
                }
            }
        }
        assert((cnt << 1) == sol);
        tot += (cnt << 1);
    }

}

BENCHMARK(BM_packed_ull_solution);

BENCHMARK_MAIN();