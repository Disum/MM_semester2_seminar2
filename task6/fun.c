#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun.h"
int strcmp_spcf(const char *str1, const char *str2);
#define MAX_LEN 1024

int strcmp_spcf(const char *str1, const char *str2)
{
	char *c1, *c2, *c_srch;
	int pls, cnt_srch1, cnt_srch2;

	c1 = (char *)str1;
	c2 = (char *)str2;
	pls = 0;
	if( *c2=='\\' && ( *(c2 + 1)=='+' || *(c2 + 1)=='\\' ) )
		c2++;
	while( *c1 && *c1!='\n' && *c2 && *c2!='\n' )
	{
		if( pls )
		{
			cnt_srch2 = 0;
			c_srch = c2 - 1;
			c2++;
			while( *c_srch==*c2 )
			{
				c2++;
				if( *c2!='+' )
					cnt_srch2++;
				else
					c2++;
			}

			cnt_srch1 = 0;
			while( *c_srch==*(c1 + cnt_srch1) )
			{
				cnt_srch1++;
			}

			if( cnt_srch1<cnt_srch2 )
				return 1;

			c1 += cnt_srch1;
		}

		if( *c1!=*c2 )
			return 1;

		c1++;
		c2++;

		pls = 0;
		if( *c2=='\\' && ( *(c2 + 1)=='+' || *(c2 + 1)=='\\' ) )
			c2++;
		else if( *c2=='+' )
			pls = 1;
	}

	if( (!*c1 || *c1=='\n') && (!*c2 || *c2=='\n') )
		return 0;
	return 1;
}

/* Ф-ия выводит в name_out строки из name_in, совпадающие со строкой s.
 * Последовательностям "\+" и "\\" в s соответствуют '+' и '\'.
 * Символ '+' в s означает, что предыдущий символ может учитываться один или более раз.
 * Ф-ия возвращает:
 * ERROR_OPEN_IN, если не удалось открыть name_in;
 * ERROR_OPEN_OUT, если не удалось открыть name_out;
 * ERROR_MEMORY, если не удалось выделиь память;
 * кол-во выведенных строк, если проблем не возникло. */
int fun(const char *name_in, const char *name_out, const char *s)
{
	FILE *in, *out;
	int count = 0;
	char *buff;

	if( !(in = fopen(name_in, "r")) )
		return ERROR_OPEN_IN;
	if( !(out = fopen(name_out, "w")) )
	{
		fclose(in);
		return ERROR_OPEN_OUT;
	}

	if( !(buff = (char *)malloc(MAX_LEN)) )
	{
		fclose(in);
		fclose(out);
		return ERROR_MEMORY;
	}

	while( fgets(buff, MAX_LEN, in) )
	{
		if( !strcmp_spcf(buff, s) )
		{
			count++;
			fprintf(out, "%s\n", buff);
		}
	}

	free(buff);
	fclose(in);
	fclose(out);
	return count;
}
