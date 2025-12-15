#pragma once
#include <iostream>
#include <string>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

// ================= CONSOLE =================
inline void setConsoleColor(int text = 15, int bg = 1) {
#ifdef _WIN32
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        (bg << 4) | text
    );
#endif
}

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ================= CURSOR =================
inline void setCursor(int x, int y) {
#ifdef _WIN32
    COORD pos;
    pos.X = static_cast<SHORT>(x);
    pos.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        pos
    );
#endif
}

// ================= FIXED LEFT UI =================
// Use SAME X everywhere
inline void printAt(int x, int y, const std::string& text) {
    setCursor(x, y);
    std::cout << text;
}

inline void inputAt(int x, int y, const std::string& label) {
    setCursor(x, y);
    std::cout << label;
}

// ================= PAUSE =================
inline void pauseScreen() {
    std::cout << "\n\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
