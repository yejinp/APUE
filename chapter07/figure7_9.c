#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define	TOK_ADD	5
#define	MAXLEN 1024

void do_line(char *);
void cmd_add(void);
int get_token(void);

int
main(void)
{
	char	line[MAXLEN];
	while(fgets(line, MAXLEN, stdin) )
	{
		do_line(line);
	}

	exit(0);
}

char	*tok_ptr;

void 
do_line(char *ptr)
{
	int	cmd;
	tok_ptr = ptr;
	while((cmd = get_token()) > 0) {
		switch(cmd) {
		case	TOK_ADD: 
			cmd_add();
			break;
		}
	}

}

void
cmd_add(void)
{
	int	token;
	token = get_token();
	/* rest of processing for this command */
}


int
get_token(void)
{
	/*fetch next token from line pointed to by tok_ptr */
}
