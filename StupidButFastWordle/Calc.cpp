#include <iostream> 
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "Init.cpp"
#include "Interactor.cpp"
#include "Player.cpp"

using namespace std;

vector<int> toAsk = {3583, 2215, 334};

string CalcWord(Word w, vector<int> to_ask) {
    Interactor iter(w);
    Player p;

    string s = "";
    for(auto e : to_ask) {
        auto ans = iter.Query(all[e]);
        for(auto ch : ans)
            s += to_string((int)(ch));
    }

    return s;
}

vector<string> PrecalcAll(vector<int> to_ask) {
    vector<string> hashes(all.size());
    int c = 0;
    for(auto e : all)
        hashes[c++] = CalcWord(e, to_ask);

    return hashes;
}

int f(vector<int> to_ask) {
    auto hash = PrecalcAll(to_ask);

    map<string, int> used;

    int good = hash.size() * (hash.size() - 1) / 2;
    for(int i = 0;i < hash.size();i++)
        good -= used[hash[i]], used[hash[i]]++;
    
    return good;
}

double rnd() {
    return rand() / (double)RAND_MAX;
}

double chance(double y, double x, double t) {
    return rnd() < (exp(y - x) / (t));
}

vector<int> FindBest() {
    int ans_val = 0;
    auto ans_vec = toAsk;

    auto best_vec = toAsk;

    int best_val = f(best_vec);

    double t = 1;
    while(clock() / (double)(CLOCKS_PER_SEC) < 2) {
        auto new_vec = best_vec;

        int pos = rand() % new_vec.size();
        int dlt = rand() % all.size();
        new_vec[pos] = dlt;

        int new_val = f(new_vec);
        if(best_val < new_val || chance(new_val, best_val, t)) {
            best_vec = new_vec;
            best_val = new_val;
        }

        if(best_val > ans_val) {
            ans_val = best_val;
            ans_vec = best_vec;
        }

        t *= 0.994;
        if(t < 0.001) {
            t = 1;
        }
    }

    return ans_vec;
}

