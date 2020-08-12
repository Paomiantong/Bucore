//Here Someting
#ifndef BC_VERSION_H
#define BC_VERSION_H
#include "Libraries.h"
#include "Assets.h"
#include "Utils/System.h"
#include "Utils/Tools.h"
#include "Utils/Args.h"

bool AllowChecker(Value &val);

class Version
{
	private:
		// void Lib_load(Value& data);
		friend class VersionParser;
		AssetIndex asidx;
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
		AssetIndex GetAssets();
		Libraries GetLibraries();
		std::string GetMainclass();
		std::string GetId();
		std::string GetAssetIndex();
		Args GetMinecraftArguments();
		Args GetJVMArguments();
		//Assets assets;
};

class VersionParser
{
	public:
		VersionParser(std::string VersionJson_,Version* VersionPointer_);
		virtual void Parse();
		virtual void LibrariesLoader(Value& data);
		bool IsInit();
	protected:
		Version* VersionPointer;
		std::string VersionJson;
		bool InitFlag;
};

VersionParser* CreateVersionParser(std::string src, Version* VersionPointer_);

#endif
