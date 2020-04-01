#ifndef B_ASSETS_H
#define B_ASSETS_H

#include <string>
#include <vector>

#include "System.h"

class assets
{
public:
	assets (std::string hash);
	bool check();
	std::string GetPath();
	std::string GetUrl();

private:
	std::string m_sHash;
	std::string m_sPrefix;
};

class assetsIndex
{
public:
	assetsIndex (std::string u, std::string p);
	std::vector<assets> GetLostAssest();
	std::vector<assets> GetAll();
	std::string GetUrl();
	std::string GetPath();
	void AddAsset(assets as);
private:
	std::string m_sUrl;
	std::string m_sPath;
	std::vector<assets> m_vAssets;
};

#endif /* ifndef B_ASSETS_H */
