#include "stdafx.h"
#include "LibcurlHttpRequest.h"
#include <curl/curl.h>

LibcurlHttpRequest::LibcurlHttpRequest()
{
}


LibcurlHttpRequest::~LibcurlHttpRequest()
{
}
LibcurlHttpRequest *LibcurlHttpRequest::getInstance()
{
	LibcurlHttpRequest *http = new LibcurlHttpRequest();
	if (http)
	{
		return http;
	}
	return nullptr;
}
//'GET'方式
void LibcurlHttpRequest::httpGetSaveLocation(string url)
{
// 	string body;
// 	string heady;
// 	CURL *curl;
// 	CURLcode res;
// 	FILE *file = fopen("./resp.html", "w");
// 
// 	struct curl_slist *headers = NULL;
// 	headers = curl_slist_append(headers, "Accept:Agent-000");
// 	curl = curl_easy_init();
// 	if (curl)
// 	{
// 		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
// 		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
// 		curl_easy_setopt(curl, CURLOPT_READFUNCTION, LibcurlHttpRequest::readData);
// 		curl_easy_setopt(curl, CURLOPT_HEADERDATA, file);
// 		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlHttpRequest::OnWriteData);
// 		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
// 		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
// 		res = curl_easy_perform(curl);
// 		if (res != 0)
// 		{
// 			curl_slist_free_all(headers);
// 		}
// 	}
// 	fclose(file);
// 	curl_easy_cleanup(curl);
}
string LibcurlHttpRequest::httpGetReturnString(string url)
{
	string body;
	string heady;
	CURL *curl;
	CURLcode res;

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept:Agent-000");
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, LibcurlHttpRequest::readData);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlHttpRequest::OnWriteData);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&body);
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
		res = curl_easy_perform(curl);
		if (res != 0)
		{
			curl_slist_free_all(headers);
		}
	}
	curl_easy_cleanup(curl);
	return body;
}
//'POST'方式
void LibcurlHttpRequest::httpPostDefault(string url, string data)
{
	string resp_data;

	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlHttpRequest::OnWriteData);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&resp_data);
		curl_easy_setopt(curl, CURLOPT_READDATA, LibcurlHttpRequest::readData);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(data.c_str()));
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1);
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
}
void LibcurlHttpRequest::httpPostCustom(string url, string data)
{
	string resp_data;
	struct WriteThis pooh;
	pooh.readptr = data.c_str();
	pooh.sizeleft = (long)strlen(data.c_str());
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&resp_data);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, readData);

		curl_easy_setopt(curl, CURLOPT_READDATA, &pooh);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, pooh.sizeleft);

		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
}
size_t LibcurlHttpRequest::OnWriteData(void *buffer, size_t size, size_t nmemb, void *usedata)
{
	string *str = dynamic_cast<string *>((string *)usedata);
	if (NULL == str || NULL == buffer)
	{
		return -1;
	}
	char *pData = (char *)buffer;
	str->append(pData, size * nmemb);
	return nmemb;
}
size_t LibcurlHttpRequest::readData(void *buffer, size_t size, size_t nmemb, void *usedata)
{
	struct WriteThis *data = (struct WriteThis *)usedata;
	if (data == NULL)
	{
		return -1;
	}
	if (size * nmemb < 1)
	{
		return 0;
	}
	if (data->sizeleft)
	{
		*(char *)buffer = data->readptr[0];
		data->readptr++;
		data->sizeleft--;
		return 1;
	}
	return 0;
}