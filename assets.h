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
	assetsIndex ();
	std::vector<assets> GetLostAssest();
	std::vector<assets> GetAll();
	void AddAsset(assets as);
private:
	std::vector<assets> m_vAssets;
};

#endif /* ifndef B_ASSETS_H */
