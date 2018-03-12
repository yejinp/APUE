#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <stddef.h>
#include <string.h>

int main(int argc, char **argv)
{
	struct passwd *ptr;
	setpwent();
	while((ptr = getpwent()) != NULL) {
		if(ptr)
		printf("name:%s\n", ptr->pw_name);
	}
	endpwent();
}
