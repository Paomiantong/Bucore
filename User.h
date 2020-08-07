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
		std::string Name;
		std::string Type;
		std::string uuid;
		std::string accessToken;
	public:
		User();
		User(std::string n);
		User(std::string email,std::string passwords,std::string clientToken="");
		std::string Getuuid();
		std::string GetName();
		std::string GetType();
		std::string GetaccessToken();
		void Setuuid(std::string u);
		void SetaccessToken(std::string a);
		std::string Auth(std::string email,std::string passwords,std::string clientToken="");
		static bool AuthToken(std::string Token, std::string clientToken="");
};
#endif
