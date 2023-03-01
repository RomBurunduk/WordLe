#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <random>
#include <array>
#include <Carbon/Carbon.h>
#include <thread>

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
    for (auto it=con.begin();it!=con.end();it++) {
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
    int p = (int) word.find(letter,pos);
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


void emulateKeyPress(CGKeyCode keyCode) {
    CGEventRef keyDownEvent = CGEventCreateKeyboardEvent(NULL, keyCode, true);
    CGEventPost(kCGHIDEventTap, keyDownEvent);
    CFRelease(keyDownEvent);

    CGEventRef keyUpEvent = CGEventCreateKeyboardEvent(NULL, keyCode, false);
    CGEventPost(kCGHIDEventTap, keyUpEvent);
    CFRelease(keyUpEvent);
}

std::map<std::string, int> alph={{"а",3},{"б",43},{"в",2},{"г",32},{"д",37},{"е",17},{"ж",41},{"з",35},{"и",11},{"й",12},{"к",15},{"л",40},{"м",9},{"н",16},{"о",38},{"п",5},{"р",4},{"с",8},{"т",45},{"у",14},{"ф",0},{"х",33},{"ц",13},{"ч",7},{"ш",34},{"щ",31},{"ъ",30},{"ы",1},{"ь",46},{"э",39},{"ю",47},{"я",6}};

void Type(std::string &s){
    for (int i = 0; i < s.size()/2; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        emulateKeyPress(alph[s.substr(i*2,2)]);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

