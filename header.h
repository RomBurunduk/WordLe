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
#include <opencv2/opencv.hpp>

// функция удаления по индексу
void rem(std::vector<std::string> &v, size_t index) {
    auto it = v.begin();
    std::advance(it, index);
    v.erase(it);
}

int MyCount(const std::string &s1, const std::string &s2) {
    int cnt = 0;
    for (int i = 0; i < 5; ++i)
        if (s1.substr(i * 2, 2) == s2)
            cnt++;
    return cnt;
}

void normalaize(const std::string &word, std::vector<int> &con) {
    std::map<std::string, int> mp;
    for (int i = 0; i < 5; ++i) {
        if (con[i] != 1)
            mp[word.substr(i * 2, 2)]++;
    }
    for (int i = 0; i < 5; ++i) {
        if (mp[word.substr(i * 2, 2)] != 0 && con[i] == 1)
            con[i] = 2;
    }
}

bool LettersInWord(const std::string &word, std::map<std::string, std::array<int, 2>> con) {
    for (auto &it: con) {
        if (it.second[1] == 0) {
            if (MyCount(word, it.first) != it.second[0])
                return false;
        } else {
            if (MyCount(word, it.first) < it.second[0])
                return false;
        }
    }
    return true;
}


// функция фильтрации по условию игры на букву
bool f(const std::string &letter, int pos, int num, const std::string &word) {
    int p = (int) word.find(letter, pos);
    switch (num) {
        case 1:
            return word.find(letter) == std::string::npos;
            break;
        case 2:
            return word.find(letter) != std::string::npos && p != pos;
            break;
        case 3:
            return pos == p;
        default:
            return true;
            break;
    }
}


void emulateKeyPress(CGKeyCode keyCode) {
    CGEventRef keyDownEvent = CGEventCreateKeyboardEvent(nullptr, keyCode, true);
    CGEventPost(kCGHIDEventTap, keyDownEvent);
    CFRelease(keyDownEvent);

    CGEventRef keyUpEvent = CGEventCreateKeyboardEvent(nullptr, keyCode, false);
    CGEventPost(kCGHIDEventTap, keyUpEvent);
    CFRelease(keyUpEvent);
}

std::map<std::string, int> alph = {{"а", 3},
                                   {"б", 43},
                                   {"в", 2},
                                   {"г", 32},
                                   {"д", 37},
                                   {"е", 17},
                                   {"ж", 41},
                                   {"з", 35},
                                   {"и", 11},
                                   {"й", 12},
                                   {"к", 15},
                                   {"л", 40},
                                   {"м", 9},
                                   {"н", 16},
                                   {"о", 38},
                                   {"п", 5},
                                   {"р", 4},
                                   {"с", 8},
                                   {"т", 45},
                                   {"у", 14},
                                   {"ф", 0},
                                   {"х", 33},
                                   {"ц", 13},
                                   {"ч", 7},
                                   {"ш", 34},
                                   {"щ", 31},
                                   {"ъ", 30},
                                   {"ы", 1},
                                   {"ь", 46},
                                   {"э", 39},
                                   {"ю", 47},
                                   {"я", 6}};

void Type(std::string &s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        emulateKeyPress(alph[s.substr(i * 2, 2)]);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    emulateKeyPress(kVK_Return);
}


cv::Vec3b green = {94, 182, 135};
cv::Vec3b gray = {194, 174, 166};

std::vector<int> condit(int line) {
    std::vector<int> c(5);
    int y = 377 + 126 * line, x = 1177;
    std::system("screencapture ~/Desktop/myscreen.png");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cv::Mat image = cv::imread("/Users/romburunduk/Desktop/myscreen.png"); // загрузка изображения
    for (int i = 0; i < 5; ++i, x += 125) {
        cv::Point pixel(x, y); // координаты пикселя
        cv::Vec3b color = image.at<cv::Vec3b>(pixel); // получение цвета пикселя
        if ((green[0] - 10 < color[0] && color[0] < green[0] + 10) &&
            (green[1] - 10 < color[1] && color[1] < green[1] + 10) &&
            (green[2] - 10 < color[2] && color[2] < green[2] + 10))
            c[i] = 3;
        else if ((gray[0] - 10 < color[0] && color[0] < gray[0] + 10) &&
                 (gray[1] - 10 < color[1] && color[1] < gray[1] + 10) &&
                 (gray[2] - 10 < color[2] && color[2] < gray[2] + 10))
            c[i] = 1;
        else
            c[i] = 2;
    }
    return c;
}

