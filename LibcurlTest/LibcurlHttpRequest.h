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
	/******'GET'��ʽ����******/
	//1.�����յ������ݴ浽����
	void httpGetSaveLocation(string url);
	//2.�����յ���������Ϊstring����
	string httpGetReturnString(string url);

	/*****'POST'��ʽ����*****/
	//1.Ĭ��read function��ʽ
	void httpPostDefault(string url, string data);
	//2.ʹ�ö���read function
	void httpPostCustom(string url, string data);

	/***custom function***/
	static size_t readData(void *buffer, size_t size, size_t nmemb, void *usedata);
	static size_t OnWriteData(void *buffer, size_t size, size_t nmemb, void *usedata);
};

