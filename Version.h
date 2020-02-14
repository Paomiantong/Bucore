//Here Someting
#ifndef BC_VERSION_H
#define BC_VERSION_H
#include "Libraries.h"
#include "System.h"

#include <vector>
#include <iostream>
#include <fstream>

class Version
{
	private:
		void Lib_load(Value& data);
	public:
		Version();
		Version(std::string ver_json);
		Libraries libraries;
		std::string from;
		std::string ver;
		std::string mainclass;
		std::string minecraftarguments;
		//Assets assets;
};

bool _Replace(std::string &str1,std::string str2,std::string str3);
bool Replace(std::string &str1,std::string str2,std::string str3,bool loop);
std::string read(std::string path);
bool AllowChecker(Value &val);
std::vector<std::string> split(const std::string& str, const std::string& delim);
#endif
