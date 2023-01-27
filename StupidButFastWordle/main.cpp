#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream> 
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "Init.cpp"
#include "Interactor.cpp"
#include "Player.cpp"

using namespace std;

Word guessedWord;
int wins;

int calc(Word s, vector<int> &rate) {
    int score = 1;
    int cnt = 0;

    vector<double> used(32, 1);
    for(int i = 0;i < WORD_LEN;i++) {
        score += (rate[s.GetSymb(i)]) * used[s.GetSymb(i)];
        // cout << sqrt(rate[s.GetSymb(i)]) * used[s.GetSymb(i)] << ' ';
        // cout << endl;
        used[s.GetSymb(i)] *= 0.5;
    }

    return score;
}

int check(Word s) {
    int score = 1;
    int cnt = 0;

    for(int j = 0;j < 32;j++) {
        int i = j;
        for(auto pos : must[i]) {
            if(s.GetSymb(pos) != i) 
                return 0;
        }
        if(s.count[j] < letterCountInAnswer[j])
            return 0;
    }

    for(int i = 0;i < WORD_LEN;i++) {
        int c = s.GetSymb(i);
        if(state[c][i] == 0)
            return 0;
        score += (WORD_LEN - state[c].count() + 3) * 9;
    }

    return score;
}

void solve(Word word) {
    for(int i = 0;i < 32;i++)
        state[i] = ALL, must[i].clear();

    fill(letterCountInAnswer.begin(), letterCountInAnswer.end(), 0);

    guessedWord = word;

    srand(time(NULL));

    Interactor inter(word);
    
    inter.ans = guessedWord;

    Player p;

    int bestPos = 1737;
    int bestScore = 0;

    vector<bool> goodWord(all.size(), true);
    for(int q = 0;q < 5;q++) {

        vector<int> rate(32);
        bestScore = 0;
        fill(letterCost.begin(), letterCost.end(), 0);

        for(int i = 0;i < all.size();i++) {
            if(!goodWord[i]) continue;
            for(int j = 0;j < WORD_LEN;j++) {
                letterCost[all[i].GetSymb(j)]++;
            }
        }

        for(int i = 0;i < 32;i++) {
            rate[i] = (state[i].count()) * (letterCost[i]) * must[i].empty();
        }

        for(int i = 0;i < all.size();i++) {
            if(!goodWord[i]) continue;
            int newVal = calc(all[i], rate);
            if(bestScore < newVal) {
                bestPos = i;
                bestScore = newVal;
            }
        }
        
        p.ask(inter, all[bestPos]);
        for(int i = 0;i < all.size();i++)
            goodWord[i] = check(all[i]);
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
    
    // cout << check(word) << endl;
    // for(int i = 0;i < WORD_LEN;i++) {
    //     cout << letterCountInAnswer[word[i]] << ':' << (int)word.count[word[i]] << endl;
    // }
    // for(int i = 0;i < WORD_LEN;i++) {
    //     cout << state[guessedWord[i]] << endl;
    // }

    if(guessedWord != all[bestPos]) {
        wins--;
        cout << "WA: " << translate[guessedWord.word] << ", ";
        cout << "I'm think it is " << translate[all[bestPos].word] << endl; 
    }
}
/*
281
*/
int main() {

    setlocale(LC_ALL, "Russian");

    freopen("Dict.txt", "r", stdin);

    ReadDict();
    CountLetterFreq();
    wins = all.size();

    double time = clock();    
#ifdef DEBUG
    solve(all[281]);
#else
    for(auto e : all)
        solve(e);
#endif
    cout << (double)(wins) / (double)(all.size()) << endl;

    cout << (clock() - time) / (double)CLOCKS_PER_SEC << endl;

    return 0;
}