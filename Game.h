//Here Are Someting 
#ifndef BC_GAME_H
#define BC_GAME_H

#include <string>

#include "Version.h"
//#include "User.h"

class Game
{
	private:
		Version vsersion;
//		User user;
	public:
		Game();
		void LoadVersion(Version ver);
		Version GetVersion();
		std::string config;
};

#endif
