#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <windows.h>
#include "play.hpp"
using namespace std;

struct Pos {
    int row;
    int col;
};
struct Key {
    char c;
    Pos p;
};

uint32_t end_flag_ = 1;
mutex mtx_que_;
queue<Key> que_;
// mutex mtx_io_;

void push(Key key){
    lock_guard<mutex> lock(mtx_que_);
    que_.push(key);
}
Key pop(){
    lock_guard<mutex> lock(mtx_que_);
    Key r = que_.front(); que_.pop();
    return r;
}
void change_key_color(Key key, int color_num){
    // lock_guard<mutex> lock(mtx_io_);
    cout << "\033[s";
    cout << "\033[" << key.p.row << ';' << key.p.col << "H";
    cout << "\033[" << color_num << 'm' << key.c << "\033[m";
    cout << "\033[u" << flush;
}
char get_char(){
    // lock_guard<mutex> lock(mtx_io_);
    char c;
    cin >> noskipws;
    cin >> c;
    return c;
}
void put_char(char c){
    // lock_guard<mutex> lock(mtx_io_);
    cout << c << flush;
}
Pos getCursorPosition(HANDLE &hStdin) {
    // lock_guard<mutex> lock(mtx_io_);
    /* カーソル位置を要求 */
    cout << "\033[6n" << flush;

    /* 応答の読み取り */
    char buf[32];
    size_t i = 0;
    DWORD bytesRead;
    while (i < sizeof(buf) - 1) {
        if (ReadFile(hStdin, &buf[i], 1, &bytesRead, NULL) && bytesRead != 1) {
            break;
        }
        if (buf[i] == 'R') {
            break;
        }
        i++;
    }
    buf[i] = '\0';

    /* 応答をパース */
    int row, col;
    if (buf[0] != '\033' || buf[1] != '[') {
        return {-1, -1}; // 期待した形式でない
    }
    if (sscanf(buf + 2, "%d;%d", &row, &col) != 2) {
        return {-1, -1}; // パース失敗
    }

    return {row, col};
}

int input(){
    /* 標準入力のechoとエンター待ちを無効化する */
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE) {
        cerr << "failed to get stdin handle." << endl;
        return 1;
    }
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    DWORD newMode = mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(hStdin, newMode);

    while (true) {
        char c = get_char();
        // cout << "input char is: " << c << endl;
        if (c == 'q') {
            end_flag_ = 0;
            break;
        }
        put_char(c);
        Pos pos = getCursorPosition(hStdin);
        pos.col--; // 文字の位置はカーソルより1つ前
        push({c, pos});
    }

    SetConsoleMode(hStdin, mode);
    return 0;
}
int controler(){
    while (end_flag_) {
        while (end_flag_ && !que_.empty()) {
            Key key = pop();
            string str{key.c};
            /* 文字色を変えて再生 */
            change_key_color(key, 31); // 赤に変える
            play(str);
            change_key_color(key, 34); // 青に変える
        }
        Sleep(2);
    }
    return 0;
}

int main(){
    // cout << "\e[6n" << endl;
    thread th_input(input);
    thread th_controler(controler);

    th_input.join();
    th_controler.join();

    return 0;
}
