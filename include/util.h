#ifndef __util_h__
#define __util_h__
#include <cstdio>
#include <cstdarg>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sysexits.h>
#include <vector>
using std::vector;
using std::string;
using std::cerr;
using std::cout;
using std::endl;
enum debug_level_t {
    SILENT,
    NORMAL,
    VERBOSE, 
    TRACE
};

string SF(const string &fmt, ...);
void Warn(int debug_level, const string &fmt, ...);
void Warn(const string &fmt, ...);
void Die(int exit_status, const string &fmt, ...);
#endif
