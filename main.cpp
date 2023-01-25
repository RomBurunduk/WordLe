#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

// функция удаления по индексу
void rem(std::vector<std::string> &v, size_t index){
    auto it = v.begin();
    std::advance(it, index);
    v.erase(it);
}

// функция подсчета букв в слове
int count_letter (std::string s, std::string a) {
    int count = 0;

    for (int i = 0; i < s.size(); i++)
        if (s.substr(i*2,2) == a) count++;

    return count;
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

    int n=4914;

    // рабочий словарь (который будет урезаться)
    std::vector<std::string> dict(n);
    for (int i=0; i<n; i++) {
        in>>dict[i];
    }
    // словарь для поика оптимального слова
    std::vector<std::string> optimal=dict;

    // слово
    std::string wor("boo");
    // условия
    std::vector<int> con(5);
    std::cout<<"Введите слово"<<std::endl;
    std::cin>>wor;
    std::cout<<"Введите условия"<<std::endl;
    // считывание условия
    for (int j=0; j<5; j++) {
        std::cin>>con[j];
    }


    while (wor!="все") {
        int t=0;
        while (t<n) {   // филтрация словарая по условию
            if (f(wor.substr(0,2), 0, con[0], dict[t]) && f(wor.substr(2,2), 2, con[1], dict[t]) && f(wor.substr(4,2), 4, con[2], dict[t]) && f(wor.substr(6,2), 6, con[3], dict[t]) && f(wor.substr(8,2), 8, con[4], dict[t])) {
                std::cout<<dict[t]<<' ';
                t+=1;
            } else {
                rem(dict, t);
                n--;
            }
        }
        // окончание работы программы если в словре осталось немколько слов
        std::cout<<std::endl;
        if (dict.size()<=2){
            return 0;
        }

        // составление рейтинга букв
        std::multimap<int,std::string> mp;
        for (int l=0; l<32; l++) {
            int i=0;
            for (int j=0; j<dict.size(); j++) {
                if (dict.at(j).find(alph.substr(l*2,2))!=std::string::npos) {
                    i+=1;
                }
            }
            if (i != 0 && i != dict.size()) {
                mp.insert(std::make_pair(i,alph.substr(l*2,2)));
            }
        }

        // выводим оставшего алфавита
        std::map <int, std::string> :: iterator it = mp.begin();
        for (; it != mp.end(); it++) {
            std::cout << it->first << " " << it->second << std::endl;
        }

        //  вывод оптимального слова
        std::string OptWord;
        bool OptFlag=false;
        if (mp.size()>=5){
            it=mp.end();
            it--;
            std::string l1=it->second;
            it--;
            std::string l2=it->second;
            it--;
            std::string l3=it->second;
            it--;
            std::string l4=it->second;
            it--;
            std::string l5=it->second;
            for (int i = 5; i >1 ; --i) {
                for (std::string s: optimal){
                    if ((s.find(l1)!=std::string::npos) + (s.find(l2)!=std::string::npos) + (s.find(l3)!=std::string::npos) + (s.find(l4)!=std::string::npos) == i){
                        std::cout<<"Оптимальное слово: "<<s<<std::endl;
                        OptWord=s;
                        OptFlag=true;
                        break;
                    }
                }
                if (OptFlag) break;
            }

        }

        // если есть оптимальное слово -> вводим его в игру
        if (OptFlag){
            wor=OptWord;
        } else {
            std::cout<<"Введите слово"<<std::endl;
            std::cin>>wor;
            if (wor=="все") {
                break;
            }
        }

        std::cout<<"Введите условия"<<std::endl;
        for (int j=0; j<5; j++) {
            std::cin>>con[j];
        }
    }
}