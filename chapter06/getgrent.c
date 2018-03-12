#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main()
{
	struct group *gp;

	setgrent();
	while((gp = getgrent())) {
		printf("group name:%20s, group id:%10d\n",gp->gr_name, gp->gr_gid);
	}
	endgrent();
}
