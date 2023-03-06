#include "header.h"


int main() {
    sleep(1);
    std::ios_base::sync_with_stdio(false);
    setlocale(LC_ALL, "Russian");
    std::string alph{"абвгдежзийклмнопрстуфхчцщшъыьэюя"};
    std::ifstream in("/Users/romburunduk/CLionProjects/untitled/dict.txt");
    // Количество слов в изначальном словаре
    int n = 4914;

    // рабочий словарь (который будет урезаться)
    std::vector<std::string> dict(n);
    for (int i = 0; i < n; i++) {
        in >> dict[i];
    }
    // словарь для поика оптимального слова
    std::vector<std::string> const optimal = dict;
    std::random_device dev;
    std::mt19937 rnd(dev());
    std::multimap<int, std::string> mp;
    double wins = 0;
    std::vector<int> con(5);
    std::string OptWord;
    std::vector<int> att(6);
    std::vector<std::string> WrAns;
    std::map<std::string, std::array<int, 2>> NumOfLetters;  //{колчичество, режим (0-строго, 1-нестрого)}






    // НАЧАЛО ЦИКЛА ИГРЫ



    for (int times = 0; times < 10; times++) {
        int line = 0;
        // слово
        std::string wor("кроат");
        Type(wor);
        sleep(1);
        // условия
        con = condit(line);
        line++;
        std::map<std::string, std::array<int, 2>> rate;  //{gray, not gray}
        for (int i = 0; i < 5; ++i) {
            if (con[i] != 1)
                rate[wor.substr(i * 2, 2)][1]++;
            else
                rate[wor.substr(i * 2, 2)][0]++;
        }
        normalaize(wor, con);
        auto iter = rate.begin();
        for (; iter != rate.end(); iter++) {
            if (iter->second[0] == 0 && iter->second[1] != 0)
                NumOfLetters[iter->first] = {iter->second[1], 1};
            else if (iter->second[0] != 0 && iter->second[1] == 0)
                NumOfLetters[iter->first] = {0, 0};
            else
                NumOfLetters[iter->first] = {iter->second[1], 0};
        }
        int attempts = 1;


        while (attempts < 7 && !std::all_of(con.begin(),con.end(),[](int c){return c==3;})) {
            int t = 0;
            while (t < n) {     // филтрация словарая по условию
                if (LettersInWord(dict.at(t), NumOfLetters) && f(wor.substr(0, 2), 0, con[0], dict.at(t)) &&
                    f(wor.substr(2, 2), 2, con[1], dict.at(t)) &&
                    f(wor.substr(4, 2), 4, con[2], dict.at(t)) && f(wor.substr(6, 2), 6, con[3], dict.at(t)) &&
                    f(wor.substr(8, 2), 8, con[4], dict.at(t))) {
                    t++;
                } else {
                    rem(dict, t);
                    n--;
                }
            }

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
                            (s.find(l3) != std::string::npos) + (s.find(l4) != std::string::npos) +
                            (s.find(l5) != std::string::npos) == i) {
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
            }

            Type(wor);
            sleep(2);
            con=condit(line);
            line++;
            rate.clear();
            for (int i = 0; i < 5; ++i) {
                if (con[i] != 1)
                    rate[wor.substr(i * 2, 2)][1]++;
                else
                    rate[wor.substr(i * 2, 2)][0]++;
            }
            normalaize(wor, con);
            iter = rate.begin();
            NumOfLetters.clear();
            for (; iter != rate.end(); iter++) {
                if (iter->second[0] == 0 && iter->second[1] != 0)
                    NumOfLetters[iter->first] = {iter->second[1], 1};
                else if (iter->second[0] != 0 && iter->second[1] == 0)
                    NumOfLetters[iter->first] = {0, 0};
                else
                    NumOfLetters[iter->first] = {iter->second[1], 0};
            }
            attempts++;
            mp.clear();
        }
        NumOfLetters.clear();
        rate.clear();
        mp.clear();
        dict = optimal;
        n = 4914;
        sleep(2);
        emulateKeyPress(kVK_Return);
        sleep(2);
    }
}