#pragma once

#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <map>
#include <vector>
#include <string>

using std::vector;
using std::map;
using std::string;

struct Token
{
	int id;
	string value;
	int row;
	int col;
	string sfname;
	Token(int _id, string _value,int _row,int _col, string _sfname)
	{
		id=_id;
		value=_value;
		row=_row;
		col=_col;
		sfname=_sfname;
	}
	~Token(){}
};

class Lex
{
private:
	int Lextable[30][128];        //state transition table
	map<string, int> KeywordTbl;  //keyword table
	string  sourceFname;            //source file's Name
	vector<Token>* pTokenList;
	string Source;                 //source file's content
	string Buffer;                 //lex Buffer
	int state;                     //automata state 
	int row;                       //row number
	int col;                       //col number
	int tmp_col;
	int current_pos;               //current postion of file pointer
	void setLexTbl(const char* lexFname);
	void setKeywordTbl(const char* keywordFname=NULL);
	bool Handle(int tag);
    bool FindKeyword(string target,int &id);	
	void SubmitToken(const int _id,const string& _value,const int _row, const int _col);

public:
	Lex(void);
	~Lex(void);
	void Init();
	bool SetSourceFname(string fname);
	int GenToken(vector<Token>* m_pTokenList);
	
};




#endif

