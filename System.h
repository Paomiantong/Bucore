#ifndef BC_SYSTEM_H
#define BC_SYSTEM_H

#ifdef _WIN32
#define B_OS "windows"
#elif __linux__ 
#define B_OS "linux"
#elif __APPLE__ 
#define B_OS "macos"
#elif __MACOSX__
#define B_OS "osx"
#endif

#include <string>
#ifdef __WIN32__
#include <io.h>
#include <windows.h>
#define BC_MAXPATH 1024
#else
#include <unistd.h>
#include <sys/stat.h>
#endif
#define _cwd_ getDir()
#define _exist_ checkfile
std::string getDir();
bool checkfile(std::string file);
#endif
