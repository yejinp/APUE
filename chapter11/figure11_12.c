#include <stdlib.h>
#include <pthread.h>

#define		NHASH		29
#define		HASH(fp)	(((unsigned long)fp)%NHASH)

struct foo *fh[NHASH];

pthread_mutex_t	hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo{
	int	f_count;
	struct	foo	*f_next;
	int	f_id;
};


struct	foo*	foo_alloc(void)
{
	struct	foo	*fp;
	int	idx;
	if((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;

		idx = HASH(fp);
		pthread_mutex_lock(&hashlock);
		fp->f_next = fh[idx];
		fh[idx] = fp->f_next;
		pthread_mutex_unlock(&hashlock);
	}

	return fp;
}

void foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&hashlock);
	fp->f_count ++;
	pthread_mutex_unlock(&hashlock);
}

struct	foo *
foo_find(int id)
{
	struct	foo	*fp;
	int	idx;

	idx = HASH(fp);
	pthread_mutex_lock(&hashlock);
	for(fp = fh[idx]; fp != NULL; fp = fp->f_next) {
		if(fp->f_id == id) {
			fp->f_count++;
			break;
		}
	}

	pthread_mutex_unlock(&hashlock);
	return fp;
}


void
foo_rele(struct	foo *fp)
{
	struct	foo	*tfp;
	int	idx;
	
	pthread_mutex_unlock(&hashlock);
	if(fp->f_count == 1) {
		idx = HASH(fp);
		tfp = fh[idx];
		if(tfp == fp) {
			fh[idx] = fp->f_next;
		} else {
			while(tfp->f_next != fp) {
				tfp = tfp->f_next;
			}
			tfp->f_next = fp->f_next;
		pthread_mutex_unlock(&hashlock);
		free(fp);
		}
	} else {
		pthread_mutex_unlock(&hashlock);
	}

}
