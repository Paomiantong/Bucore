#include "Args.h"

Args::Args(){}

void Args::Add(std::string name, std::string value)
{
	args[name] = value;
}

bool Args::Delete(std::string name)
{
	return args.erase(name);
}

void Args::Reset(std::string name, std::string value)
{
	args[name] = value;
}

bool Args::Find(std::string name)
{
	if(args.find(name)!=args.end())
		return true;
	else
		return false;
}

std::string Args::ToString()
{
	std::string str;
	for (auto i : args)
	{
		str+=i.first+" "+i.second+" ";
	}
	return str;
}

std::string Args::GetValue(std::string name)
{
	if(Find(name))
		return args.find(name)->second;
	else
		return "";
}
