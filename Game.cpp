#include "Game.h"

void Game::Init()
{
	HttpR::HttpR_init();
}

Game::Game()
{
	config="test";
}

void Game::LoadUser(User usr)
{
	user = usr;
}

void Game::LoadVersion(Version ver)
{
	vsersion = ver;
}

User Game::GetUser()
{
	return user;
}

Version Game::GetVersion()
{
	return vsersion;
}
