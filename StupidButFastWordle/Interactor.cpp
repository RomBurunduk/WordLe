#pragma once

#include "Init.cpp"
#include <vector>
#include <iostream>
#include <set>
#include <bitset>

using namespace std;

struct Interactor {
    Word ans;

    Interactor(Word ans) { this->ans = ans; }
    Interactor() {}

    int num_queries = 0;

    vector<pair<char, bitset<WORD_LEN>>> Query(Word s) {
        num_queries++;
        //cout << "Query num: " << num_queries << ' ' << s.s << endl;
        vector<pair<char, bitset<WORD_LEN>>> res;
        for(int i = 0;i < WORD_LEN;i++) {
            if(ans[i] == s[i]) {
                must[s[i]].insert(i);
                for(int j = 0;j < 32;j++) {
                    if(j != s[i]) {
                        state[j] &= ALL ^ bitset<WORD_LEN>(1 << i);
                    }
                }

            } else if(ans.find(s[i]) != string::npos) {
                res.push_back({s[i], ALL ^ (bitset<WORD_LEN>(1 << i))});
            } else {
                res.push_back({s[i], bitset<WORD_LEN>()});
            }
        }
        return res;
    }

};