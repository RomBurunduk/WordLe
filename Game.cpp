#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>

std::string conditions(std::string str, std::string ans){
    std::string report;
    for (int i = 0; i < 5; ++i) {
        if (str.substr(i*2,2)==ans.substr(i*2,2)){
            report+="3 ";
        } else if (ans.find(str.substr(i*2,2))!=std::string::npos){
            report+="2 ";
        } else {
            report+="1 ";
        }
    }
    return report;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::ifstream in("/Users/romburunduk/CLionProjects/untitled/dict.txt");
    int n=4914;

    std::vector<std::string> dict(n);
    for (int i=0; i<n; i++) {
        in>>dict[i];
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> Rand(0,4913);
    std::string answer=dict[Rand(rng)];
    std::cout<<answer<<std::endl;

    std::string word;
    bool win= true;

    for (int i = 0; i < 6; ++i) {
        std::cin>>word;
        if (word!=answer) {
            std::cout<<conditions(word, answer)<<std::endl;
        } else {
            std::cout<<"Победа!";
            win= false;
        }
    }
    if (win){
        std::cout<<"Проигрыш"<<std::endl;
    }
}
