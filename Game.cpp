#include "Game.h"
Game::Game()
{
	config="test";
}
void Game::LoadVersion(Version ver)
{
	vsersion=ver;
}

Version Game::GetVersion()
{
	return vsersion;
}
