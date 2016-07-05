#ifndef __REQUEST__
#define __REQUEST__

void do_request(int fd);

struct wen_request{
	int wen_fd;
	int wen_method;
	char* wen_url;
};

#endif
