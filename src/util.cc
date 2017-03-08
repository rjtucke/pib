#include "../include/util.h"
#include <algorithm>
using std::stringstream;
extern debug_level_t DEBUG;

                                                ///////////////////////////
                                                //   Utility functions   //
                                                ///////////////////////////
std::string SF(const std::string &fmt, ...) {
    int size=100;
    std::string str;
    va_list ap;
    while (1) {
        str.resize(size);
        va_start(ap,fmt);
        int n = vsnprintf((char *) str.c_str(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)   size = n+1;
        else          size *= 2;
    }
}

void Warn(int debug_level, const std::string &fmt, ...) {
    if (DEBUG >= debug_level) {
        int size=100;
        std::string str;
        va_list ap;
        while (1) {
            str.resize(size);
            va_start(ap,fmt);
            int n = vsnprintf((char *) str.c_str(), size, fmt.c_str(), ap);
            va_end(ap);
            if (n > -1 && n < size) {
                str.resize(n);
                cout << str;
                if (str[n-1] != ' ')
                    cout << endl;
                return;
            }
            if (n > -1)   size = n+1;
            else          size *= 2;
        }
    }
}

void Warn(const std::string &fmt, ...) {
    if (DEBUG == SILENT)   return;
    int size=100;
    std::string str;
    va_list ap;
    while (1) {
        str.resize(size);
        va_start(ap,fmt);
        int n = vsnprintf((char *) str.c_str(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            cout << str;
            if (str[n-1] != ' ')
                cout << endl;
            return;
        }
        if (n > -1)   size = n+1;
        else          size *= 2;
    }
}

void Die(int exit_status, const std::string &fmt, ...) {
    int size=100;
    std::string str;
    va_list ap;
    while (1) {
        str.resize(size);
        va_start(ap,fmt);
        int n = vsnprintf((char *) str.c_str(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            cerr << str;
            if (str[n-1] != ' ')
                cerr << endl;
            exit(exit_status);
        }
        if (n > -1)   size = n+1;
        else          size *= 2;
    }
}

