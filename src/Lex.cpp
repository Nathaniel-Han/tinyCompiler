#include "Lex.h"


#define HandleToken(x,y) if(tag==x){SubmitToken(y,"",row,col);}

Lex::Lex(void)
{
}


Lex::~Lex(void)
{
}

void Lex::setLexTbl(const char* lexFname)
{
	FILE *fp = fopen("lex.txt","r");

	int i=0,j=0;
	while(!feof(fp))
	{
		fscanf(fp, "%d ", &Lextable[i][j]);
		if(j!=127)
			j++;
		else
		{
			i++;
			j=0;
		}
	}
	fclose(fp);
	return;
}

void Lex::setKeywordTbl(const char* keywordFname)
{
	KeywordTbl["+"]=2;
	KeywordTbl["-"]=3;
	KeywordTbl["/"]=4;
	KeywordTbl["*"]=5;
	KeywordTbl["="]=6;
	KeywordTbl["=="]=7;
	KeywordTbl["<"]=8;
	KeywordTbl["<="]=9;
	KeywordTbl[">"]=10;
	KeywordTbl[">="]=11;
	KeywordTbl["!="]=12;
	KeywordTbl["("]=13;
	KeywordTbl[")"]=14;
	KeywordTbl["{"]=15;
	KeywordTbl["}"]=16;
	KeywordTbl[";"]=17;
	KeywordTbl["int"]=28; 
	KeywordTbl["real"]=29;
	KeywordTbl["if"]=30;
	KeywordTbl["then"]=31;
	KeywordTbl["else"]=32;
	KeywordTbl["while"]=33;

	return;
}

bool Lex::SetSourceFname(string fname)
{
	FILE *fp=NULL;
	if((fp=fopen(fname.c_str(),"r"))!=NULL)
	{
		sourceFname = fname;
		fclose(fp);
		return true;
	}
	return false;
}

int  Lex::GenToken(vector<Token>* m_pTokenList)
{
	//source file handling=======================================
	FILE *fp = fopen(sourceFname.c_str(),"r");
	int tag=1; //use1:file tag
	char  buf[1];
	while(tag==1)
	{
		tag=fread(buf,1,1,fp);
		if(tag==1)
			Source.push_back((char)buf[0]);
	}
	fclose(fp);
	tag=0;  //use2:automata state
	Source.push_back(' ');  //a trick
	//**source file handing======================================


	current_pos=0;
    pTokenList=m_pTokenList;
	state=1;
	Buffer="";
	row=1;
	col=tmp_col=1;
	pTokenList->clear();
	

	while(current_pos<Source.length())
	{	
		if(Source[current_pos]=='\n')
		{
			row++;
			//col=1;
		}
		
		Buffer.push_back(Source[current_pos]);

		tag=Handle(Lextable[state][(int)Source[current_pos]]);

		if (tag<0)
		{
			//Error Handling...
			fprintf(stderr,"lexical analyser error occurred in row %d,col%d",row,col);
		}
		current_pos++;
	}
	
	return tag;
}

void Lex::Init()
{
	setLexTbl("lex.txt");
	setKeywordTbl();
}

bool Lex::Handle(int tag)
{
	if(tag==-99)
		return false;
	int id,i,fEnter=0;

	if(tag<0)
	{
		
		if(Buffer[Buffer.length()-1]=='\n')
		{
			row--;
			fEnter=1;
		}
		//buffer back
		Buffer=Buffer.substr(0,Buffer.length()-1);
		current_pos--;

		//Buffer.trim()============================================
		i=0;
		while(Buffer[i]<=32)
			i++;
		Buffer=Buffer.substr(i,Buffer.length());
		i=Buffer.length()-1;
		while(Buffer[i]<=32)
			i--;
		Buffer=Buffer.substr(0,i+1);
		//**Buffer.trim()===========================================

		HandleToken(-1,13);
		HandleToken(-2,14);
		HandleToken(-3,2);
		HandleToken(-4,5);
		HandleToken(-5,3);
		HandleToken(-7,4);
		if(tag<=-8 && tag>=-11)
		{
			//Handle contants
			//Think About Symbol Table
			SubmitToken(-tag+26,"",row,col);
		}
		HandleToken(-12,12);
		HandleToken(-14,17);
		HandleToken(-15,6);
		HandleToken(-16,7);
		HandleToken(-17,8);
		HandleToken(-18,9);
		HandleToken(-19,11);
		HandleToken(-20,10);
		HandleToken(-21,15);
		HandleToken(-22,16);
		if(tag==-23)         //handle keyword and identifier
		{
			if(FindKeyword(Buffer,id))
			{
				SubmitToken(id,"",row,col);
			}
			else
			{
				SubmitToken(1,Buffer,row,col);
			}

		}

		if(fEnter)
			col=1;
		else
			col+=Buffer.length();
		Buffer="";
		state=1;		
	}
	else
	{
		state=tag;
	}
	return true;
}

bool Lex::FindKeyword(string target,int &id)
{
	if(KeywordTbl.find(target)!=KeywordTbl.end())
	{
		id=KeywordTbl[target];
		return true;
	}
	return false;
}

void Lex::SubmitToken(const int _id,const string& _value,const int _row, const int _col)
{
	pTokenList->push_back(Token(_id,_value,_row,_col,sourceFname));
}
