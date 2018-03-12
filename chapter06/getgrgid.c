#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc, char **argv)
{
	struct group *gp;
	gp = getgrgid(getgid());
	if(gp) {
		printf("my group name is:%s, group id is:%d\n",
			gp->gr_name, gp->gr_gid);
	}

}
