#include "Assets.h"

Asset::Asset(std::string hash):Hash(hash)
{
	if(hash != "")
		Prefix = Hash.substr(0,2);
}

bool Asset::Check()
{
	return _exist_(_cwd_+"/.minecraft/assets/objects/"+Prefix+"/"+Hash);
}

std::string Asset::GetPath()
{
	return _cwd_+"/.minecraft/assets/objects/"+Prefix+"/"+Hash;
}

std::string Asset::GetUrl()
{
	return "http://resources.download.minecraft.net/"+Prefix+"/"+Hash;
}

Assets::Assets()
{
}

Assets::Assets(std::string u, std::string p):Url(u),Path(p)
{
}

std::string Assets::GetPath()
{
	return Path;
}

std::string Assets::GetUrl()
{
	return Url;
}

std::vector<Asset> Assets::GetLostAssest()
{
	Document dom;
	dom.Parse(ReadF(Path).c_str());
	std::vector<Asset> tmp;
	for (Value::ConstMemberIterator itr = dom["objects"].MemberBegin();
		itr != dom["objects"].MemberEnd(); ++itr)
	{
		Asset tAsset(itr->value["hash"].GetString());
		if(!tAsset.Check())
			tmp.push_back(tAsset);
	}
	return tmp;
}
