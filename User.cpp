#include "User.h"

User::User(){}

User::User(std::string n):name(n){type="Legacy";}

User::User(std::string email,std::string passwords,std::string clientToken)
{
	auth(email,passwords,clientToken);
}

std::string User::Getuuid()
{
	return uuid;
}

std::string User::Getname()
{
	return name;
}

std::string User::Gettype()
{
	return type;
}

std::string User::GetaccessToken()
{
	return accessToken;
}

void User::Setuuid(std::string u)
{
	uuid = u;
}

void User::SetaccessToken(std::string a)
{
	accessToken = a;
}

std::string User::auth(std::string email, std::string passwords, std::string clientToken)
{
	HttpR hr=HttpR("https://authserver.mojang.com",true);

	Document dom;

	std::stringstream str;
	str<<"{\"agent\": {\"name\": \"Minecraft\",\"version\": 1},";
	if(clientToken!="")
		str<<"\"clientToken\":\""+clientToken+"\",";
	str<<"\"username\": \""+email+"\",";
	str<<"\"password\": \""+passwords+"\"}";
	
	std::string authdate=hr.POST("/authenticate",str.str());
	dom.Parse(authdate.c_str());

	if(dom.HasMember("error"))
	{
		std::string error = dom["error"].GetString(),errormsg = dom["errorMessage"].GetString();
		return error+errormsg;
	}

	accessToken = dom["accessToken"].GetString();
	name = dom["selectedProfile"]["name"].GetString();
	uuid = dom["selectedProfile"]["id"].GetString();
	type = "Mojang";

	return dom["clientToken"].GetString();
}
