
#include "philo.h"

int main(void)
{
	struct timeval	t0;
	struct timeval	t1;
	gettimeofday(&t0, 0);
	/* ... */
	usleep(100000);
	gettimeofday(&t1, 0);
	long elapsed = (t1.tv_sec-t0.tv_sec)*1000+t1.tv_usec-t0.tv_usec;
	printf("Elapsed: %ld\n", elapsed);
}