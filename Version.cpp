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
		std::string temp = dom["minecraftArguments"].GetString();
		std::vector<std::string> temp_vector = split(temp," ");
		std::string pre = "";
		for(auto i : temp_vector)
		{
		
		   std::string temp_str = i;
		   if(temp_str.find("$")!=std::string::npos)
		   	minecraftarguments.Add(pre,temp_str);
		   else
		   	pre = temp_str;
		
		}
	}else if(dom.HasMember("arguments"))//1.13 and more
	{
		Value &Arg_Game = dom["arguments"]["game"],&Arg_Jvm = dom["arguments"]["jvm"];
		std::string pre = "";
		for(auto &a_v : Arg_Game.GetArray())
		{
			if(a_v.IsString())
			{
				std::string temp = a_v.GetString();
				if(temp.find("$")!=std::string::npos)
					minecraftarguments.Add(pre,temp);
				else
					pre = temp;
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

Args Version::GetMinecraftArguments()
{
	return minecraftarguments;
}

void Version::Lib_load(Value& data)
{
	for (auto& v : data.GetArray())
	{
			if (!AllowChecker(v))//Check Allow
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
			std::string classifiers_key;
			if(tmp1[1].find("platform")!=std::string::npos&&v.HasMember("natives"))
			{
				classifiers_key =  v["natives"][B_OS].GetString();
				///* TODO: Add arch <25-02-20, yourname> */
				if(classifiers_key.find("${arch}"))
				{
					Replace(classifiers_key,"${arch}","32",false);
				}
				last=tmp1[1]+"-"+tmp1[2]+"-"+classifiers_key;
			}else
				last=tmp1[1]+"-"+tmp1[2];
			names=_cwd_+"/.minecraft/libraries/"+tmp1[0]+"/"+tmp1[1]+"/"+tmp1[2]+"/"+last+".jar";
			if(v.HasMember("downloads"))
			{
				if(v["downloads"].HasMember("classifiers"))
				{
					Value& downloads=v["downloads"]["classifiers"][classifiers_key.c_str()];
					libraries.Add(names,downloads["url"].GetString(),false,downloads["size"].GetInt());
				}
				else
				{
					Value& downloads=v["downloads"]["artifact"];
					libraries.Add(names,downloads["url"].GetString(),false,downloads["size"].GetInt());
				}
			}
			else if(v.HasMember("url"))//todo:forge url
				{
					libraries.Add(names,v["url"].GetString(),false,-1);
				}
				else
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
					if (rule["os"]["name"].GetString()==B_OS)
						allowed=(action=="allow");
			}
			return allowed;
		}
	}
}

