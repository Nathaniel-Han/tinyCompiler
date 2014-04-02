#include "Syntax.h"

#define SetTbl(n1,n2,n3) ParseTbl[n1][n2]=n3 ;
#define SetPro(num,str)  ProductList[num]=#str ;
#define num2str(num,str) if(val==num) return #str ;
#define PrintHelper(num,str) if(message[i]==num) fprintf(out,#str);


Syntax::Syntax(void)
{
	ParseStack=stack_create(NULL,NULL);
	out=NULL;
}


Syntax::~Syntax(void)
{
	stack_destroy(ParseStack);
	if(!out)
		fclose(out);
}

void Syntax::Init()
{
	for(int i=0;i<20;i++)
		for(int j=0;j<50;j++)
			ParseTbl[i][j]=-1;

	SetTbl(0,15,1) SetTbl(1,15,5) SetTbl(1,30,2) SetTbl(1,33,3) SetTbl(1,1,4) SetTbl(2,15,6) 
	SetTbl(3,15,7) SetTbl(3,16,8) SetTbl(3,30,7) SetTbl(3,33,7) SetTbl(3,1,7) SetTbl(4,30,9)
	SetTbl(5,33,10) SetTbl(6,1,11) SetTbl(7,1,12) SetTbl(7,13,12) SetTbl(7,34,12) SetTbl(7,35,12)
	SetTbl(7,36,12) SetTbl(7,37,12) SetTbl(8,8,13) SetTbl(8,10,14) SetTbl(8,9,15) SetTbl(8,11,16)
	SetTbl(8,7,17) SetTbl(9,13,18) SetTbl(9,1,18) SetTbl(9,34,18) SetTbl(9,35,18) SetTbl(9,36,18)
	SetTbl(9,37,18)  SetTbl(10,14,21) SetTbl(10,17,21) SetTbl(10,8,21) SetTbl(10,9,21)
	SetTbl(10,10,21) SetTbl(10,11,21) SetTbl(10,7,21) SetTbl(10,2,19) SetTbl(10,3,20) SetTbl(11,13,22)
	SetTbl(11,1,22) SetTbl(11,34,22) SetTbl(11,35,22) SetTbl(11,36,22) SetTbl(11,37,22) SetTbl(12,14,25)
	SetTbl(12,17,25) SetTbl(12,8,25) SetTbl(12,9,25) SetTbl(12,10,25) SetTbl(12,11,25) SetTbl(12,7,25)
	SetTbl(12,2,25)  SetTbl(12,3,25) SetTbl(12,5,23) SetTbl(12,4,24) SetTbl(13,13,31) SetTbl(13,1,26)
	SetTbl(13,34,27) SetTbl(13,35,28) SetTbl(13,36,29) SetTbl(13,37,30)

	SetPro(1,6062) SetPro(2,6164) SetPro(3,6165) SetPro(4,6166) SetPro(5,6162) SetPro(6,62156316) SetPro(7,636163)
	SetPro(8,6300) SetPro(9,643013671431613261) SetPro(10,653313671461) SetPro(11,6601066917) SetPro(12,67696869) SetPro(13,6808) SetPro(14,6810)
	SetPro(14,6810) SetPro(15,6809) SetPro(16,6811) SetPro(17,6807) SetPro(18,697170) SetPro(19,70027170) SetPro(20,70037170) SetPro(21,7000)
	SetPro(22,717372) SetPro(23,72057372) SetPro(24,72047372) SetPro(25,7200) SetPro(26,7301) SetPro(27,7334) SetPro(28,7335)
	SetPro(29,7336) SetPro(30,7337) SetPro(31,73136914)

	message.clear();
	errorHint.clear();

}

void Syntax::Push(string& pro)
{
	assert(pro.length() >= 0);
	int i,limit=pro.length()-2;
	for(i=limit;i>=2;i=i-2)
		stack_push(ParseStack,(void*)(atoi(pro.substr(i,2).c_str())));

	//Print Helper======================================================
	message.push_back(-3);
	message.push_back(atoi(pro.substr(0,2).c_str()));
	message.push_back(-1);
	for(i=2;i<=limit;i=i+2)
	{
		message.push_back((atoi(pro.substr(i,2).c_str())));
		message.push_back(-4);
	}
	message.push_back(-2);
	//**Print Helper====================================================
		 
}

bool Syntax::Pop(int& top)
{
	if(stack_length(ParseStack)==0)
		return false;

	stack_top(ParseStack,(void**)&top);
	stack_pop(ParseStack);

	return true;
}

