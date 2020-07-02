#ifndef BC_ASSETS_H
#define BC_ASSETS_H

#include <string>
#include <vector>
#include "rapidjson/document.h"
using namespace rapidjson;

#include "System.h"
#include "Utils/Tools.h"

class Asset
{
public:
	Asset (std::string hash);
	bool check();
	std::string GetPath();
	std::string GetUrl();

private:
	std::string m_sHash;
	std::string m_sPrefix;
};

class Assets
{
public:
	Assets();
	Assets (std::string u, std::string p);
	std::string GetPath();
	std::string GetUrl();
	std::vector<Asset> GetLostAssest();
private:
	std::string m_sUrl;
	std::string m_sPath;
};

#endif
