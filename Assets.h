#ifndef BC_ASSETS_H
#define BC_ASSETS_H

#include <string>
#include <vector>
#include "rapidjson/document.h"
using namespace rapidjson;

#include "Utils/System.h"
#include "Utils/Tools.h"

class Asset
{
public:
	Asset (std::string hash);
	bool Check();
	std::string GetPath();
	std::string GetUrl();

private:
	std::string Hash;
	std::string Prefix;
};

class AssetIndex
{
public:
	AssetIndex();
	AssetIndex (std::string u, std::string p);
	std::string GetPath();
	std::string GetUrl();
	std::vector<Asset> GetLostAssest();
private:
	std::string Url;
	std::string Path;
};

#endif
