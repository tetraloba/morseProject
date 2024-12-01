#include <iostream>
#include <windows.h>
#include "play.hpp"

#define HZ 880
#define SHORT 150

std::string CHARS[26] = { ".-  ", "-...", "-.-.", "-.. ",
                     ".   ", "..-.", "--. ", "....",
                     "..  ", ".---", "-.- ", ".-..",
                     "--  ", "-.  ", "--- ", ".--.",
                     "--.-", ".-. ", "... ", "-   ",
                     "..- ", "...-", ".-- ", "-..-",
                     "-.--", "--.."};

void _playchar(std::string m){
    for (char d : m) {
        if (d == '.') {
            Beep(HZ, SHORT);
        } else if (d == '-') {
            Beep(HZ, SHORT * 3);
        } else {
            break;
        }
    }
}
void play(std::string s) {
    for (char c : s) {
        if ('A' <= c && c <= 'Z') {
            _playchar(CHARS[c - 'A']);
        }
        else if ('a' <= c && c <= 'z') {
            _playchar(CHARS[c - 'a']);
        }
        Sleep(SHORT * 3);
    }
}
