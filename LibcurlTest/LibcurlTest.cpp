#include "stdafx.h"
#include "LibcurlHttpRequest.h"
using namespace std;
int main()
{
	string url = "http://192.168.1.24:8000";
	string data = "Hello server！";
	LibcurlHttpRequest *http = LibcurlHttpRequest::getInstance();
	string return_msg = http->httpGetReturnString(url);
	printf("%s\n", return_msg.c_str());
	http->httpPostDefault(url,data);
	
    return 0;
}

