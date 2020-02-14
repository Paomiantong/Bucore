#ifndef BC_USER_H
#define BC_USER_H
class User
{
	public:
		std::string name;
		std::string type;
		std::string uuid;
		void login(std::string email,std::string passwords);
};
#endif
