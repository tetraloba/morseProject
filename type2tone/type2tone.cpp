#include <iostream>
#include <unistd.h>
#include <queue>
using namespace std;
int cursor_pos_test();
bool getCursorPosition(int&, int&);
struct Key {
    char c;
    int row;
    int col;
};

int rawtest(){
    system("stty raw -echo");
    queue<Key> que;
    while (true) {
        char c;
        cin >> c;
        // cout << "input char is: " << c << endl;
        if (c == 'q') {
            break;
        }
        cout << c;
        int row, col;
        getCursorPosition(row, col);
        que.push({c, row, col});
    }
    while (!que.empty()) {
        Key q = que.front(); que.pop();
        cout << '(' << q.c << ':' << q.row << ',' << q.col << ')';
    }
    system("stty cooked echo");
    return 0;
}
bool getCursorPosition(int &row, int &col) {
    // カーソル位置を要求
    cout << "\033[6n" << flush;

    // 応答を読み取るバッファ
    char buf[32];
    size_t i = 0;

    // 読み取り
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) {
            break;
        }
        if (buf[i] == 'R') {
            break;
        }
        i++;
    }
    buf[i] = '\0';

    // 応答をパース
    if (buf[0] != '\033' || buf[1] != '[') {
        return false; // 期待した形式でない場合
    }

    if (sscanf(buf + 2, "%d;%d", &row, &col) != 2) {
        return false; // パース失敗
    }

    return true;
}
int cursor_pos_test(){
    int row = 0, col = 0;
    if (getCursorPosition(row, col)) {
        // cout << "Cursor is at row " << row << ", column " << col << endl;
        cout << '(' << row << ',' << col << ')';
    } else {
        cerr << "Failed to get cursor position." << endl;
    }
    return 0;
}

int main(){
    // cout << "\e[6n" << endl;
    rawtest();
    // cursor_pos_test();
    return 0;
}