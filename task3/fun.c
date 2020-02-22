#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun.h"
char *strstr_spcf(const char *str1, const char *str2, const int *wh_sp);
#define MAX_LEN 1024
#define CHAR_SZ 256

char *strstr_spcf(const char *str1, const char *str2, const int *wh_sp)
{
	char *c1, *c1_beg, *c2;

	for( c1_beg = (char *)str1, c1 = c1_beg; *c1_beg && *c1_beg!='\n'; c1_beg++, c1 = c1_beg )
	{
		if( !wh_sp[(int)( (unsigned char)*c1 )] && c1!=str1 )
			continue;

		while( wh_sp[(int)( (unsigned char)*c1 )] && *c1 && *c1!='\n' )
			c1++;

		c2 = (char *)str2;

		while( *c1==*c2 )
		{
			c1++;
			c2++;

			if( (wh_sp[(int)( (unsigned char)*c1 )] || !*c1 || *c1=='\n')
				&& (wh_sp[(int)( (unsigned char)*c2 )] || !*c2 || *c2=='\n') )
			{
				return c1_beg;
			}
		}
	}

	return NULL;
}

/* Ф-ия выводит в name_out строки из name_in, имеющие общее слово со строкой s.
 * Символы, содержащиеся в t - пробельные.
 * Ф-ия возвращает:
 * ERROR_OPEN_IN, если не удалось открыть name_in;
 * ERROR_OPEN_OUT, если не удалось открыть name_out;
 * ERROR_MEMORY, если не удалось выделиь память;
 * кол-во выведенных строк, если проблем не возникло. */
int fun(const char *name_in, const char *name_out, const char *s, const char *t)
{
	FILE *in, *out;
	int i, count = 0, *wh_sp;
	char *buff, *c, *wrd_beg;

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
	if( !(wh_sp = (int *)malloc(CHAR_SZ*sizeof(int))) )
	{
		free(buff);
		fclose(in);
		fclose(out);
		return ERROR_MEMORY;
	}

	for( i = 0; i<CHAR_SZ; i++ )
	{
		wh_sp[i] = 0;
	}
	for( c = (char *)t; *c!='\0' && *c!='\n'; c++ )
	{
		wh_sp[(int)( (unsigned char)*c )] = 1;
	}

	while( fgets(buff, MAX_LEN, in) )
	{
		wrd_beg = (char *)s;
		while( wh_sp[(int)( (unsigned char)*wrd_beg )] && *wrd_beg && *wrd_beg!='\n' )
				wrd_beg++;

		while( *wrd_beg && *wrd_beg!='\n' )
		{
			if( strstr_spcf(buff, wrd_beg, wh_sp) )
			{
				count++;
				fprintf(out, "%s\n", buff);
				break;
			}

			while( !wh_sp[(int)( (unsigned char)*wrd_beg )] && *wrd_beg && *wrd_beg!='\n' )
				wrd_beg++;
			while( wh_sp[(int)( (unsigned char)*wrd_beg )] && *wrd_beg && *wrd_beg!='\n' )
				wrd_beg++;
		}
	}

	free(wh_sp);
	free(buff);
	fclose(in);
	fclose(out);
	return count;
}
