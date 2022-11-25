#include<stdio.h>
#define MAXLINE 100 /*maximum input line length*/
#include "pattern"
int strindex(char source[],char pattern[]);

int main(void)
{
	char line[MAXLINE];

	while ((getchar()!=EOF))
	{
		fgets(line,100,stdin);
		if(strindex(line,pattern) > 0)
			printf("%s",line);
	}
}

int strindex(char s[],char p[])
{
	int i,j,k;

	for (i = 0; s[i] != '\0' ; ++i)
	{
		for (j=i,k=0;p[k] != '\0' && s[j]==p[k];++j,++k)
			;
		if ( k > 0 && p[k] == '\0')
			return i;
	}
	return -1;
}

