#include<stdio.h>
#include "../../mylibrary/mychar.h"
#define MAXLINE 100

/* rudimentary calculator */

int main(void)
{
	double sum;
	char line[MAXLINE];

	sum = 0;
	while ( GETLINE(line,MAXLINE) > 0){
		printf("\t%g\n",sum += atof(line));
	}
	return 0;
}
