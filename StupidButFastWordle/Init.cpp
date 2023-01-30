#pragma once

#include <iostream> 
#include <fstream>
#include <ctime>
#include <bitset>
#include <set>
#include <array>
#include <map>
#include <vector>
#include "Word.cpp"

using namespace std;


array<bitset<5>, 32> state;
array<int, 32> letterCost;
array<set<int>, 32> must;
array<int, 32> letterCountInAnswer;

map<ll, string> translate;

bitset<5> ALL = 0b11111;
const int NOT_FOUND = -1;
const int WRONG_PLACE = -2;
const int WORD_LEN = 5;
const int HASH_SIZE = 3;

vector<Word> all;
string alph{"абвгдежзийклмнопрстуфхчцщшъыьэюя"};

void ReadDict() {
    string s;

    map<string, int> mp;
    for(int i = 0;i < alph.length() / 2;i++) {
        mp[alph.substr(2 * i, 2)] = i;
    }   

    while(cin >> s) {
        string t = "";
        for(int i = 0;i < s.length() / 2;i++)
            t.push_back((char)(mp[s.substr(2 * i, 2)]));
        
        translate[Word(t).word] = s;
        all.push_back(Word(t));
    }
    
}
