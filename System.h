#ifndef BC_SYSTEM_H
#define BC_SYSTEM_H

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
