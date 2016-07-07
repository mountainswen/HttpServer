#include<string.h>
#include"response.h"
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>

int http_response(struct wen_request* request)
{
	// first check the request url
	if(strcmp(request->wen_url,"/") == 0);
	return 1; 
}
