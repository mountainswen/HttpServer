#include<fcntl.h>
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
	if(strcmp(url,"/") == 0)
		filename = "index.html";
	else 
		return ;
}

static void io_write(char* filename,int fd)
{
	http_header();

	char path[100] = "html/";
	strcat(path,filename);

	int file = open(path,O_RDONLY);

	char buf[1024];
	int count = read(file,buf,sizeof buf);
	
	while(count != 0)
	{
		write(fd,buf,count);
		count = read(file,buf,sizeof buf);
	}
}

static void http_header(int fd)
{
	
}


