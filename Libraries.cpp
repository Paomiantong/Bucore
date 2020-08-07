#include "Libraries.h"

/*Library Part*/

bool Library::Check()
{
	return _exist_(Path+Name);
}

/*Libraries Part*/
void Libraries::Add(std::string path, std::string name, std::string url, std::string sha1, bool native, int size)
{
	library.push_back(Library(path,name,url,sha1,native,size));
}

std::vector<Library> Libraries::GetLostLib()
{
	std::vector<Library> res;
	lostlib.clear();
	for(int i=0;i<library.size();i++)
	{
		if(!library[i].Check())
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

std::vector<Library> Libraries::GetNativeLib()
{
	std::vector<Library> res;
	for(int i=0;i<library.size();i++)
	{
		if(library[i].Native)
		{
			nativelib.push_back(i);
		}
	}
	for(int i=0;i<nativelib.size();i++)
	{
		res.push_back(library[nativelib[i]]);
	}
	return res;
}

std::vector<Library> Libraries::GetAll()
{
	return library;
}

std::string Libraries::ToClassPathArg()
{
	std::string temp;
	for(int i=0;i<library.size();i++)
	{
		if(!library[i].Native)
		{
			if(i!=library.size()-1)
				temp+=library[i].Path+library[i].Name+";";
			else
				temp+=library[i].Path+library[i].Name;
		}

	}
	return temp;
}
