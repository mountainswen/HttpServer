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
//	int count = read(client,buf,sizeof buf);
//	int count = parse_request_line(buf,fd);
//	sprintf(buf,"hello myname is wenguangshan, how are you\r\n");

//	for (int i=0;i<1022;++i)buf[i] = 'B';
//	buf[1022] = '\r';
//	buf[1023] = '\r';
//	write(fd,buf,sizeof(buf)+1);
//	send(fd,buf,sizeof buf,0);
	//exit(0);
	buf[0] = 'w';
	
	send(client,buf,1,0);
//	close(client);
	// sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
	
//	  send(client, buf, sizeof(buf), 0);
//	   sprintf(buf, "Content-type: text/html\r\n");
//	    send(client, buf, sizeof(buf), 0);
//	     sprintf(buf, "\r\n");
//	      send(client, buf, sizeof(buf), 0);
//	       sprintf(buf, "<P>Your browser sent a bad request, ");
//	        send(client, buf, sizeof(buf), 0);
//		 sprintf(buf, "such as a POST without a Content-Length.\r\n");
//		  send(client, buf, sizeof(buf), 0);
//	for (int i=0;i<100;++i)buf[i] = 'A';
//	buf[100] = '\r';
//	buf[101] = '\n';
//	write(fd,buf,102); 
	//如果这里写的是sizeof buf则浏览器端会直接下载，如果写的是具体的长度，则会显示。？
	// 浏览器不知道如何显示，于是直接下载下来？
	//这里write和send函数的效果是一样的
//	close(client);
//	exit(1);
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
