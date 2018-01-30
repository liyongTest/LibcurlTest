#pragma once
#include <iostream>
using namespace std;
struct WriteThis {
	const char *readptr;
	long sizeleft;
};
class LibcurlHttpRequest
{
public:
	LibcurlHttpRequest();
	~LibcurlHttpRequest();
	static LibcurlHttpRequest *getInstance();
public:
	/******'GET'方式请求******/
	//1.将接收到得数据存到本地
	void httpGetSaveLocation(string url);
	//2.将接收到的数据作为string返回
	string httpGetReturnString(string url);

	/*****'POST'方式请求*****/
	//1.默认read function方式
	void httpPostDefault(string url, string data);
	//2.使用定制read function
	void httpPostCustom(string url, string data);

	/***custom function***/
	static size_t readData(void *buffer, size_t size, size_t nmemb, void *usedata);
	static size_t OnWriteData(void *buffer, size_t size, size_t nmemb, void *usedata);
};

