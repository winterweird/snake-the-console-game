#ifndef WF_INITIALIZED
#include <windows.h>
#include "stringfuncs.h"

#ifndef XSIZE
#define XSIZE 80
#endif

#ifndef YSIZE
#define YSIZE 25
#endif

void jumpTo(int, int);
void setConsoleSizeDefault();
void setConsoleSize(int, int);
void clearScreenDefaultSize();
void clearScreen(int, int);
void printCXDefaultWidth(const char*, int);
void printCX(int, const char*, int);

void jumpTo(int x, int y) {
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &coninfo);
    coninfo.dwCursorPosition.X = x;
    coninfo.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
}
void setConsoleSizeDefault() {
    setConsoleSize(XSIZE, YSIZE);
}
void setConsoleSize(int xsize, int ysize) {
    char mode[20] = {'\0'}; // let's be realistic
    strcat(mode, "mode ");
    char* r = toString(xsize);
    strcat(mode, r);
    free(r);
    
    strcat(mode, ",");
    
    r = toString(ysize);
    strcat(mode, r);
    free(r);
    
    system(mode);
}
void clearScreenDefaultSize() {
    clearScreen(XSIZE, YSIZE);
}
void clearScreen(int xsize, int ysize) {
    jumpTo(0,0);
    for (int i = 0; i < xsize*ysize; i++) {
        printf(" ");
    }
    jumpTo(0,0);
}
void printCX(int width, const char* txt, int lineNum) {
    int i = 0;
    while (txt[i]) i++;
    jumpTo(width/2-i/2, lineNum);
    printf(txt);
}
void printCXDefaultWidth(const char* txt, int lineNum) {
    printCX(XSIZE, txt, lineNum);
}

#define WF_INITIALIZED
#endif