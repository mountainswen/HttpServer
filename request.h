#ifndef __REQUEST__
#define __REQUEST__

#define TRUE  1
#define FALSE 0

#define METHOD int
#define VERSION int

#define AGAIN 1
#define OK 2

#define POST 1
#define GET  2

#define HTTP_1_0 1
#define HTTP_1_1 2

#define MIN(X,Y) X>Y?Y:X

#define MAX_REQUEST 1024*8
struct wen_request{
	char BUF[MAX_REQUEST];
	int pos_first;
	int pos_last;
	int wen_fd;
	char* uri_start;
	char* uri_end;
	char* method_start;
	char* method_end;
	METHOD wen_method;
	char wen_url[1024];
	VERSION wen_version;
};

void init_request(struct wen_request*,int);
void do_request(struct wen_request*);

#endif
