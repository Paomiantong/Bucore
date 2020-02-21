#ifndef B_UTILS_HTTP_H
#define B_UTILS_HTTP_H

#ifdef __WIN32__
#include <WinSock.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#endif

#include <sstream>
#include <string>
#include <cstring>

class BHttpRequest
{
	private:
		std::string h_host;
		int h_port;
	public:
	BHttpRequest(std::string host,int port);
	~BHttpRequest();
	std::string httpSocket(std::string request);
	std::string POST(std::string path,std::string content);
	std::string GET(std::string path,std::string content);

};

#endif
