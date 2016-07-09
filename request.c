#include<sys/socket.h>
#include "response.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "request.h" 
#include<time.h>
#include<string.h>
int parse_request(struct wen_request*);
int get_line(int,char*,int);
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
	sleep(1);
	//如果send数据之后立即调用close可能会导致对端没有接收到完整的数据
	close(request->wen_fd);
	free(request);
}

void do_request(struct wen_request *request)
{
	if(!parse_request(request)){
		bad_request(request);
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

int parse_request(struct wen_request *request)
{

	if(!parse_request_line(request))return FALSE;
	
//	printf(request->wen_url);

	return TRUE;
}

int parse_request_line(struct wen_request* request)
{
	printf("parse request line\n");
	char request_line[1024];
	int count = get_line(request->wen_fd,request_line,1024);	
	if(count == 0)
	{
		printf("count is zero\n");
		wen_free(request);
		return FALSE;
	}

	int idx = 0;
	char method[10];
	memset(method,0,10);
	char http_ver[10];
	int flag = 0;
	int i=0;
	while(1)
	{
		if(request_line[idx] == '\n')break;
		
		if(flag == 0)
		{
			if(request_line[idx] != ' ')method[i++] = request_line[idx]; 
			else{
				i=0;
				flag ++;
				idx++;
				continue;
			}
		}
		else if(flag == 1)
		{
			if(request_line[idx] != ' ')request->wen_url[i++] = request_line[idx];
			else
			{
				i=0;
				flag++;
				idx++;
				continue;
			}
		}

		else
		{
			if(request_line[idx] != ' ')http_ver[i++] = request_line[idx];
			else
			{
				break;
			}
		}
		idx++;
	}
//	printf(method);
//	printf("\n");
//	printf(request.wen_url);
//	printf("\n");
//	printf(http_ver);

	request->wen_method = http_method(method);
	request->wen_version = http_version(http_ver);
	
	return TRUE;
}

int get_line(int fd,char *buf,int size)
{
	int i=0;
	char c = '\0';
	int n;
//	printf("size is : %d\n",size);
	while(i < size-1 && c!='\n')
	{
		n = recv(fd,&c,1,0);
		if(n>0)
		{
			if(c == '\r')
			{
				n = recv(fd,&c,1,MSG_PEEK);
				if(c =='\n' && n > 0)
					recv(fd,&c,1,0);
				else
					c = '\n';
			}
			buf[i] = c;
			i++;
		}
		else
			c = '\n';
	}

	buf[i] = '\0';

	return i;
}

