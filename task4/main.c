#include <stdio.h>
#include <time.h>
#include "fun.h"

int main(int argc, char **argv)
{
	int res;
	clock_t t_begin;

	if( argc<4 )
	{
		fprintf(stderr, "Usage: %s a b s\n", argv[0]);
		return 1;
	}

	t_begin = clock();
	res = fun(argv[1], argv[2], argv[3]);
	printf("Time: %.2lf\n", (double)(clock() - t_begin)/CLOCKS_PER_SEC);
	if( res<0 )
	{
		switch( res )
		{
		case ERROR_OPEN_IN:
			fprintf(stderr, "Can not open %s!\n", argv[1]);
			return 2;
		case ERROR_OPEN_OUT:
			fprintf(stderr, "Can not open %s!\n", argv[2]);
			return 2;
		case ERROR_MEMORY:
			fprintf(stderr, "Can not allocate memory!\n");
			return 3;
		default:
			fprintf(stderr, "Unknown error with code %d!\n", res);
			return 4;
		}
	}
	printf("Number of printed strings: %d\n", res);

	return 0;
}
