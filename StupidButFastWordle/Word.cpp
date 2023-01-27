#pragma once

#include "Util.cpp"
#include <string>

using namespace std;

using ll = long long;

struct Word {
    ll word = 0;
    array<char, 32> count;

    Word() {};

    Word(string s) {
        fill(count.begin(), count.end(), 0);
        for(int i = 0;i < 5;i++)
            count[GetByte(s[i], 0)]++, word |= GetByte(s[i], 0) << (8 * i);
    }

    ll GetSymb(int pos) {
        return GetByte(word, pos);
    }

    ll operator[](int i) {
        return GetSymb(i);
    }

    size_t find(int symb) {
        for(int i = 0;i < 5;i++)
            if(GetSymb(i) == symb)
                return i;
        
        return string::npos;
    }

    bool operator!=(Word oth) { return oth.word != word; }

    bool operator<(Word oth) { return oth.word < word; }
};