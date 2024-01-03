#include <windows.h>
#include <stdio.h>

#define HZ 440
#define SHORT 150

void play(char*);
void playchar(char*);

char CHARS[][5] = { ".-  ", "-...", "-.-.", "-.. ",
                    ".   ", "..-.", "--. ", "....",
                    "..  ", ".---", "-.- ", ".-..",
                    "--  ", "-.  ", "--- ", ".--.",
                    "--.-", ".-. ", "... ", "-   ",
                    "..- ", "...-", ".-- ", "-..-",
                    "-.--", "--.."};

void main(void){
    char str[] = "Hello World! This is a test message. Can you hear me?";
    play(str);
}
void play(char* c) {
    while (*c) {
        if ('A' <= *c && *c <= 'Z') {
            playchar(CHARS[*c - 'A']);
        }
        else if ('a' <= *c && *c <= 'z') {
            playchar(CHARS[*c - 'a']);
        }
        putchar(*c);
        Sleep(SHORT * 3);
        c++;
    }
    putchar('\n');
}
void playchar(char *m){
    while (*m) {
        if (*m == '.') {
            Beep(HZ, SHORT);
        } else if (*m == '-') {
            Beep(HZ, SHORT * 3);
        } else {
            break;
        }
        m++;
    }
}