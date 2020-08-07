#include "User.h"

User::User(){}

User::User(std::string n):Name(n){Type="Legacy";}

User::User(std::string email,std::string passwords,std::string clientToken)
{
	Auth(email,passwords,clientToken);
}

std::string User::Getuuid()
{
	return uuid;
}

std::string User::GetName()
{
	return Name;
}

std::string User::GetType()
{
	return Type;
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

std::string User::Auth(std::string email, std::string passwords, std::string clientToken)
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
	Name = dom["selectedProfile"]["name"].GetString();
	uuid = dom["selectedProfile"]["id"].GetString();
	Type = "Mojang";

	return dom["clientToken"].GetString();
}

bool User::AuthToken(std::string Token, std::string clientToken)
{
	HttpR hr=HttpR("https://authserver.mojang.com",true);

	std::stringstream str;
	str<<"{";
	str<<"\"accessToken\": \""+Token+"\"";
	if(clientToken!="")
		str<<",\"clientToken\":\""+clientToken+"\"";
	str<<"}";
	
	hr.POST("/validate",str.str());

	if(hr.GetHttpCode() == 204)
		return true;
	else 
		return false;

}
