#include "Assets.h"

Asset::Asset(std::string hash):m_sHash(hash)
{
	if(hash != "")
		m_sPrefix = m_sHash.substr(0,2);
}

bool Asset::check()
{
	return _exist_(_cwd_+"/.minecraft/assets/objects/"+m_sPrefix+"/"+m_sHash);
}

std::string Asset::GetPath()
{
	return _cwd_+"/.minecraft/assets/objects/"+m_sPrefix+"/";
}

std::string Asset::GetUrl()
{
	return "http://resources.download.minecraft.net/"+m_sPrefix+"/"+m_sHash;
}

std::string Asset::GetName()
{
	return m_sHash;
}

Assets::Assets()
{
}

Assets::Assets(std::string u, std::string p):m_sPath(p),m_sUrl(u)
{
}

std::string Assets::GetPath()
{
	return m_sPath;
}

std::string Assets::GetUrl()
{
	return m_sUrl;
}

std::vector<Asset> Assets::GetLostAssest()
{
	Document dom;
	dom.Parse(ReadF(m_sPath).c_str());
	std::vector<Asset> tmp;
	for (Value::ConstMemberIterator itr = dom["objects"].MemberBegin();
		itr != dom["objects"].MemberEnd(); ++itr)
	{
		Asset tAsset(itr->value["hash"].GetString());
		if(!tAsset.check())
			tmp.push_back(tAsset);
	}
	return tmp;
}