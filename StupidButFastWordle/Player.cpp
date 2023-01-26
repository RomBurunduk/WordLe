#pragma once

#include "Interactor.cpp"
#include <iostream>

using namespace std;

struct Player {
    void ask(Interactor& inter, Word s) {
        vector<pair<char, bitset<5>>> res = inter.Query(s);
        //cout << "query: " << translate[s].s << endl;
        for(auto e : res) {
            //cout << alph.substr(e.first * 2, 2) << ' ' << e.second << endl;
            state[e.first] &= (e.second); 
            //cout << alph.substr(e.first * 2, 2) << ' ' << state[e.first] << endl;
        }
    }
};
