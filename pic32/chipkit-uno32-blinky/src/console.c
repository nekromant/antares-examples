struct console_device {
	void (*putc)(char* c);
	int (*getc)(void);
	/* private data */	
	
}
