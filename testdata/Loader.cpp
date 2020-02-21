#include "rapidjson/document.h"
#include <iostream>
#include <vector>
#include <map>
#include "stdlib.h"
using namespace std;
#include "Core.h"
using namespace rapidjson;
bool AllowChecker(Value &val);
string ParseLibrary(Value& lval,Launcher &Lau);
void Load(Launcher &Lau,string filename)
{
	string json=read(filename);
	Document dom;
	dom.Parse(json.c_str());
	Lau.pbase=GetBasePath();//获得工作路径
	Lau.id=dom["id"].GetString();//获得Id
	Lau.mainclass=dom["mainClass"].GetString();//获得mainclass
	Lau.vtype=dom["type"].GetString();
	if(dom.HasMember("assetIndex"))
		Lau.asindex=dom["assetIndex"]["id"].GetString();
	Lau.mcargs=dom["minecraftArguments"].GetString();
	Lau.plibs+=ParseLibrary(dom,Lau);
	if(dom.HasMember("jar"))
		Lau.plibs+=Lau.pbase+Lau.gmdir+"\\versions\\"+Lau.fatherid+"\\"+Lau.fatherid+".jar";
	else
		Lau.plibs+=Lau.pbase+Lau.gmdir+"\\versions\\"+Lau.id+"\\"+Lau.id+".jar";
	Lau.DealminecraftArguments();
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
				string action=rule["action"].GetString();
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
string ParseLibrary(Value& lval,Launcher &Lau)
{
	string Libs_="";
	Value& libs=lval["libraries"];
	for (auto& v : libs.GetArray())
	{
			if (v.HasMember("extract")||!AllowChecker(v))
			{
				continue;
			}
			vector<string> tmp1=split(v["name"].GetString(),":");
			string names="",last,native;
			for (int x=0;x<tmp1[0].length();x++)
			{
				if(tmp1[0][x]=='.')
					tmp1[0][x]='\\';
			}
			if(tmp1[1].find("platform")!=string::npos&&v.HasMember("natives"))
			{
				Value& natives_=v["natives"];
				native=v["natives"]["windows"].GetString();
				if(native.find("${arch}")!=string::npos)
					Replace(native,"${arch}",GetSystemBits());
				last=tmp1[1]+"-"+tmp1[2]+"-"+native;
			}else
				last=tmp1[1]+"-"+tmp1[2];
			names=Lau.pbase+Lau.gmdir+"\\libraries\\"+tmp1[0]+"\\"+tmp1[1]+"\\"+tmp1[2]+"\\"+last+".jar;";
			Libs_+=names;
	}
	if(lval.HasMember("inheritsFrom"))
	{
		string json=read(Lau.pbase+Lau.gmdir+"\\versions\\"+lval["inheritsFrom"].GetString()+"\\"+lval["inheritsFrom"].GetString()+".json");
		Document _dom;
		_dom.Parse(json.c_str());
		Lau.Setinner(lval["inheritsFrom"].GetString());
		if(_dom.HasMember("assetIndex"))
			Lau.asindex=_dom["assetIndex"]["id"].GetString();
		return Libs_+ParseLibrary(_dom,Lau);
	}
	else
		return Libs_;
}
