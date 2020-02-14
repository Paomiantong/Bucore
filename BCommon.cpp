#ifndef BCOMMON_H
#define BCOMMON_H
#include <sstream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <tchar.h>
#include <conio.h>
namespace uuids = ::boost::uuids;
string GetBasePath(void)//获取工作路径
{  
    char szFilePath[MAX_PATH + 1]={0};  
    GetModuleFileNameA(NULL, szFilePath, MAX_PATH);  
    (strrchr(szFilePath, '\\'))[0] = 0;
    string path = szFilePath;  
  
    return path;  
}
bool _Replace(string &str1,string str2,string str3)
{
	if(str1.find(str2)!=string::npos)
	{
		str1.replace(str1.find(str2),str2.length(),str3);
		return 1;
	}
	return 0;
}
bool Replace(string &str1,string str2,string str3,bool loop=false)
{
	if(str1.find(str2)!=string::npos)
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
string read(string path)
{
	ifstream F(path.c_str());
	string str,tmp;
	while(getline(F,tmp))
	{
		str+=tmp;
	}
	F.close();
	return str;
}
int s2i(string str)
{
	stringstream ss;
	ss<<str;
	int num;
	ss>>num;
	return num;
}
string i2s(int num)
{
	stringstream ss;
	ss<<num;
	string str;
	ss>>str;
	return str;
}
vector<string> split(const string& str, const string& delim) {  
	vector<string> res;  
	if("" == str) return res;  
	//先将要切割的字符串从string类型转换为char*类型  
	char * strs = new char[str.length() + 1] ; //不要忘了  
	strcpy(strs, str.c_str());   
 
	char * d = new char[delim.length() + 1];  
	strcpy(d, delim.c_str());  
 
	char *p = strtok(strs, d);  
	while(p) {  
		string s = p; //分割得到的字符串转换为string类型  
		res.push_back(s); //存入结果数组  
		p = strtok(NULL, d);  
	}  
 
	return res;  
}
// 获取操作系统位数
string GetSystemBits()
{
	typedef void (WINAPI *LPFN_PGNSI)(LPSYSTEM_INFO); 
    SYSTEM_INFO si;
    LPFN_PGNSI pGNSI = (LPFN_PGNSI) GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "GetNativeSystemInfo");
    pGNSI(&si);
     if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
    {
        return "64";
    }
    return "32";
}
namespace uuids = ::boost::uuids;
string UUIDgenerator(string name)
{
	uuids::name_generator uuid_v5(uuids::string_generator()("980ed8f2-ca8b-43c0-969f-93934c94dcb3"));
	string uuid;
    stringstream x;
    x<<uuid_v5(name);
    x>>uuid;
    Replace(uuid,"-","",true);
	return uuid;
}
#endif
