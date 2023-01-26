#pragma once

#include "Util.cpp"
#include <string>

using namespace std;

using ll = long long;

struct Word {
    ll word = 0;

    Word() {};

    Word(string s) {
        word |= GetByte(s[0], 0) << 0;
        word |= GetByte(s[1], 0) << 8;
        word |= GetByte(s[2], 0) << 16;
        word |= GetByte(s[3], 0) << 24;
        word |= GetByte(s[4], 0) << 32;
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