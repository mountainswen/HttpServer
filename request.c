#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "request.h" 

void parse_request_line(char*);
void do_request(int fd)
{
	char buf[512];
	char sbuf[512];
	int count = read(fd,buf,sizeof(buf));
	parse_request_line(buf);
	write(fd,buf,count);
	close(fd);
}

void parse_request_line(char *buf)
{
	char method[6];
	char url[20];
	char httpversion[10];
	
	int flag = 0;
	char* tmp = method;
	while(1)
	{
		if(flag == 2)break;
		switch (*buf)
		{
			case ' ':
				if(flag == 0){tmp = url;flag++;}
				else if(flag == 1){tmp = httpversion; flag ++;}
				else fprintf(stdout,"something wrong!");
				break;
			default:
				*tmp = *buf;
				tmp ++;
		}

		buf++;
	}

	fprintf(stdout,method);
	fprintf(stdout,"\n");
	fprintf(stdout,url);
	fprintf(stdout,"\n");
//	fprintf(stdout,httpversion);
}
