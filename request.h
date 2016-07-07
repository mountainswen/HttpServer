#define TRUE  1
#define FALSE 0
struct wen_request{
	int wen_fd;
	int wen_method;
	char* wen_url;
};

void do_request(struct wen_request);

