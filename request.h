#ifndef __REQUEST__
#define __REQUEST__

#define TRUE  1
#define FALSE 0

#define METHOD int
#define VERSION int

#define POST 1
#define GET  2

#define HTTP_1_0 1
#define HTTP_1_1 2

struct wen_request{
	int wen_fd;
	METHOD wen_method;
	char wen_url[1024];
	VERSION wen_version;
};

void do_request(struct wen_request*);

#endif
