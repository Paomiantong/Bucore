#include "assets.h"

assets::assets(std::string hash):m_sHash(hash)
{
	if(hash != "")
		m_sPrefix = hash[0]+hash[1];
}

bool assets::check()
{
	return _exist_(_cwd_+".minecraft/assets/objects/"+m_sPrefix+"/"+m_sHash);
}

std::string assets::GetPath()
{
	return _cwd_+".minecraft/assets/objects/"+m_sPrefix+"/"+m_sHash;
}

std::string assets::GetUrl()
{
	return "http://resources.download.minecraft.net/"+m_sPrefix+"/"+m_sHash;
}

void assetsIndex::AddAsset(assets as)
{
	m_vAssets.push_back(as);
}

std::vector<assets> assetsIndex::GetLostAssest()
{
	std::vector<assets> tmp;
	for (int i = 0; i < m_vAssets.size() ; ++i) 
	{
		if(!m_vAssets[i].check())
			tmp.push_back(m_vAssets[i]);
	}

	return tmp;
}

std::vector<assets> assetsIndex::GetAll()
{
	return m_vAssets;
}
