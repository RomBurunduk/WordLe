#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream> 
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "Word.cpp"
#include "Init.cpp"
#include "Interactor.cpp"
#include "Player.cpp"

using namespace std;

Word guessedWord;
int wins;

int calc(Word s, vector<int> &rate) {
    int score = 1;
    int cnt = 0;

    vector<int> used(32, 1);
    for(int i = 0;i < WORD_LEN;i++) {
        score += sqrt(rate[s.GetSymb(i)]) * used[s.GetSymb(i)];
        used[s.GetSymb(i)] *= 0.5;
    }

    return score;
}

int check(Word s) {
    int score = 1;
    int cnt = 0;
    for(int j = 0;j < 33;j++) {
        int i = j;
        for(auto pos : must[i]) {
            if(s.GetSymb(pos) != i)
                return 0;
        }
    }

    int curr = 0;
    for(int i = 0;i < WORD_LEN;i++) {
        int c = s.GetSymb(i);
        if(state[c][curr] == 0)
            return 0;
        curr++;
        score += 5 - state[c].count();
    }

    return score;
}

void solve(Word word) {
    for(int i = 0;i < 33;i++)
        state[i] = ALL, must[i].clear();

    guessedWord = word;

    srand(time(NULL));

    Interactor inter(word);
    
    inter.ans = guessedWord;

    Player p;

    int bestPos = 1737;
    int bestScore = 0;
    for(int q = 0;q < 5;q++) {
        vector<int> rate(33);
        bestScore = 0;
        for(int i = 0;i < 33;i++) {
            rate[i] = (state[i].count()) * letterCost[i];
        }

        for(int i = 0;i < all.size();i++) {
            //if(check(all[i]) && i) continue;
            int newVal = calc(all[i], rate);
            if(bestScore < newVal) {
                bestPos = i;
                bestScore = newVal;
            }
        }
        
        p.ask(inter, all[bestPos]);
    }

    int summ = 0;
    bestPos = 0;
    bestScore = 0;
    for(int i = 0;i < all.size();i++) {
        int newVal = check(all[i]);
        summ += newVal;
        if(bestScore < newVal) {
            bestPos = i;
            bestScore = newVal;
        }
    }
    
    //cout << summ << endl;
    
    if(guessedWord != all[bestPos]) {
        wins--;
        cout << "WA: " << translate[guessedWord.word] << ", ";
        cout << "I'm think it is " << translate[all[bestPos].word] << endl; 
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    freopen("Dict.txt", "r", stdin);

    ReadDict();
    CountLetterFreq();
    wins = all.size();

    double time = clock();    

    for(auto e : all)
        solve(e);

    cout << (double)(wins) / (double)(all.size()) << endl;

    cout << (clock() - time) / (double)CLOCKS_PER_SEC << endl;

    return 0;
}