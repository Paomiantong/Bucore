//Here Someting
#ifndef BC_VERSION_H
#define BC_VERSION_H
#include "Libraries.h"
#include "System.h"
#include "Utils/Tools.h"
#include "Utils/Args.h"

class Version
{
	private:
		void Lib_load(Value& data);
		Libraries libraries;
		std::string from;
		std::string ver;
		std::string mainclass;
		Args minecraftarguments;
	public:
		Version();
		Version(std::string ver_json);
		Libraries GetLibraries();
		std::string GetMainclass();
		Args GetMinecraftArguments();
		//Assets assets;
};

bool AllowChecker(Value &val);
#endif
