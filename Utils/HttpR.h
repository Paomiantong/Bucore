#ifndef B_HTTPR_H
#define B_HTTPR_H

#include <curl/curl.h>
#include <string>

class HttpR
{
	private:
		std::string h_host;
		bool IsSSL;
		long httpcode;
	public:
		HttpR(std::string host,bool _IsSSL);
		std::string GET(std::string path,std::string con);
		std::string POST(std::string path,std::string con);
		std::string httpRequest(std::string url,bool IsPOST=false,std::string pCon="");
		long GetHttpCode();
		static void HttpR_init();
		static size_t CurlWriteBuffer(char *buffer, size_t size, size_t nmemb, std::string* stream);
};

#endif
