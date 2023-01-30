#pragma once

#include "Interactor.cpp"
#include <iostream>

using namespace std;

struct Player {

    string hashQ = "";

    void ask(Interactor& inter, Word s) {
        array<char, 5> ans = inter.Query(s);
        // cout << "query: " << translate[s.word] << endl;

        // for(int i = 0;i < ans.size();i++) {
        //     cout << (int)(ans[i]);
        // }
        // cout << endl;

        array<int, 32> letterCount;
        fill(letterCount.begin(), letterCount.end(), 0);
        for(int i = 0;i < WORD_LEN;i++) {
            hashQ += to_string((int)(ans[i]));
            if(ans[i] != 0)
                letterCount[s[i]]++;
        }

        for(int i = 0;i < 32;i++)
            letterCountInAnswer[i] = max(letterCount[i], letterCountInAnswer[i]);

        for(int i = 0;i < WORD_LEN;i++) {
            if(ans[i] == 1) {
                must[s[i]].insert(i);
                for(int j = 0;j < 32;j++) {
                    state[j] &= ALL ^ bitset<5>(1 << i);
                }
            }
        }

        for(int i = 0;i < WORD_LEN;i++) {
            if(ans[i] == 0) {
                letterCountInAnswer[s[i]] = letterCount[s[i]];
                state[s[i]] &= ALL ^ bitset<5>(1 << i);
                //state[s[i]] &= ALL ^ bitset<5>(1 << (rand() % 5));
            }
        }

        for(int i = 0;i < WORD_LEN;i++) {
            if(ans[i] == 2) {
                state[s[i]] &= ALL ^ bitset<5>(1 << i);
            }
        }

        for(int i = 0;i < 32;i++)
            for(auto pos : must[i])
                state[i] |= bitset<5>(1 << pos);
    }
};
