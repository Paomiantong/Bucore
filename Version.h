//Here Someting
#ifndef BC_VERSION_H
#define BC_VERSION_H
#include "Libraries.h"
#include "Assets.h"
#include "System.h"
#include "Utils/Tools.h"
#include "Utils/Args.h"

class Version
{
	private:
		void Lib_load(Value& data);
		Assets asidx;
		Libraries libraries;
		std::string from;
		std::string ver;
		std::string assetidx;
		std::string mainclass;
		Args minecraftarguments;
		Args jvmarguments;
		std::string loggingArg;
		bool isinit;
	public:
		Version();
		Version(std::string ver_json);
		bool IsInit();
		Assets GetAssets();
		Libraries GetLibraries();
		std::string GetMainclass();
		std::string GetId();
		std::string GetAssetIndex();
		Args GetMinecraftArguments();
		Args GetJVMArguments();
		//Assets assets;
};

bool AllowChecker(Value &val);
#endif
