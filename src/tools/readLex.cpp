#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *fp=fopen("lex.txt","r");
	int tbl[26][128];
	int i=0,j=0;
	while(!feof(fp))
	{
	  fscanf(fp, "%d ", &tbl[i][j]);
	  if(j!=127)
	    j++;
	  else
	  {
	    i++;
		j=0;
	  }
	}
	fclose(fp);
	printf("tbl[1][123]=%d\n",tbl[1][123]);
}