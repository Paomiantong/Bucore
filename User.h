#ifndef BC_USER_H
#define BC_USER_H

#include <string>
#include <sstream>
#include <rapidjson/document.h>

using namespace rapidjson;

#include "Utils/HttpR.h"

class User
{
	private:
		std::string name;
		std::string type;
		std::string uuid;
		std::string accessToken;
	public:
		User();
		User(std::string n);
		std::string Getuuid();
		std::string Getname();
		std::string Gettype();
		std::string GetaccessToken();
		std::string auth(std::string email,std::string passwords,std::string clientToken="");
};
#endif
