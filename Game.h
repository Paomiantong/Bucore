//Here Are Someting 
#ifndef BC_GAME_H
#define BC_GAME_H

#include <string>

#include "Version.h"
#include "User.h"

class Game
{
	private:
		Version vsersion;
		User user;
	public:
		static void Init();
		Game();
		void LoadVersion(Version ver);
		void LoadUser(User usr);
		Version GetVersion();
		User GetUser();
		std::string config;
};

#endif
