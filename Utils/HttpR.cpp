#include "HttpR.h"

HttpR::HttpR(std::string host,bool _IsSSL):h_host(host),IsSSL(_IsSSL){}

void HttpR::HttpR_init()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

size_t HttpR::CurlWriteBuffer(char *buffer, size_t size, size_t nmemb, std::string* stream)
{
	//第二个参数为每个数据的大小，第三个为数据个数，最后一个为接收变量
	size_t sizes = size*nmemb;
	if(stream == NULL) 
		return 0;
	stream->append(buffer,sizes);
	return sizes;
}

std::string HttpR::httpRequest(std::string url,bool IsPOST,std::string pCon)
{
	CURL* pCurl=NULL;
	CURLcode res;
	std::string response;
	pCurl = curl_easy_init();	
	if(pCurl==NULL)
		return "Failed to InitpCurl";
	//设置请求头
	struct	curl_slist* header_ = NULL;
	header_ = curl_slist_append(header_,"Content-Type: application/json;charset=utf-8");
	
	//添加请求头到handle
	curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, header_);
	
	//设置URL
	curl_easy_setopt(pCurl, CURLOPT_URL, url.c_str());	
 
	if(IsPOST == true)
	{
		curl_easy_setopt(pCurl,CURLOPT_POSTFIELDS,pCon.c_str());			   //post请求消息数据	 
		curl_easy_setopt(pCurl,CURLOPT_POSTFIELDSIZE,pCon.length());		   //消息长度
	}
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, CurlWriteBuffer);
	curl_easy_setopt(pCurl,CURLOPT_WRITEDATA,&response);//数据接收变量
	curl_easy_setopt(pCurl,CURLOPT_TIMEOUT,10000);	//连接超时时间
 
	//不支持ssl验证
	if(IsSSL == 0)
	{
		curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0);//设定为不验证证书和HOST
		curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);
	}
	else
	{
		curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0L);		
	}
	
	//执行http连接
	res = curl_easy_perform(pCurl);
	//清除消息头
	curl_slist_free_all(header_);
	//清除handle
	curl_easy_cleanup(pCurl);
 
	return response;
}

std::string HttpR::GET(std::string path, std::string con)
{
	std::string url=h_host+path+"?"+con;
	return httpRequest(url);
}


std::string HttpR::POST(std::string path, std::string con)
{
	return httpRequest(h_host+path,true,con);
}
