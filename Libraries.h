#ifndef BC_LIBRARIES_H
#define BC_LIBRARIES_H
#include <string>
#include <fstream>
#include <vector>

#include "System.h"
#include "rapidjson/document.h"
using namespace rapidjson;

class Library
{
	public:
		Library(std::string p, std::string na, std::string u, std::string sh,bool n, int s )
		:path(p),
		name(na),
		url(u),
		sha1(sh),
		native(n),
		size(s){};
		std::string path;
		std::string name;
		std::string url;
		std::string sha1;
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
		void Add(std::string path, std::string name, std::string url, std::string sha1, bool native, int size);
		std::vector<Library> GetAll();
		std::vector<Library> GetLostLib();
		std::vector<Library> GetNativeLib();
		std::string ToClassPathArg();
};
#endif
