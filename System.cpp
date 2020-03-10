#include "System.h"
std::string GetDir()
{
	std::string executeFile;
#ifdef __WIN32
    char path[BC_MAXPATH]; GetModuleFileNameA(NULL,path,MAX_PATH);
    executeFile = path;
#else
    char path[1024];
    int cnt = readlink("/proc/self/exe", path, 1024);
    executeFile=path;
#endif
		std::string dirName = executeFile.substr(0, executeFile.find_last_of("/\\"));
    return dirName;
}

bool Checkfile (std::string file)
{
#ifdef __WIN32
	return (_access(file.c_str(), 0) != -1);
#else	
	struct stat buffer;
	return (stat (file.c_str(), &buffer) == 0);
#endif
}

int Getarch()
{

}
