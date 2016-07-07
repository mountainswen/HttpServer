#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "request.h" 
#include<string.h>
int parse_request(struct wen_request);
int get_line(int,char*,int);
int bad_request(struct wen_request);
int parse_request_line(struct wen_request);
void wen_free(struct wen_request);

void wen_free(struct wen_request request)
{
	close(request.wen_fd);
}

void do_request(struct wen_request request)
{
	if(!parse_request(request)){bad_request(request);return ;}
}

int bad_request(struct wen_request request)
{
	int client = request.wen_fd;
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

int parse_request(struct wen_request request)
{
	if(!parse_request_line(request))return FALSE;
	
	return TRUE;
}

int parse_request_line(struct wen_request request)
{
	char request_line[1024];
	int count = get_line(request.wen_fd,request_line,1024);	
	if(count == 0){wen_free(request);return FALSE;}

 	printf(request_line);	

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
