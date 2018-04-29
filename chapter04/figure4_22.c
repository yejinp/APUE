#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <strings.h>

typedef	int	Myfunc(const char *, const struct stat *, int);

static	Myfunc	myfunc;
static	int	myftw(char *, Myfunc *);
static	int	dopath(Myfunc *);

static	long	nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

char *path_alloc(int *len)
{
	
	char *path = NULL;
	path = (char *) malloc(1024);

	*len = 1024;
	return path;
}

int
main(int argc, char *argv[])
{
	int	ret;
	if(argc != 2) {
		printf("usage: %s <starting-pathname>\n", argv[0]);
		exit(9);
	}

	ret = myftw(argv[1], myfunc);

	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if(ntot == 0) 
		ntot = 1; /*avoid divide by 0; print 0 for all counts */
	
	printf("regular files  = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
	printf("directories    = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
	printf("block special  = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
	printf("char special   = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
	printf("FIFOs          = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
	printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
	printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);
	exit(0);
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 *
*/

#define		FTW_F	1
#define		FTW_D	2
#define		FTW_DNR	3
#define		FTW_NS	4

static	char	*fullpath;
static int
myftw(char *pathname, Myfunc *func)
{
	int	len;
	fullpath = path_alloc(&len);

	strncpy(fullpath, pathname, len);
	fullpath[len - 1] = 0;
	return	(dopath(func));
}

static int
dopath(Myfunc *func)
{
	struct	stat	statbuf;
	struct	dirent	*dirp;
	DIR	*dp;
	int	ret;
	char	*ptr;

	if(lstat(fullpath, &statbuf) < 0) 
		return (func(fullpath, &statbuf, FTW_NS));

	if(S_ISDIR(statbuf.st_mode) == 0)
		return (func(fullpath, &statbuf, FTW_F));

	if((ret = func(fullpath, &statbuf, FTW_D)) != 0) 
		return ret;

	ptr = fullpath + strlen(fullpath);
	*ptr++ = '/';
	*ptr = 0;

	if((dp = opendir(fullpath)) == NULL)
		return (func (fullpath, &statbuf, FTW_DNR));

	while((dirp = readdir(dp)) != NULL) {
		if(strcmp(dirp->d_name, ".") == 0 ||
			strcmp(dirp->d_name, "..") == 0) 
			continue;

		strcpy(ptr, dirp->d_name);

		if((ret = dopath(func))) 
			break;
	}

	ptr[-1] = 0;

	if(closedir(dp) < 0) {
		printf("can't close directory %s\n", fullpath);
		exit(9);
	}

	return (ret);
}


static int
myfunc(const char *pathname, const struct stat *statptr, int type)
{
	switch(type) {
	case	FTW_F:
		switch (statptr->st_mode &S_IFMT) {
		case S_IFREG:	nreg++;	break;
		case S_IFBLK:	nblk++;	break;
		case S_IFCHR:	nchr++;	break;
		case S_IFIFO:	nfifo++;	break;
		case S_IFLNK:	nslink++;	break;
		case S_IFSOCK:	nsock++;	break;
		case	S_IFDIR:
			printf("for S_IFDIR for %s", pathname);
		}
		break;

	case FTW_D:
		ndir++;
		break;

	case FTW_DNR:
		printf("can't read directory %s\n", pathname);
		break;

	case FTW_NS:
		printf("stat error for %s\n", pathname);
		break;
	default:
		printf("unkown type %d for pathname %s\n", type, pathname);
	}
	return (0);
}

