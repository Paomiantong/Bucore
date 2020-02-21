#include "Tools.h"
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

std::string ReadF(std::string path)
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
	char * strs = new char[str.length() + 1] ; 
	strcpy(strs, str.c_str());
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
	char *p = strtok(strs, d);
	while(p) {
		std::string s = p;
		res.push_back(s); 
		p = strtok(NULL, d);
	}
	return res;
}
