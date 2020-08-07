#include "HttpR.h"

HttpR::HttpR(std::string host,bool _IsSSL):h_host(host),IsSSL(_IsSSL){}

void HttpR::HttpR_init()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

size_t HttpR::CurlWriteBuffer(char *buffer, size_t size, size_t nmemb, std::string* stream)
{
	size_t sizes = size*nmemb;
	if(stream == NULL) 
		return 0;
	stream->append(buffer,sizes);
	return sizes;
}

std::string HttpR::HttpRequest(std::string url,bool IsPOST,std::string postcon)
{
	CURL* CurlPointer=NULL;
	CURLcode Result;
	std::string Response;
	CurlPointer = curl_easy_init();	
	if(CurlPointer==NULL)
		return "Failed to Init CurlPointer";
	//设置请求头
	struct	curl_slist* header_ = NULL;
	header_ = curl_slist_append(header_,"Content-Type: application/json;charset=utf-8");

	curl_easy_setopt(CurlPointer, CURLOPT_HTTPHEADER, header_);
	
	curl_easy_setopt(CurlPointer, CURLOPT_URL, url.c_str());	
 
	if(IsPOST == true)
	{
		curl_easy_setopt(CurlPointer,CURLOPT_POSTFIELDS,postcon.c_str());	
		curl_easy_setopt(CurlPointer,CURLOPT_POSTFIELDSIZE,postcon.length());
	}
	curl_easy_setopt(CurlPointer, CURLOPT_WRITEFUNCTION, CurlWriteBuffer);
	curl_easy_setopt(CurlPointer,CURLOPT_WRITEDATA,&Response);
	curl_easy_setopt(CurlPointer,CURLOPT_TIMEOUT,10000);
 
	if(IsSSL == 0)
	{
		curl_easy_setopt(CurlPointer, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(CurlPointer, CURLOPT_SSL_VERIFYHOST, 0);
	}
	else
	{
		curl_easy_setopt(CurlPointer, CURLOPT_SSL_VERIFYPEER, 0L);		
	}
	
	Result = curl_easy_perform(CurlPointer);
	if(Result == 0)
	{
		curl_easy_getinfo(CurlPointer, CURLINFO_RESPONSE_CODE, &httpcode);
	}
	curl_slist_free_all(header_);
	curl_easy_cleanup(CurlPointer);
 
	return Response;
}

std::string HttpR::GET(std::string path, std::string con)
{
	std::string url=h_host+path+"?"+con;
	return HttpRequest(url);
}


std::string HttpR::POST(std::string path, std::string con)
{
	return HttpRequest(h_host+path,true,con);
}

long HttpR::GetHttpCode()
{
	return httpcode;
}
