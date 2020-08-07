#include "System.h"
std::string GetDir()
{
	std::string executeFile;
#ifdef _WIN32
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

bool CheckFile (std::string file)
{
#ifdef _WIN32
	return (_access(file.c_str(), 0) != -1);
#else	
	struct stat buffer;
	return (stat (file.c_str(), &buffer) == 0);
#endif
}

std::string GetArch()
{
#ifdef _WIN32
	typedef void (WINAPI *LPFN_PGNSI)(LPSYSTEM_INFO); 
    SYSTEM_INFO si;
    LPFN_PGNSI pGNSI = (LPFN_PGNSI) GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "GetNativeSystemInfo");
    pGNSI(&si);
     if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
    {
        return "64";
    }
    return "32";
#else
	return "32";
#endif
}
