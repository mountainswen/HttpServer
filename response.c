#include<string.h>
#include"response.h"
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>

static void parse_http_uri(char*,char*);
static void io_write(char*,int);
static void http_header(int);

int http_response(struct wen_request* request)
{
	// first check the request url
	char filename[100];

	parse_http_uri(request->wen_url,filename);
	
	io_write(filename,request->wen_fd);

	return 1; 
}

static void parse_http_uri(char* url,char*fiename)
{

}

static void io_write(char* filename,int fd)
{

}

static void http_header(int fd)
{

}


