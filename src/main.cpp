#include<stdio.h>

#include "Lex.h"
#include "Syntax.h"
#include "global.h"


int main(int argc, char* argv[])
{
	char infname[128];
	char outfname[128];
	if(argc==2)
		sprintf(infname,"%s",argv[1]);
	else
	{
		printf("Too many/few arguments\nUsage:tinyParse fname\n");
		return -1;
	}
	sprintf(outfname,"r%s",infname);

	Lex lex;
	Syntax syntax;
	lex.Init();
	syntax.Init();
	
	lex.SetSourceFname(infname);
	syntax.SetOutFname(outfname);
	TokenStream.clear();
	lex.GenToken(&TokenStream);

	/* test TokenStream
	FILE* fp=fopen("TokenStream.txt","w");
	for(int i=0;i!=TokenStream.size();i++)
		fprintf(fp,"id=%d, value=%s, row=%d, col=%d, sfname=%s\n",
		           TokenStream[i].id,TokenStream[i].value.c_str(),TokenStream[i].row,TokenStream[i].col,TokenStream[i].sfname.c_str());
	fclose(fp);*/

	syntax.Parse();
	syntax.PrintMessage();
	

	return 0;
}