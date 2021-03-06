#include "Version.h"


Version::Version():isinit(0){}
Version::Version(std::string ver_json):isinit(0)
{
	VersionParser* parser = CreateVersionParser(ver_json,this);
	parser->Parse();
	delete parser;
	isinit = 1;
}

bool Version::IsInit()
{
	return isinit;
}

AssetIndex Version::GetAssets()
{
	return asidx;
}

Libraries Version::GetLibraries()
{
	return libraries;
}

std::string Version::GetId()
{
	return ver;
}

std::string Version::GetAssetIndex()
{
	return assetidx;
}

std::string Version::GetMainclass()
{
	return mainclass;
}

Args Version::GetMinecraftArguments()
{
	return minecraftarguments;
}

Args Version::GetJVMArguments()
{
	return jvmarguments;
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
				{
					std::string A=rule["os"]["name"].GetString(),B=B_OS;
					if (A==B)
						allowed=(action=="allow");
				}
			}
			return allowed;
		}
	}
}

VersionParser::VersionParser(std::string VersionJson_,Version* VersionPointer_)
{
	VersionPointer = VersionPointer_;
	VersionJson = VersionJson_;
	InitFlag = false;
}

void VersionParser::Parse()
{
	//let json string to be a json object
	std::string json = ReadF(VersionJson);
	if(json == "")
		return;
	Document dom;
	dom.Parse(json.c_str());
	
	// //get game version
	VersionPointer->ver = dom["id"].GetString();


	//get version mainclass
	VersionPointer->mainclass = dom["mainClass"].GetString();
	

	//get assetIndex, there will not be an assetIndex if the version is a modloader.
	if (dom.HasMember("assetIndex"))
	{
		VersionPointer->assetidx = dom["assetIndex"]["id"].GetString();
		VersionPointer->asidx = AssetIndex(dom["assetIndex"]["url"].GetString(), _cwd_ + "/.minecraft/assets/indexes/" + VersionPointer->assetidx + ".json");
	}

	//Arguments
	if(dom.HasMember("logging"))
	{
	std::string temp = dom["logging"]["client"]["argument"].GetString(),lid = dom["logging"]["client"]["file"]["id"].GetString();
	//"assets/log_configs"
	Replace(temp,"${path}","\""+_cwd_+"/assets/log_configs/"+lid+"\"",false);
	VersionPointer->loggingArg = temp;
	}
	
	//generate start arguments
	VersionPointer->jvmarguments = JVM_ARGS_D;
	VersionPointer->jvmarguments.Add(VersionPointer->loggingArg);
	VersionPointer->jvmarguments.Add("-cp","");

	if(dom.HasMember("minecraftArguments"))//after 1.13
	{
		std::string temp = dom["minecraftArguments"].GetString();
		std::vector<std::string> temp_vector = Split(temp," ");
		std::string pre = "";
		for(auto i : temp_vector)
		{
		
		   std::string temp_str = i;
		   if(temp_str.find("--")==std::string::npos)
		   	VersionPointer->minecraftarguments.Add(pre,temp_str);
		   else
		   	pre = temp_str;
		
		}
	}else if(dom.HasMember("arguments"))//1.13 and more
	{
		Value &Arg_Game = dom["arguments"]["game"];
		std::string pre = "";
		for(auto &a_v : Arg_Game.GetArray())
		{
			if(a_v.IsString())
			{
				std::string temp = a_v.GetString();
				if(temp.find("--")==std::string::npos)
					VersionPointer->minecraftarguments.Add(pre,temp);
				else
					pre = temp;
			}
		}
	}

	//if(dom.HasMember("jar"))
	
	//if the version is a modloader it will have inheritsFrom
	if(dom.HasMember("inheritsFrom"))
	{
		std::string ihf=dom["inheritsFrom"].GetString(),p=_cwd_+"/.minecraft/versions/"+ihf+"/"+ihf+".json";
		Version* TempVersion = new Version();
		VersionParser* parser = CreateVersionParser(p,TempVersion);

		parser->Parse();		
		if(!parser->IsInit())
		{
			delete parser;
			delete TempVersion;
			return;
		}
		VersionPointer->libraries = TempVersion->GetLibraries();
		VersionPointer->assetidx = TempVersion->GetAssetIndex();

		delete parser;
		delete TempVersion;

	}

	//load libraries
	LibrariesLoader(dom["libraries"]);

	//if the version is not a modloader , you should add itself to libraries
	if(!dom.HasMember("inheritsFrom"))
	{
		VersionPointer->libraries.Add(_cwd_+"/.minecraft/versions/"+VersionPointer->ver+"/",VersionPointer->ver+".jar","null","",false,-1);
	}

	InitFlag = true;
}


void VersionParser::LibrariesLoader(Value& data)
{
		for (auto& v : data.GetArray())
	{
			if (!AllowChecker(v))//Check Allow
			{
				continue;
			}
			//Split The name
			std::vector<std::string> tmp1=Split(v["name"].GetString(),":");
			std::string last,path;
			for (int x=0;x<tmp1[0].length();x++)
			{
				if(tmp1[0][x]=='.')
					tmp1[0][x]='/';
			}
			/*Native Part&Push Library*/
			std::string classifiers_key;
			if(v.HasMember("natives"))
			{
				classifiers_key =  v["natives"][B_OS].GetString();
				if(classifiers_key.find("${arch}"))
				{
					Replace(classifiers_key,"${arch}",_arch_,false);
				}
				last=tmp1[1]+"-"+tmp1[2]+"-"+classifiers_key+".jar";
			}else
				last=tmp1[1]+"-"+tmp1[2]+".jar";
			path=_cwd_+"/.minecraft/libraries/"+tmp1[0]+"/"+tmp1[1]+"/"+tmp1[2]+"/";
			if(v.HasMember("downloads"))
			{
				if(v["downloads"].HasMember("classifiers") && (classifiers_key != ""))
				{
					Value& downloads=v["downloads"]["classifiers"][classifiers_key.c_str()];
					VersionPointer->libraries.Add(path,last,downloads["url"].GetString(),downloads["sha1"].GetString(),true,downloads["size"].GetInt());
				}
				else if(v["downloads"].HasMember("artifact"))
				{
					Value& downloads=v["downloads"]["artifact"];
					VersionPointer->libraries.Add(path,last,downloads["url"].GetString(),downloads["sha1"].GetString(),false,downloads["size"].GetInt());
				}
			}
			else if(v.HasMember("url"))//TODO:forge url
				{
					VersionPointer->libraries.Add(path,last,v["url"].GetString(),"",false,-1);
				}
				else
				{
					VersionPointer->libraries.Add(path,last,"null","",false,-1);
				}
	}
}

bool VersionParser::IsInit()
{
	return InitFlag;
}

VersionParser* CreateVersionParser(std::string src, Version* VersionPointer_)
{
	return (new VersionParser(src,VersionPointer_));
}