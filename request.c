#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "request.h" 

int parse_request_line(char*,int);
void do_request(int fd)
{
	char buf[1024];
	char sbuf[512];
	int count = parse_request_line(buf,fd);
	write(1,buf,count);
	close(fd);
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
	printf("size is : %d\n",size);
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
