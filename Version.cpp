#include "Version.h"

Version::Version(){}
Version::Version(std::string ver_json)
{
	std::string json = ReadF(ver_json);
	Document dom;
	dom.Parse(json.c_str());
	ver = dom["id"].GetString();
	mainclass = dom["mainClass"].GetString();
	//if(dom.HasMember("assetIndex"))
	//	Lau.asindex=dom["assetIndex"]["id"].GetString();
	//Arguments
	if(dom.HasMember("minecraftArguments"))//after 1.13
	{
		minecraftarguments=dom["minecraftArguments"].GetString();
	}else if(dom.HasMember("arguments"))//1.13 and more
	{
		Value &Arg_Game=dom["arguments"]["game"],&Arg_Jvm=dom["arguments"]["jvm"];
		for(auto &a_v : Arg_Game.GetArray())
		{
			if(a_v.IsString())
			{
				minecraftarguments+=a_v.GetString();
				minecraftarguments+=" ";
			}
		}
	}
	//if(dom.HasMember("jar"))
	if(dom.HasMember("inheritsFrom"))
	{
		std::string ihf=dom["inheritsFrom"].GetString(),p=_cwd_+"/.minecraft/version/"+ihf+"/"+ihf+".json";
		Version father(p);
		libraries=father.GetLibraries();
	}
	Lib_load(dom["libraries"]);
}

Libraries Version::GetLibraries()
{
	return libraries;
}

std::string Version::GetMainclass()
{
	return mainclass;
}

std::string Version::GetMinecraftArguments()
{
	return minecraftarguments;
}

void Version::Lib_load(Value& data)
{
	for (auto& v : data.GetArray())
	{
			if (v.HasMember("extract")||!AllowChecker(v))//Check Allow
			{
				continue;
			}
			//Split The name
			std::vector<std::string> tmp1=split(v["name"].GetString(),":");
			std::string last,names;
			for (int x=0;x<tmp1[0].length();x++)
			{
				if(tmp1[0][x]=='.')
					tmp1[0][x]='/';
			}
			/*Native Part&Push Library*/
			if(tmp1[1].find("platform")!=std::string::npos&&v.HasMember("natives"))
			{
				//last=tmp1[1]+"-"+tmp1[2]+"-"+native;
			}else
				last=tmp1[1]+"-"+tmp1[2];
			names=_cwd_+"/.minecraft/libraries/"+tmp1[0]+"/"+tmp1[1]+"/"+tmp1[2]+"/"+last+".jar";
			if(v.HasMember("downloads"))
			{
				Value& downloads=v["downloads"]["artifact"];
				libraries.Add(names,downloads["url"].GetString(),false,downloads["size"].GetInt());
			}else if(v.HasMember("url"))//todo:forge url
			{
				libraries.Add(names,v["url"].GetString(),false,-1);
			}else
			{
				libraries.Add(names,"null",false,-1);
			}
	}
}

bool AllowChecker(Value &val)
{
	bool allowed=false;
	if(!val.HasMember("rules"))
	{
		return true;
	}
	else 
	{
		Value& rules=val["rules"];
		if(!rules.Size())
		{
			return true;
		}
		else
		{
			for (auto &rule:rules.GetArray())
			{
				std::string action=rule["action"].GetString();
				if(!rule.HasMember("os"))
					allowed=(action=="allow");
				else
					if (rule["os"]["name"].GetString()=="windows")
						allowed=(action=="allow");
			}
			return allowed;
		}
	}
}

