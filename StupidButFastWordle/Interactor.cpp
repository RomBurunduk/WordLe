#pragma once

#include "Init.cpp"
#include <vector>
#include <iostream>
#include <set>
#include <bitset>

using namespace std;

struct Interactor {
    Word ans;
    array<char, 32> count;

    Interactor(Word ans) { 
        this->ans = ans;
        fill(count.begin(), count.end(), 0);
        for(int i = 0;i < WORD_LEN;i++)
            count[ans[i]]++;
    }

    Interactor() {}

    int num_queries = 0;

    //color[i] == 1 -> ith card is green
    //color[i] == 2 -> ith card is yellow
    //color[i] == 0 -> ith card is gray
    array<char, 5> Query(Word s) {
        array<char, 5> color = {0, 0, 0, 0, 0};
        array<char, 32> count = this->count;

        for(int i = 0;i < WORD_LEN;i++) {
            if(ans[i] == s[i]) {
                color[i] = 1;
                count[s[i]]--;
            }
        }
        for(int i = 0;i < WORD_LEN;i++) {
            if(count[s[i]] != 0 && color[i] != 1) {
                color[i] = 2;
                count[s[i]]--;
            } else if(color[i] != 1) {
                color[i] = 0;
            } 
        }

        return color;
    }

};