#include "Libraries.h"

/*Library Part*/

bool Library::check()
{
	struct stat buffer;
	return (stat (path.c_str(), &buffer) == 0);
}

/*Libraries Part*/
void Libraries::Add(std::string path,std::string url,bool native,int size)
{
	library.push_back(Library(path,url,native,size));
}

std::vector<Library> Libraries::GetLostLib()
{
	std::vector<Library> res;
	lostlib.clear();
	for(int i=0;i<library.size();i++)
	{
		if(!library[i].check())
		{
			lostlib.push_back(i);
		}
	}
	for(int i=0;i<lostlib.size();i++)
	{
		res.push_back(library[lostlib[i]]);
	}
	return res;
}

std::string Libraries::toString()
{
	return library[0].path;
}
