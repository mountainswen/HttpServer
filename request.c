#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "request.h" 
#include<string.h>
int parse_request_line(char*,int);
int get_line(int,char*,int);
void do_request(int client)
{
	char buf[1024];
	int count = read(client,buf,sizeof buf);
	if(count == 0){close(client);return ;}
	printf("count :%d\n",count);
	
	printf("\n send to server ..\n");	

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

}

int parse_request_line(char *buf,int fd)
{
	char line[1024];
	int n = get_line(fd,line,sizeof line);
	memcpy(buf,line,n);	
	write(1,line,n);
	return n;
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