bool Syntax::Parse()
{
	Cur_Pos=0;
	int i=0,j=0,val=60,space_num=0;
	int error_num=100; //number of error message >=100
	int tmp;           //tmp production number
	char error[256];
	
	stack_clear(ParseStack);
	stack_push(ParseStack,(void*)val);
	
	while(stack_length(ParseStack)!=0 && Cur_Pos<TokenStream.size())
	{
		if(Pop(val))
		{
			if(val==0)
			{
				//Print Helper======================================================
				message.push_back(-3);
				message.push_back(0);
				message.push_back(-2);
				//**Print Helper====================================================
				continue;

			}
			
			if(val<60)
				if(val==TokenStream[Cur_Pos].id)
				{
					Cur_Pos++;
					message.push_back(val);
					message.push_back(-2);
				}
				else
				{
					//error handling
					string tmp=Num2Str(val);
					message.push_back(error_num);
					sprintf(error,"%s:%d:%d: error: Expected '%s'\n",TokenStream[Cur_Pos].sfname.c_str(),
						TokenStream[Cur_Pos].row,TokenStream[Cur_Pos].col,tmp.c_str());
					errorHint.push_back(error);
					Cur_Pos++;
					error_num++;
				}

			if(val>=60)
			{
				i=val-60;
				j=TokenStream[Cur_Pos].id;
				tmp=ParseTbl[i][j];  
				if(tmp==-1)
				{
					//error handling
					message.push_back(error_num);
					sprintf(error,"%s:%d:%d: error: Unexpected Token\n",TokenStream[Cur_Pos].sfname.c_str(),
						TokenStream[Cur_Pos].row,TokenStream[Cur_Pos].col);
					errorHint.push_back(error);
					Cur_Pos++;
					error_num++;
				}
				else
				{
					Push(ProductList[tmp]);
				}

			}

		}
	}

	return (stack_length(ParseStack)==0 && Cur_Pos==TokenStream.size());
}

void Syntax::PrintMessage()
{
	int i,size = message.size();

    for(i=0;i<size;i++)
    {
        if(message[i]==-1) fprintf(out,"  ->  ");
		if(message[i]==-2) fprintf(out,"\n");
		if(message[i]==-3) fprintf(out,"      ");
		if(message[i]==-4) fprintf(out,"  ");
	    PrintHelper(0,¦Å) PrintHelper(1,ID)
        PrintHelper(2,+) PrintHelper(3,-) PrintHelper(4,/) PrintHelper(5,*) PrintHelper(6,=) PrintHelper(7,==)
	    PrintHelper(8,<) PrintHelper(9,<=) PrintHelper(10,>) PrintHelper(11,>=) PrintHelper(12,!=) PrintHelper(15,{)
	    PrintHelper(16,}) PrintHelper(17,;) PrintHelper(28,int) PrintHelper(29,real) PrintHelper(30,if) PrintHelper(31,then)
	    PrintHelper(32,else) PrintHelper(33,while) PrintHelper(34,NUM) PrintHelper(35,NUM) PrintHelper(36,NUM) PrintHelper(37,NUM)
	    if(message[i]==13) fprintf(out,"(");
	    if(message[i]==14) fprintf(out,")");
	    PrintHelper(60,program) 
	    PrintHelper(61,stmt) PrintHelper(62,compoundstmt)
	    PrintHelper(63,stmts) PrintHelper(64,ifstmt) PrintHelper(65,whilestmt)
	    PrintHelper(66,assgstmt) PrintHelper(67,boolexpr) PrintHelper(68,boolop)
	    PrintHelper(69,arithexpr) PrintHelper(70,arithexprprime) PrintHelper(71,multexpr)
	    PrintHelper(72,multexprprime) PrintHelper(73,simpleexpr)
		if(message[i]>=100)
			fprintf(out,"%s\n",errorHint[message[i]-100].c_str());
	}

	
}

void Syntax::SetOutFname(const char* outfname)
{
	out=fopen(outfname,"w");
}
string Syntax::Num2Str(int val)
{
	num2str(2,+) num2str(3,-) num2str(4,/) num2str(5,*) num2str(6,=) num2str(7,==)
		num2str(8,<) num2str(9,<=) num2str(10,>) num2str(11,>=) num2str(12,!=) num2str(15,{)
		num2str(16,}) num2str(17,;) num2str(28,int) num2str(29,real) num2str(30,if) num2str(31,then)
		num2str(32,else) num2str(33,while)
		if(val==13) return "(";
	if(val==14) return ")";
	return "";
}