#include "HttpRequest.h"

#ifdef __WIN32__
#pragma comment(lib,"ws2_32.lib")
#endif

BHttpRequest::BHttpRequest(std::string host,int port):h_host(host),h_port(port)
{
	//init4win32
#ifdef __WIN32__
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

BHttpRequest::~BHttpRequest(){}

std::string BHttpRequest::httpSocket(std::string request)
{
	std::stringstream ret;
	int sockfd;
	struct sockaddr_in address;
	struct hostent *server;
 
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_port = htons(h_port);
	server = gethostbyname(h_host.c_str());
	memcpy((char *)&address.sin_addr.s_addr,(char*)server->h_addr, server->h_length);
 
	if(-1 == connect(sockfd,(struct sockaddr *)&address,sizeof(address))){
		return "connect error";
    }
 
#ifdef WIN32
	send(sockfd, request.c_str(),request.size(),0);
#else
	write(sockfd,request.c_str(),request.size());
#endif
	char buffer[1024*1024] = {0};
	int offset = 0;
	int recv_;
 
#ifdef WIN32
	while(recv_ = recv(sockfd, buffer+offset, 1024,0))
#else
	while(recv_ = read(sockfd, buffer+offset, 1024))
#endif
	{
		offset += recv_;
	}
 
#ifdef WIN32
	closesocket(sockfd);
#else
	close(sockfd);
#endif
	buffer[offset] = 0;
	ret<<buffer;
	return ret.str();
}

std::string BHttpRequest::POST(std::string path,std::string content)
{
	std::stringstream stream;
	stream << "POST " << path;
	stream << " HTTP/1.0\r\n";
	stream << "Host: "<< h_host << "\r\n";
	stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream << "Content-Type:application/x-www-form-urlencoded\r\n";
	stream << "Content-Length:" <<content.length()<<"\r\n";
	stream << "Connection:close\r\n\r\n";
	stream << content.c_str();
	return httpSocket(stream.str());
}

std::string BHttpRequest::GET(std::string path,std::string content)
{
	std::stringstream stream;
	stream << "GET " << path << "?" << content;
	stream << " HTTP/1.0\r\n";
	stream << "Host: " << h_host << "\r\n";
	stream <<"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream <<"Connection:close\r\n\r\n";

	return httpSocket(stream.str());
}
