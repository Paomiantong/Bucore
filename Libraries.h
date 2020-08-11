#ifndef BC_LIBRARIES_H
#define BC_LIBRARIES_H
#include <string>
#include <fstream>
#include <vector>

#include "Utils/System.h"
#include "rapidjson/document.h"
using namespace rapidjson;

class Library
{
	public:
		Library(std::string p, std::string na, std::string u, std::string sh,bool n, int s )
		:Path(p),
		Name(na),
		Url(u),
		Sha1(sh),
		Native(n),
		FileSize(s){};
		std::string Path;
		std::string Name;
		std::string Url;
		std::string Sha1;
		bool Native;
		int FileSize;
		bool Check();
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
