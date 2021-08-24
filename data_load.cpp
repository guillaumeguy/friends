//
// Created by guillaume_guy on 8/24/21.
//
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define rep(i, a, b) for (int i = (a); i < (int) (b); ++i)
#define trav(it, v) for (auto& it : v)
#define all(v) (v).begin(), (v).end()

typedef unsigned long long ull;

using namespace std;

pair<int,vector <vector<bool>>> load_as_vector(string name = string("../data/d2.txt")) {
    string line;
    ifstream input_file(name);

    if (input_file.is_open()) {

        int q;
        getline(input_file, line);
        q = stoi(line);

        vector <vector<bool>> input_data(q);

        int i = 0;
        while (getline(input_file, line)) {
            input_data[i].reserve(q);
            trav(e, line)
            {
                input_data[i].push_back(e == '1');
            }
            ++i;
        }
        input_file.close();
        return make_pair(q,input_data);
    }
    cout << "file malfunction" << endl;
    throw "file malfunction";

}

pair<int,vector <bitset<2000>>> load_as_bitset(string name = string("../data/d2.txt")){
    string line;
    ifstream input_file(name);

    if (input_file.is_open()) {

        int q;
        getline(input_file, line);
        q = stoi(line);

        vector<bitset<2000>> input_data(q);

        int i = 0;
        while (getline(input_file, line)) {

            reverse(line.begin(), line.end());

            bitset<2000> t (line);
            input_data[i] = t;
            ++i;
        }
        input_file.close();
        return make_pair(q,input_data);
    }
    cout << "file malfunction" << endl;
    throw "file malfunction";


}


pair<int,vector <vector<ull>>> load_as_packed_ull(string name = string("../data/d2.txt")) {
    string line;
    ifstream input_file(name);

    if (input_file.is_open()) {

        int q;
        getline(input_file, line);
        q = stoi(line);

        vector<vector<ull>> input_data(q,vector<ull>(1 + (q-1)/64,0ULL));

        int i = 0;
        while (getline(input_file, line)) {
            rep(j,0,1 + (q-1)/64) {
                string str = line.substr(j*64,64);
                reverse(str.begin(),str.end());
                ull ul = std::stoull(str,nullptr,2);
                input_data.at(i).at(j) = ul;
            }
            ++i;
        }
        input_file.close();
        return make_pair(q,input_data);
    }
    cout << "file malfunction" << endl;
    throw "file malfunction";

}