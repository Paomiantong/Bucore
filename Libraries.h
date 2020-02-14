#ifndef BC_LIBRARIES_H
#define BC_LIBRARIES_H
#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

#include "rapidjson/document.h"
using namespace rapidjson;

class Library
{
	public:
		Library(std::string p,std::string u,bool n,int s):path(p),url(u),native(n),size(s){};
		std::string path;
		std::string url;
		bool native;
		int size;
		bool check();
};

class Libraries
{
	private:
		std::vector<Library> library;
		std::vector<int> lostlib;
		std::vector<int> nativelib;
	public:
		void Add(std::string path,std::string url,bool native,int size);
		std::vector<Library> GetLostLib();
		std::string toString();
};
#endif
