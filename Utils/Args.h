#ifndef B_ARGS_H
#define B_ARGS_H

#include <string>
#include <map>

class Args
{
private:
	std::map<std::string, std::string> args;
public:
	Args();
	void Add(std::string name, std::string value);
	void Reset(std::string name, std::string value);
	bool Delete(std::string name);
	bool Find(std::string name);
	std::string ToString();
	std::string GetValue(std::string name);
};

#endif /* B_ARGS_H */
