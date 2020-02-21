#ifndef BC_TOOLS_H
#define BC_TOOLS_H

#include <vector>
#include <string>
#include <cstring>
#include <fstream>

bool _Replace(std::string &str1,std::string str2,std::string str3);
bool Replace(std::string &str1,std::string str2,std::string str3,bool loop);
std::string ReadF(std::string path);
std::vector<std::string> split(const std::string& str, const std::string& delim);
#endif
