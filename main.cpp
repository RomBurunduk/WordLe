#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <random>

// функция удаления по индексу
void rem(std::vector<std::string> &v, size_t index){
    auto it = v.begin();
    std::advance(it, index);
    v.erase(it);
}

std::vector<int> conditions(std::string str, std::string ans){
    std::vector<int> report(5);
    if (str==ans){
        report={0,3,3,3,3};
        return report;
    }
    for (int i = 0; i < 5; ++i) {
        if (str.substr(i*2,2)==ans.substr(i*2,2)){
            report[i]=3;
        } else if (ans.find(str.substr(i*2,2))!=std::string::npos){
            report[i]=2;
        } else {
            report[i]=1;
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


int main() {
    setlocale(LC_ALL, "Russian");
    std::string alph{"абвгдежзийклмнопрстуфхчцщшъыьэюя"};
    std::ifstream in("/Users/romburunduk/CLionProjects/untitled/dict.txt");
    // Количество слов в изначальном словаре
    int n=4914;

    // рабочий словарь (который будет урезаться)
    std::vector<std::string> dict(n);
    for (int i=0; i<n; i++) {
        in>>dict[i];
    }
    // словарь для поика оптимального слова
    std::vector<std::string> const optimal=dict;

    std::mt19937 rnd(12);
    std::multimap<int, std::string> mp;
    double wins=0;
    std::vector<int> con(5);
    std::string OptWord;
    std::vector<int> att(6);
    std::vector<std::string> WrAns;




    // НАЧАЛО ЦИКЛА ИГРЫ



    for (std::string ans: optimal) {

        // слово
        std::string wor("кроат");
        // условия
        //    std::cout<<"Введите слово"<<std::endl;
        //    std::cin>>wor;
        //    std::cout<<"Введите условия"<<std::endl;
        // считывание условия
        con = conditions(wor, ans);


        int attempts=1;


        while (con[0] != 0 && attempts<6) {
            int t = 0;
            while (t < n) {   // филтрация словарая по условию
                if (f(wor.substr(0, 2), 0, con[0], dict[t]) && f(wor.substr(2, 2), 2, con[1], dict[t]) &&
                    f(wor.substr(4, 2), 4, con[2], dict[t]) && f(wor.substr(6, 2), 6, con[3], dict[t]) &&
                    f(wor.substr(8, 2), 8, con[4], dict[t])) {
                    //                std::cout<<dict[t]<<' ';
                    t += 1;
                } else {
                    rem(dict, t);
                    n--;
                }
            }
            //        std::cout<<std::endl;
            // окончание работы программы если в словре осталось немколько слов
            //        if (dict.size()<=2){
            //            return 0;
            //        }

            // составление рейтинга букв
            for (int l = 0; l < 32; l++) {
                int i = 0;
                for (int j = 0; j < dict.size(); j++) {
                    if (dict.at(j).find(alph.substr(l * 2, 2)) != std::string::npos) {
                        i += 1;
                    }
                }
                if (i != 0 && i < dict.size()) {
                    mp.insert(std::make_pair(i, alph.substr(l * 2, 2)));
                }
            }

            // выводим оставшего алфавита
            std::map<int, std::string>::iterator it = mp.begin();
            //        for (; it != mp.end(); it++) {
            //            std::cout << it->first << " " << it->second << std::endl;
            //        }

            //  вывод оптимального слова
            bool OptFlag = false;
            if (mp.size() >= 5) {
                it = mp.end();
                it--;
                std::string l1 = it->second;
                it--;
                std::string l2 = it->second;
                it--;
                std::string l3 = it->second;
                it--;
                std::string l4 = it->second;
                it--;
                std::string l5 = it->second;
                for (int i = 5; i > 1; --i) {
                    for (std::string s: optimal) {
                        if ((s.find(l1) != std::string::npos) + (s.find(l2) != std::string::npos) +
                            (s.find(l3) != std::string::npos) + (s.find(l4) != std::string::npos) == i) {
//                            std::cout << "Оптимальное слово: " << s << std::endl;
                            OptWord = s;
                            OptFlag = true;
                            break;
                        }
                    }
                    if (OptFlag) break;
                }

            }

            // если есть оптимальное слово -> вводим его в игру
            if (OptFlag) {
                wor = OptWord;
            } else {
                wor = dict[rnd() % dict.size()];
                //            std::cout<<"Оптимальное слово: "<<wor<<std::endl;
                //            std::cout<<"Введите слово"<<std::endl;
                //            std::cin>>wor;
                //            if (wor=="все") {
                //                break;
                //            }
            }

//            std::cout << "Введите условия" << std::endl;
            con = conditions(wor, ans);
            attempts++;
            mp.clear();
        }
        if (con[0]==0){
            wins++;
        } else {
            wins+=1.0/dict.size();
            WrAns.push_back(ans);
        }
        mp.clear();
        dict=optimal;
        n=4914;
        att[attempts-1]+=1;
        std::cout<<ans<<' '<<wins<<' '<<attempts<<std::endl;

    }

    std::cout<<wins*100.0/4914.0<<"%"<<std::endl;
    for (int i = 0; i < 6; ++i) {
        std::cout<<i+1<<' '<<att[i]<<std::endl;
    }
    for (std::string str : WrAns) {
        std::cout<<str<<' ';
    }
    std::cout<<std::endl;

}