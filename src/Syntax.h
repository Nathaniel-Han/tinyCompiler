#pragma once
#ifndef SYNTAX_H
#define SYNTAX_H
#include "stack.h"
#include "Lex.h"
#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;

extern vector<Token> TokenStream;



class Syntax
{
private:
	int ParseTbl[20][50];
	string ProductList[40];
	Stack *ParseStack;
	int Cur_Pos;		        //current syntax analytical word index
	vector<int> message;
	vector<string> errorHint;
	map<string,int> ReservedTbl;
	void Push(string& pro);
	bool Pop(int &top);
	FILE* out;
    string Num2Str(int val);

public:
	Syntax(void);
	~Syntax(void);
	void SetOutFname(const char* outfname);
	bool Parse();
	void Init();
	void PrintMessage();
};

#endif