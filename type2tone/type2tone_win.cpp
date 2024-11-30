#include <iostream>
#include <windows.h>
#include <queue>
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
Pos getCursorPosition(HANDLE&);

int rawtest(){
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

    queue<Key> que;
    while (true) {
        char c;
        cin >> c;
        // cout << "input char is: " << c << endl;
        if (c == 'q') {
            break;
        }
        cout << c;
        Pos pos = getCursorPosition(hStdin);
        que.push({c, pos});
        string str{c};
        play(str);
    }
    while (!que.empty()) {
        Key q = que.front(); que.pop();
        cout << '(' << q.c << ':' << q.p.row << ',' << q.p.col << ')';
    }

    SetConsoleMode(hStdin, mode);
    return 0;
}
Pos getCursorPosition(HANDLE &hStdin) {
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

int main(){
    // cout << "\e[6n" << endl;
    rawtest();
    return 0;
}
