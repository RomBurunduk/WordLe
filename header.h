#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <random>
#include <array>

// функция удаления по индексу
void rem(std::vector<std::string> &v, size_t index){
    auto it = v.begin();
    std::advance(it, index);
    v.erase(it);
}

int MyCount(std::string s1,std::string s2){
    int cnt = 0;
    for(int i = 0; i < 5; ++i)
        if (s1.substr(i*2,2)==s2)
            cnt++;
    return cnt;
}

void normalaize(std::string word, std::vector<int> &con){
    std::map<std::string, int> mp;
    for (int i = 0; i < 5; ++i) {
        if (con[i]!=1)
            mp[word.substr(i*2,2)]++;
    }
    for (int i = 0; i < 5; ++i) {
        if (mp[word.substr(i*2,2)]!=0 && con[i]==1)
            con[i]=2;
    }
}

bool LettersInWord(std::string word, std::map<std::string, std::array<int,2>> con){
    for(auto it=con.begin();it!=con.end();it++){
        if (it->second[1]==0) {
            if (MyCount(word, it->first) != it->second[0])
                return false;
        } else {
            if (MyCount(word, it->first) < it->second[0])
                return false;
        }
    }
    return true;
}

std::vector<int> conditions(const std::string &word, const std::string &ans){
    std::vector<int> report(5,1);
    if (ans == word)
        return {0,0,0,0,0};
    std::map<std::string,int> letters;
    for (int i = 0; i < 5; ++i)
        letters[ans.substr(i * 2, 2)]++;
    for (int i = 0; i < 5; ++i) {
        if (ans.substr(i*2,2)==word.substr(i*2,2)){
            report[i]=3;
            letters[word.substr(i*2,2)]--;
        }
    }
    for (int i = 0; i < 5; ++i) {
        if (ans.substr(i*2,2)!=word.substr(i*2,2) && ans.find(word.substr(i*2,2))!=std::string::npos){
            if (letters[word.substr(i*2,2)]==0)
                report[i]=1;
            else {
                report[i]=2;
                letters[word.substr(i*2,2)]--;
            }
        }
    }
    return report;
}



// функция фильтрации по условию игры на букву
bool f(std::string letter, int pos, int num, std::string word){
    int p=word.find(letter,pos);
    switch (num) {
        case 1:
            return word.find(letter)==std::string::npos;
            break;
        case 2:
            return word.find(letter)!=std::string::npos && p!=pos;
            break;
        case 3:
            return pos==p;
        default:
            return true;
            break;
    }
}
