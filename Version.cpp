#include "Version.h"

Version::Version(){}
Version::Version(std::string ver_json)
{
	std::string json = read(ver_json);
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
			}
		}
	}
	//if(dom.HasMember("jar"))
	if(dom.HasMember("inheritsFrom"))
	{
		//todo:add current path
		std::string ihf=dom["inheritsFrom"].GetString(),p=_dirname_+"/.minecraft/version/"+ihf+"/"+ihf+".json";
		Version father(p);
		//test
		//Version father("testdata/1.10.2.json");
		libraries=father.libraries;	
	}
	Lib_load(dom["libraries"]);
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
			names=_dirname_+"/.minecraft/libraries/"+tmp1[0]+"/"+tmp1[1]+"/"+tmp1[2]+"/"+last+".jar;";
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

bool _Replace(std::string &str1,std::string str2,std::string str3)
{
	if(str1.find(str2)!=std::string::npos)
	{
		str1.replace(str1.find(str2),str2.length(),str3);
		return 1;
	}
	return 0;
}

bool Replace(std::string &str1,std::string str2,std::string str3,bool loop=false)
{
	if(str1.find(str2)!=std::string::npos)
	{
		if (loop)
		{
			while(_Replace(str1,str2,str3));
		}else
		{
			_Replace(str1,str2,str3);
		}
		return 1;
	}
	return 0;
}

std::string read(std::string path)
{
	std::ifstream F(path.c_str());
	std::string str,tmp;
	while(getline(F,tmp))
	{
		str+=tmp;
	}
	F.close();
	return str;
}

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> res;
	if("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型  
	char * strs = new char[str.length() + 1] ; //不要忘了  
	strcpy(strs, str.c_str());
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
	char *p = strtok(strs, d);
	while(p) {
		std::string s = p; //分割得到的字符串转换为string类型  
		res.push_back(s); //存入结果数组  
		p = strtok(NULL, d);
	}
	return res;
}
