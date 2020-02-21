//Here Someting
#ifndef BC_VERSION_H
#define BC_VERSION_H
#include "Libraries.h"
#include "System.h"
#include "Utils/Tools.h"

class Version
{
	private:
		void Lib_load(Value& data);
		Libraries libraries;
		std::string from;
		std::string ver;
		std::string mainclass;
		std::string minecraftarguments;
	public:
		Version();
		Version(std::string ver_json);
		Libraries GetLibraries();
		std::string GetMainclass();
		std::string GetMinecraftArguments();
		//Assets assets;
};

bool AllowChecker(Value &val);
#endif
