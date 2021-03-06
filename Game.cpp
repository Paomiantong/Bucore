#include "Game.h"

void Game::Init()
{
	HttpR::HttpR_init();
}

Game::Game()
{
	config="test";
}

bool Game::LoadUser(User usr)
{
	user = usr;
	return true;
}

bool Game::LoadVersion(Version ver)
{
	if( !ver.IsInit() )
		return false;
	version = ver;
	return true;
}

User Game::GetUser()
{
	return user;
}

Version Game::GetVersion()
{
	return version;
}

std::string Game::GenerateStartArguments()
{
	std::string cwd = _cwd_;
	Args jvm = version.GetJVMArguments(), game = version.GetMinecraftArguments();

	jvm.Add("-Djava.library.path=\""+cwd+"/.minecraft/$natives/"+version.GetId()+"\"");
	jvm.Reset("-cp","\""+version.GetLibraries().ToClassPathArg()+"\" "+version.GetMainclass());

	game.Reset("--username","\""+user.GetName()+"\"");
	game.Reset("--version","\""+version.GetId()+"\"");
	game.Reset("--gameDir","\""+cwd+"/.minecraft\"");
	game.Reset("--assetsDir","\""+cwd+"/.minecraft/assets\"");
	game.Reset("--assetIndex",version.GetAssetIndex());
	game.Reset("--uuid",user.Getuuid());
	game.Reset("--accessToken",user.GetaccessToken());
	game.Reset("--userType",user.GetType());
	game.Reset("--versionType","Bucore");
	if(game.Find("--userProperties"))
		game.Reset("--userProperties","{}");


	return jvm.ToString()+game.ToString();

}
