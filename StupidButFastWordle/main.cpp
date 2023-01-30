#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream> 
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "Calc.cpp"
#include "Init.cpp"
#include "Interactor.cpp"
#include "Player.cpp"

using namespace std;

Word guessedWord;
double wins = 0;

int calc(Word s, vector<int> &rate) {
    int score = 1;
    int cnt = 0;

    vector<double> used(32, 1);
    for(int i = 0;i < WORD_LEN;i++) {
        score += sqrt(rate[s.GetSymb(i)]) * used[s.GetSymb(i)];
        // cout << sqrt(rate[s.GetSymb(i)]) * used[s.GetSymb(i)] << ' ';
        // cout << endl;
        used[s.GetSymb(i)] *= 0.45;
    }

    return score;
}

int check(Word s) {
    int score = 1;
    int cnt = 0;

    for(int i = 0;i < 32;i++) {        
        for(auto pos : must[i]) {
            if(s.GetSymb(pos) != i) 
                return 0;
        }

        if(s.count[i] < letterCountInAnswer[i])
            return 0;
    }

    for(int i = 0;i < WORD_LEN;i++) {
        int c = s.GetSymb(i);
        if(state[c][i] == 0)
            return 0;
        score += (WORD_LEN - state[c].count() + 4) * 3;
    }

    return score;
}

void solve(Word word, vector<int> toAsk) {

    for(int i = 0;i < 32;i++) { state[i] = ALL; must[i].clear(); }
    fill(letterCountInAnswer.begin(), letterCountInAnswer.end(), 0);

    guessedWord = word;
    Interactor inter(word);

    Player p;
    int bestScore = 0;
    int bestPos = 0;

    vector<bool> isGoodWord(all.size(), true);

    for(int i = 0;i < 3;i++) {
        if(i < toAsk.size()) {
            p.ask(inter, all[toAsk[i]]);
            continue;
        }
    }

    for(int q = toAsk.size();q < 5;q++) {
        bestScore = 0;

        for(int i = 0;i < all.size();i++) {
            isGoodWord[i] = min((int)isGoodWord[i], check(all[i]));
            if(isGoodWord[i] && CalcWord(all[i], toAsk) != p.hashQ)
                isGoodWord[i] = false;
        }

        vector<int> rate(32);
        fill(letterCost.begin(), letterCost.end(), 0);

        int cntGood = 0;
        for(int i = 0;i < all.size();i++) {
            if(!isGoodWord[i]) continue;
            
            for(int j = 0;j < WORD_LEN;j++) {
                letterCost[all[i].GetSymb(j)]++;
            }
        }

        for(int i = 0;i < 32;i++) {
            rate[i] = (state[i].count()) * (letterCost[i]);
        }

        for(int i = 0;i < all.size();i++) {
            if(!isGoodWord[i]) continue;
            int newVal = check(all[i]) + calc(all[i], rate);
            if(bestScore < newVal) {
                bestPos = i;
                bestScore = newVal;
            }
        }
        
        p.ask(inter, all[bestPos]);
        toAsk.push_back(bestPos);
    }

    bestPos = 0;
    bestScore = 0;

    for(int i = 0;i < all.size();i++) {
        isGoodWord[i] = min((int)isGoodWord[i], check(all[i]));
        if(isGoodWord[i] && CalcWord(all[i], toAsk) != p.hashQ)
            isGoodWord[i] = false;
    }

    for(int i = 0;i < all.size();i++) {
        if(!isGoodWord[i])
            continue;
        
        int newVal = check(all[i]);

        if(bestScore < newVal) {
            bestPos = i;
            bestScore = newVal;
        }
    }

    if(count(isGoodWord.begin(), isGoodWord.end(), true) == 0) {
        cout << translate[word.word] << ' ';
        cout << "! NO GOOD WORDS";
        cout << endl;
        return;
    }

    //wins += 1.0 / (count(isGoodWord.begin(), isGoodWord.end(), true));
    //cout << check(all[bestPos]) << endl;

    if(word != all[bestPos]) {
        cout << "WA: " << translate[word.word] << ", ";
        cout << "I'm think it is " << translate[all[bestPos].word];
        cout << " and I have a " <<  count(isGoodWord.begin(), isGoodWord.end(), true) << " variants\n";
    } else {
        wins++;
    }
}
/*
281
*/
int main() {

    setlocale(LC_ALL, "Russian");

    freopen("Dict.txt", "r", stdin);

    ReadDict();

    srand(time(NULL));

    double time = clock(); 

    auto qs = FindBest();
    toAsk = qs;
    for(auto e : toAsk)
        cout << e << ' ';
    cout << endl;

    for(auto e : all)
        solve(e, qs);

    cout << (double)(wins) / (double)(all.size()) << endl;
    cout << (clock() - time) / (double)CLOCKS_PER_SEC << endl;

    return 0;
}