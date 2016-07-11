#include<sys/socket.h>
#include "response.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "request.h" 
#include<time.h>
#include<string.h>
int parse_request(struct wen_request*);
//int get_line(int,char*,int);
int bad_request(struct wen_request*);
int parse_request_line(struct wen_request*);
void wen_free(struct wen_request*);
METHOD http_method(char*);
VERSION http_version(char*);

METHOD http_method(char* method)
{
	if(strcmp(method,"POST"))return POST;
	if(strcmp(method,"GET")) return GET;

	return 0;
}

VERSION http_version(char*http)
{
	if(strcmp(http,"HTTP/1.0"))return HTTP_1_0;
	if(strcmp(http,"HTTP/1.1"))return HTTP_1_1;
	
	return 0;
}

void wen_free(struct wen_request *request)
{
//	send(request->wen_fd);
//	sleep(1);
	//如果send数据之后立即调用close可能会导致对端没有接收到完整的数据
//	close(request->wen_fd);
	shutdown(request->wen_fd,SHUT_WR);
	free(request);
}

void do_request(struct wen_request *request)
{
	if(!parse_request(request)){
		bad_request(request);
		wen_free(request);
		return ;
	}

	http_response(request);

	wen_free(request);
}

int bad_request(struct wen_request *request)
{
	int client = request->wen_fd;
	printf("response with bad request\n");
	char buf[1024];

	int c =  sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
	send(client,buf,c,0);
	c = sprintf(buf, "Content-type: text/html\r\n");
	send(client, buf, c, 0);

	c = sprintf(buf, "\r\n");
	send(client, buf, c, 0);
	c = sprintf(buf, "<P>Your browser sent a bad request, ");
	send(client, buf, c, 0);
	c = sprintf(buf, "such as a POST without a Content-Length.\r\n");
	send(client, buf, c, 0);
	
	return 1;
}

void init_request(struct wen_request* request,int fd)
{
	request->wen_fd = fd;
	request->pos_first = request->pos_last = 0;
	memset(request->BUF,0,sizeof request->BUF);
}

int parse_request(struct wen_request *request)
{
	
}	

int parse_request_line(struct wen_request* request)
{
	
}


